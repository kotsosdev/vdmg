from bs4 import BeautifulSoup
import requests

UNUSED = {0xd3, 0xe3, 0xe4, 0xf4, 0xdb, 0xeb, 0xec, 0xfc}

class Op:
    def __init__(self, opcode: str, cb: bool, mnem: str, byte_len: int, cycles_hi: int, cycles_lo: int, z: str, n: str, h: str, c: str) -> None:
        self.opcode = opcode.lower()
        self.cb = cb
        self.mnem = mnem
        self.byte_len = byte_len
        self.cycles_hi = cycles_hi
        self.cycles_lo = cycles_lo
        self.z = z
        self.n = n
        self.h = h
        self.c = c
        self.cycles_str = f'{self.cycles_hi}' if self.cycles_lo == self.cycles_hi else f'{self.cycles_hi} / {self.cycles_lo}'

    def get_body(self) -> str:
        ...

    def table(self) -> str:
        return f'op_{"cb_" if self.cb else ""}table[{self.opcode}] = &CPU::op_{"cb_" if self.cb else ""}{self.opcode};'

    # FIXME
    def hpp(self) -> str:
        return f'uint8_t op_{"cb_" if self.cb else ""}{self.opcode}(); /// {self.mnem} ({self.byte_len} byte{"s" if self.byte_len > 1 else ''}, {self.cycles} cycle{'s' if self.cycles > 1 else ""}, {self.z} {self.n} {self.h} {self.c})'

    def cpp(self) -> str:
        return f"""uint8_t CPU::op_{'cb_' if self.cb else ''}{self.opcode}() {{
    {self.get_body()}
    return {self.cycles_str};
}}
"""

def main() -> None:
    pass

if __name__ == '__main__':
    main()