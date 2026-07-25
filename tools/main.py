from tkinter import Tk, filedialog
from subprocess import run
from pathlib import Path
from platform import system

def main() -> None:
    EXE_PATH = str(Path(__file__).resolve().parent.parent / "build" / ("vdmg" + (".exe" if system() == "Windows" else "")))
    ROM_DIR = str(Path(__file__).resolve().parent.parent / "roms")

    root = Tk()
    root.withdraw()

    if not (rom_path := filedialog.askopenfilename(
        title="Select ROM",
        initialdir=ROM_DIR,
        filetypes=[("ROM", "*.gb *.gbc")]
    )): return
    sav_path = filedialog.askopenfilename(
        title="Select Save",
        initialdir=ROM_DIR,
        filetypes=[("Save", "*.sav")]
    )

    rom_path = str(Path(rom_path).resolve())
    if sav_path: sav_path = str(Path(sav_path).resolve())

    args = [EXE_PATH, rom_path]
    if sav_path: args.append(sav_path)

    res = run(args)

    if res.returncode != 0: print(f"Exited with code {res.returncode}")
    else: print("Exited successfully")

if __name__ == "__main__":
    main()