from tkinter import Tk, filedialog
from subprocess import run
from pathlib import Path
from platform import system

def main() -> None:
    EXE_PATH = Path(__file__).resolve().parent.parent / "build" / ("vdmg" + (".exe" if system() == "Windows" else ""))
    ROM_DIR = Path(__file__).resolve().parent.parent / "roms"

    root = Tk()
    root.withdraw()

    if not (rom_path := filedialog.askopenfilename(
        title="Select ROM",
        initialdir=ROM_DIR,
        filetypes=[("ROM", "*.gb *.gbc")]
    )): return

    rom_path = Path(rom_path).resolve()
    
    res = run([EXE_PATH, rom_path])

    if res.returncode != 0: print(f"Exited with code {res.returncode}")
    else: print("Exited successfully")

if __name__ == "__main__":
    main()