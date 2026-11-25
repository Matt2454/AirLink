#include <iostream>
#include "codec.hpp"

int main() {
    std::string message;

    std::cout << "AirLink v0.2.0\n";
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    std::string encoded = encode(message);
    std::string decoded = decode(encoded);

    std::cout << "\nEncoded: " << encoded << "\n";
    std::cout << "Decoded: " << decoded << "\n";

    return 0;
}
