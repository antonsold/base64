#include "Base64EncoderDecoder.h"
#include <iostream>
#include <stdexcept>

std::string base64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+=";

std::string encodeBuffer(std::array<char, 3> buffer) {
    std::string decodedBuffer(4, ' ');
    decodedBuffer[0] = base64Alphabet[buffer[0] >> 2];
    decodedBuffer[1] = base64Alphabet[(buffer[0] & 3u) << 4 | buffer[1] >> 4];
    decodedBuffer[2] = base64Alphabet[buffer[1] == 0 ? 63 : (buffer[1] & 15u) << 2 | buffer[2] >> 6];
    decodedBuffer[3] = base64Alphabet[buffer[2] == 0 ? 63 : buffer[2] & 63u];
    return decodedBuffer;
}

std::string base64Encode(const std::string &stringToEncode) {
    std::array<char, 3> buffer({});
    std::string encodedString;
    unsigned position = 0;
    for (; position < stringToEncode.length() - stringToEncode.length() % 3; position += 3) {
        for (int i = 0; i < 3; ++i) {
            buffer[i] = stringToEncode[position + i];
        }
        encodedString += encodeBuffer(buffer);
    }
    if (position < stringToEncode.length()) {
        for (int i = 0; i < 3; ++i) {
            buffer[i] =
                    position + i < stringToEncode.length() ? stringToEncode[position + i] : static_cast<char>(0);
        }
        encodedString += encodeBuffer(buffer);
    }
    return encodedString;
}

bool isBase64String(std::string stringToCheck){
    for(char c : stringToCheck) {
        if (!(isalnum(c) || c == '+' || c == '='))
            return false;
    }
    return true;
}

std::string decodeBuffer(std::array<char, 4> buffer) {
    std::array<size_t ,4> indexInAlphabet = {};
    unsigned countEndEqSigns = 0;
    for(int i = 0; i < 4; ++i) {
        indexInAlphabet[i] = base64Alphabet.find(buffer[i]);
        if (indexInAlphabet[i] == 63 && i > 1)
            ++countEndEqSigns;
    }
    std::string decodedString;
    decodedString += static_cast<char>((indexInAlphabet[0] << 2) | (indexInAlphabet[1] >> 4));
    if (countEndEqSigns < 2) {
        decodedString += static_cast<char>(((indexInAlphabet[1] & 15) << 4 | indexInAlphabet[2] >> 2));
    }
    if (countEndEqSigns == 0) {
        decodedString += static_cast<char>(((indexInAlphabet[2] & 3) << 6 | indexInAlphabet[3]));
    }
    return decodedString;
}

std::string base64Decode(std::string stringToDecode) {
    if (!isBase64String(stringToDecode))
        throw std::invalid_argument("String is not Base64");
    std::array<char, 4> buffer({});
    std::string decodedString;
    unsigned position = 0;
    for (; position < stringToDecode.length() - stringToDecode.length() % 4; position += 4) {
        for (int i = 0; i < 4; ++i) {
            buffer[i] = stringToDecode[position + i];
        }
        decodedString += decodeBuffer(buffer);
    }
    return decodedString;
}