#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <array>

class util {
  public:
    std::array<bool, 32> bitStringToBitArr(std::string bitString);
    std::array<bool, 32> numToBitArr(int num);
    std::string bitArrToBitString(std::array<bool, 32> bitArr);
    std::string bitArrToBitString(std::vector<bool> bitVec);
    int signedBitArrToNum(std::vector<bool> bitVec);
    std::size_t unsignedBitArrToNum(std::vector<bool> bitVec);
    int signedBitStringToNum(std::string bitStr);
    std::size_t unsignedBitStringToNum(std::string bitStr);
};
#endif
