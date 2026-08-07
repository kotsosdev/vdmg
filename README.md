# vdmg
**Status: DMG-01 functional, CGB and optimization WIP.**

This software aims to emulate the original Game Boy (DMG-01) and its successor, the Game Boy Color (CGB). It is written in C++ using the SDL2 multimedia library.

## Usage
```text
vdmg.exe <rom_path> [sav_path]
```
- `rom_path`: (Required) The filepath to the target ROM. 
- `sav_path`: (Optional) The filepath for the save data. Defaults to the ROM directory with a `.sav` extension.

## Implementations
- **CPU**
  - 256 standard 8-bit opcodes
  - 256 CB prefix opcodes
  - Interrupt handling
  - Halt bug
    
- **MMU**
  - `0xffff` (65535) Memory slots
  - Gated memory read and writes
  - Memory bank controller intercepts
  - IO register side effects
  - Real time clock
  - `.gb`, `.gbc`, and `.sav` IO

- **PPU**
  - Background
  - Window
  - Objects/Sprites
  - Accurate overlap edge cases
  - Scanline-based rendering

- **APU**
  - Pulse + Sweep channel
  - Pulse channel
  - Wave channel
  - Noise channel
  - Mixer
  - Amplifier
