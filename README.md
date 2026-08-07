# vdmg
**Status: DMG-01 functional, CGB and optimization WIP.**

Emulator for the DMG-01 and CGB.

## Hardware roadmap
- **CPU**
  - 256 standard 8-bit opcodes
  - 256 CB prefix opcodes
  - Interrupt handling
  - Halt bug
    
- **MMU**
  - ROM verification
  - Header parsing
  - *0xffff* (65535) memory slots
  - Gated memory read and writes
  - Memory bank controller intercepts
  - IO side effects

- **PPU**
  - Background
  - Window
  - Sprites
  - Accurate overlap edge cases
  - Scanline-based rendering

- **APU**
  - Pulse + Sweep channel
  - Pulse channel
  - Wave channel
  - Noise channel
