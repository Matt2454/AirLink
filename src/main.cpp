#include <iostream>
#include <string>
#include <bitset>

int main() {
    std::string message;

    std::cout << "AirLink v0.1.0\n";
    std::cout << "Enter message: ";

    std::getline(std::cin, message);

    std::cout << "\nEncoded payload:\n";

    for (unsigned char byte : message) {
        std::cout << std::bitset<8>(byte) << " ";
    }

    std::cout << "\n";

    return 0;
}
