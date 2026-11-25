#include "codec.hpp"
#include <bitset>

std::string encode(const std::string& message) {
    std::string bits;

    for (unsigned char byte : message) {
        bits += std::bitset<8>(byte).to_string();
    }

    return bits;
}

std::string decode(const std::string& bits) {
    std::string message;

    if (bits.size() % 8 != 0 ||
        bits.find_first_not_of("01") != std::string::npos) {
        return "";
    }

    for (size_t i = 0; i < bits.size(); i += 8) {
        std::bitset<8> byte(bits.substr(i, 8));
        message += static_cast<char>(byte.to_ulong());
    }

    return message;
}