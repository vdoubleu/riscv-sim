# RISCV Emulator

This is an emulator for the RISCV computer architecture.

This was built in a way to sort of emulate how a computer actually works, and as such the program is split into various parts in a way that follows this methodology.

There is first an input layer that reads in the input.
It will read in the command, clean it, parse it and then assemble it into binary.


Once the data has been assembled, it will be fed into the "cpu" where it will then be disassembled into several groups. The data within the group is then processed so that the cpu knows what to do. It will then update the registers and the memory accordingly.


## Running The Program
The main program only uses base C++ and standard libraries. For easy compilation, make sure you have the `make` utility installed. Simply run `make` in the root directory to compile the program. The binary should be available as `/bin/assembler`. 

To run tests, you will need to have `boost` installed. This application uses the boost test framework for its tests. To build the tests, run `make test`. The test binary should also be available as `/bin/test`.
