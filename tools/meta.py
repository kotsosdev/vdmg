from dataclasses import dataclass
from typing import Callable
from pathlib import Path
from bs4 import BeautifulSoup, Tag
import requests

TABLE_LINK = "https://pastraiser.com/cpu/gameboy/gameboy_opcodes.html"
OUTPUT_PATH = "out.txt"
UNUSED = {0xd3, 0xe3, 0xe4, 0xf4, 0xdb, 0xdd, 0xeb, 0xec, 0xed, 0xfc, 0xfd}

@dataclass
class Op:
    cb: bool
    unused: bool
    dec: int
    cmd: str
    dest: str
    src: str
    bytes: int
    hi_cycles: int
    lo_cycles: int
    z: str
    n: str
    h: str
    c: str
    func_body: str = ""

    @property
    def id_str(self) -> str:
        return f"op_{'cb_' if self.cb else ''}"

    @property
    def hex_str(self) -> str:
        return f"0x{self.dec:02x}"
    
    @property
    def asm_str(self) -> str:
        return f"{self.cmd}{f" {self.args_str}" if self.args_str else ""}"
    
    @property
    def args_str(self) -> str:
        args = []
        if self.dest: args.append(self.dest)
        if self.src: args.append(self.src)

        return ", ".join(args)

    @property
    def cycles_str(self) -> str:
        return f"{self.hi_cycles}" if self.hi_cycles == self.lo_cycles else f"{self.hi_cycles}/{self.lo_cycles}"
    
    @property
    def flags_str(self) -> str:
        return f"{self.z} {self.n} {self.h} {self.c}"
    
    @property
    def info(self) -> str:
        if self.unused:
            return "Unused"

        return f"{self.asm_str} ({self.bytes} byte{'' if self.bytes == 1 else 's'}, {self.cycles_str} cycle{'' if self.hi_cycles == 1 else 's'}, flags: {self.flags_str})"
    
    def header(self) -> str:
        return f"uint8_t {self.id_str}{self.hex_str}(); /// {"Unused" if self.unused else self.asm_str}"
    
    def funcdef(self) -> str:
        ret = ""

        if self.hi_cycles == self.lo_cycles:
            ret = f"return {self.hi_cycles};"
        else:
            ret = f"// return {self.cycles_str};"

        return f"""uint8_t CPU::{self.id_str}{self.hex_str}() {{
    {self.func_body}
    {ret}
}}"""
    
    def case(self) -> str:
        return f"case {self.hex_str}: return {self.id_str}{self.hex_str}();{' // Unused' if self.unused else ''}"
    
    def __str__(self) -> str:
        return f"{self.id_str}{self.hex_str} -> {self.info}"

def parse(table: Tag, arr: list, _cb: bool) -> None:
    for i, row in enumerate(table.find_all("tr")):
        if i == 0: continue

        for j, cell in enumerate(row.find_all("td")):
            if j == 0: continue

            _dec = ((i-1) * 16) + ((j-1))
            _cmd, _dest, _src = "NOP", "", ""
            _bytes = 1
            _hi_cycles, _lo_cycles = 4, 4
            _z, _n, _h, _c = "-", "-", "-", "-"

            if (not _cb) and (_dec in UNUSED):
                arr.append(Op(
                    cb=_cb,
                    unused=True,
                    dec=_dec,
                    cmd=_cmd, dest=_dest, src=_src,
                    bytes=_bytes,
                    hi_cycles=_hi_cycles, lo_cycles=_lo_cycles,
                    z=_z, n=_n, h=_h, c=_c
                ))
                continue

            l1, l2, l3 = list(cell.stripped_strings)

            l1 = l1.split()
            _cmd = l1[0]

            if len(l1) == 2:
                args = l1[1].split(",")

                if len(args) == 2:
                    _dest, _src = args[0], args[1]
                else:
                    _dest = args[0]
            
            l2 = l2.replace("\xa0", " ")
            _bytes, _cycles = l2.split()

            _bytes = int(_bytes)

            if "/" in _cycles:
                _hi_cycles, _lo_cycles = [int(c) for c in _cycles.split("/")]
            else:
                _hi_cycles, _lo_cycles = int(_cycles), int(_cycles)

            _z, _n, _h, _c = l3.split()

            # Typos on pastraiser
            if _cmd == "BIT" and _src == "(HL)":
                _hi_cycles, _lo_cycles = 12, 12
            if _dec in (0xe2, 0xf2):
                _bytes = 1

            arr.append(Op(
                cb=_cb,
                unused=False,
                dec=_dec,
                cmd=_cmd, dest=_dest, src=_src,
                bytes=_bytes,
                hi_cycles=_hi_cycles, lo_cycles=_lo_cycles,
                z=_z, n=_n, h=_h, c=_c
            ))

def get_tables() -> tuple[list[Op], list[Op]]:
    res = requests.get(TABLE_LINK)
    soup = BeautifulSoup(res.text, "html.parser")

    op_table, op_cb_table = soup.find_all("table", limit=2)
    ops, ops_cb = [], []

    parse(op_table, ops, False)
    parse(op_cb_table, ops_cb, True)

    return (ops, ops_cb)

def save(text: str) -> None:
    with open((Path(__file__).parent / OUTPUT_PATH), "w") as file:
        file.write(text)

def format_matrix(oplist: list[Op], method: Callable) -> str:
    res = ""

    for i, op in enumerate(oplist):
        res += method(op) + " "

        if (i+1) % 16 == 0:
            res += "\n"
    
    return res

def format_row(oplist: list[Op], method: Callable) -> str:
    res = ""
    for i, op in enumerate(oplist):
        res += method(op) + "\n"

        if ((i+1) % 16 == 0) and i != len(oplist) - 1:
            res += "\n"

    return res

def format_all(oplist: list[Op], method: Callable, linebreaks: int = 1) -> str:
    res = ""
    for op in oplist:
        res += method(op) + ("\n" * linebreaks)

    return res