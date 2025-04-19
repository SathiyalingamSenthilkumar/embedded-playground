# Bare-metal embedded application using Nordic's MDK

This application is built using Nordic's **MDK (Microcontroller Development Kit)**. The
MDK provides:

- **GCC support** for compiling the firmware
- **Initialization code** for system setup
- **Register definition headers** for direct access to peripheral registers

The goal is to use these directly to learn from scratch, rather than adapting an
existing example.

Nordic's MDK and Arm's CMSIS are included as Git submodules.

## Hardware
The firmware targets the nRF52840-DK and won't be made platform-independent for now.
