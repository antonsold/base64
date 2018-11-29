#ifndef BASE64_BASE64ENCODERDECODER_H
#define BASE64_BASE64ENCODERDECODER_H

#include <array>
#include <string>

std::string base64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+=";
std::string encodeBuffer(std::array<char, 3> buffer);
std::string base64Encode(const std::string &stringToEncode);

#endif //BASE64_BASE64ENCODERDECODER_H
