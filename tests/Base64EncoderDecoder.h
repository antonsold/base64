#ifndef BASE64_BASE64ENCODERDECODER_H
#define BASE64_BASE64ENCODERDECODER_H

#include <array>
#include <string>

std::string encodeBuffer(std::array<char, 3> buffer);
std::string base64Encode(const std::string &stringToEncode);
bool isBase64String(std::string stringToCheck);
std::string decodeBuffer(std::array<char, 4> buffer);
std::string base64Decode(std::string stringToDecode);

#endif //BASE64_BASE64ENCODERDECODER_H
