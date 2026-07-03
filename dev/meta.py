from bs4 import BeautifulSoup
import requests

class Op:
    def __init__(self, opcode: str, cb: bool, mnem: str, byte_len: int, cycles: int, z: str, n: str, h: str, c: str) -> None:
        self.opcode = opcode
        self.cb = cb
        self.mnem = mnem
        self.byte_len = byte_len
        self.cycles = cycles
        self.z = z
        self.n = n
        self.h = h
        self.c = c

    def hpp(self) -> str:
        return f"uint8_t op_{'cb_' if self.cb else ''}{self.opcode}(); /// {self.mnem} ({self.byte_len} byte{'s' if self.byte_len > 1 else ''}, {self.cycles} cycle{'s' if self.cycles > 1 else ''}, {self.z} {self.n} {self.h} {self.c})"

    # TODO: Cover basic mnems like LD.
    def cpp(self) -> str:
        return f"""uint8_t CPU::op_{'cb_' if self.cb else ''}{self.opcode}() {{
    return {self.cycles};
}}
"""

def main() -> None:
    pass

if __name__ == '__main__':
    main()