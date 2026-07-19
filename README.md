# vdmg
**Status: Work in progress.**

Emulator for the DMG-01 and CGB.

## Hardware roadmap
- **CPU**
  - 256 standard 8-bit opcodes
  - 256 CB prefix opcodes
  - Dual speed management
  - Cycle accuracy
  - Interrupt handling
    
- **MMU**
  - ROM verification
  - Header parsing
  - *0xffff* (65535) memory slots
  - Gated read and writes
  - MBC intercepts

- **PPU**
  - Sprite management

- **APU**
  - 4 audio channels
  - Frame sequencer timing
  - Digital audio buffer

## Machine learning integration
Exposing the emulator to python using ctypes will allow bots to play select titles.
