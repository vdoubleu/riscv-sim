#ifndef ERRORS_CPP
#define ERRORS_CPP
class unexpectedCommandType {};

class unexpectedCommandName{};
class unexpectedRCommand: unexpectedCommandName {};

class unrecognisedValue{};
class unrecognisedImm : unrecognisedValue{};
class unrecognisedReg : unrecognisedValue{};

class invalidBranchImmediate{};

class unrecognisedOpCode{};
#endif
