from dataclasses import dataclass
from bs4 import BeautifulSoup, Tag
import requests

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

        return ",".join(args)

    @property
    def cycles_str(self) -> str:
        return f"{self.hi_cycles}" if self.hi_cycles == self.lo_cycles else f"{self.hi_cycles}/{self.lo_cycles}"
    
    @property
    def flags_str(self) -> str:
        return f"{self.z} {self.n} {self.h} {self.c}"

    def table(self) -> str:
        return ""
    
    def header(self) -> str:
        return ""
    
    def __str__(self) -> str:
        if self.unused:
            return f"[u] {self.hex_str}"

        id = f"{"[cb] " if self.cb else ""}{self.hex_str}"
        info = f"{self.asm_str} | {self.bytes}  {self.cycles_str} | {self.flags_str}"

        return f"{id} -> {info}"

def parse_table(table: Tag, arr: list, cb: bool) -> None:
    for i, row in enumerate(table.find_all("tr")):
        if i == 0: continue

        for j, cell in enumerate(row.find_all("td")):
            if j == 0: continue

            dec = ((i-1) * 16) + ((j-1))
            cmd, dest, src = "NOP", "", ""
            bytes = 1
            hi_cycles, lo_cycles = 4, 4
            z, n, h, c = "-", "-", "-", "-"

            if (not cb) and (dec in UNUSED):
                arr.append(Op(
                    cb,
                    True,
                    dec,
                    cmd, dest, src,
                    bytes,
                    hi_cycles, lo_cycles,
                    z, n, h, c
                ))
                continue

            l1, l2, l3 = list(cell.stripped_strings)

            l1 = l1.split()
            cmd = l1[0]

            if len(l1) == 2:
                args = l1[1].split(",")

                if len(args) == 2:
                    dest, src = args[0], args[1]
                else:
                    dest = args[0]
            
            l2 = l2.replace("\xa0", " ")
            bytes, cycles = l2.split()

            bytes = int(bytes)

            if "/" in cycles:
                hi_cycles, lo_cycles = (int(c) for c in cycles.split("/"))
            else:
                hi_cycles, lo_cycles = int(cycles), int(cycles)

            z, n, h, c = l3.split()

            arr.append(Op(
                cb,
                False,
                dec,
                cmd, dest, src,
                bytes,
                hi_cycles, lo_cycles,
                z, n, h, c
            ))

def main() -> None:
    res = requests.get("https://pastraiser.com/cpu/gameboy/gameboy_opcodes.html")
    soup = BeautifulSoup(res.text, "html.parser")

    op_table, op_cb_table = soup.find_all("table", limit=2)
    ops, ops_cb = [], []

    parse_table(op_table, ops, False)
    parse_table(op_cb_table, ops_cb, True)

    for op in ops: print(op)
    for op_cb in ops_cb: print(op_cb)

if __name__ == '__main__':
    main()