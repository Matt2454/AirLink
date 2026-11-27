#include "crc.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::vector<uint8_t> data = {
        '1', '2', '3', '4', '5',
        '6', '7', '8', '9'
    };

    // Standard CRC-16/CCITT-FALSE test vector
    assert(crc16(data) == 0x29B1);

    // Empty input
    assert(crc16({}) == 0xFFFF);

    // Simulate a single-bit corruption
    auto corrupted = data;
    corrupted[0] ^= 0x01;

    assert(crc16(data) != crc16(corrupted));

    std::cout << "All CRC tests passed!\n";

    return 0;
}