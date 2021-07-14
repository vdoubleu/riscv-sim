#include <array>
#include <string>
#include <bitset>
#include "util.h"

std::array<bool, 32> util::bitStringToBitArr(std::string bitString) {
  std::array<bool, 32> bitArr;

  for (size_t pos = 0; pos < bitString.length(); ++pos) {
    bitArr[pos] = (bitString.at(pos) == '1');
  }

  return bitArr;
}

std::array<bool, 32> util::numToBitArr(int num) {
  return bitStringToBitArr(std::bitset<32>(num).to_string());
}

std::string util::bitArrToBitString(std::array<bool, 32> bitArr) {
  std::vector<bool> bitVec(bitArr.begin(), bitArr.end());

  return bitArrToBitString(bitVec);
}

std::string util::bitArrToBitString(std::vector<bool> bitVec) {
  std::string bitStr = "";

  for (bool b : bitVec)
    bitStr += b ? "1" : "0";

  return bitStr;
}

int util::signedBitArrToNum(std::vector<bool> bitVec) {
  return signedBitStringToNum(bitArrToBitString(bitVec));
}

std::size_t util::unsignedBitArrToNum(std::vector<bool> bitVec) {
  return unsignedBitStringToNum(bitArrToBitString(bitVec));
}

int util::signedBitStringToNum(std::string bitStr) {
  if (bitStr.length() == 1)
    return bitStr == "1" ? 1 : 0;
  else if (bitStr.length() == 0)
    return 0;
  
  int currVal = 0;
  int currPower = 1;
  for (std::size_t bInd = 0; bInd < bitStr.length() - 1; ++bInd) {
    if (bitStr.at(bitStr.length() - bInd - 1) == '1')
      currVal += currPower;
    currPower *= 2;
  }

  if (bitStr.at(0) == '1')
    currVal -= currPower;

  return currVal;
}

std::size_t util::unsignedBitStringToNum(std::string bitStr) {
  return std::stoi(bitStr, nullptr, 2);
}
