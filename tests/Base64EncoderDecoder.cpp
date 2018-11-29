#include "Base64EncoderDecoder.h"
#include <iostream>

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