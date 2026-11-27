#include <iostream>
#include <iomanip>
#include "codec.hpp"
#include "packet.hpp"

int main() {
    std::string message;

    std::cout << "AirLink v0.4.0\n";
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    Packet packet;
    packet.payload = message;

    // Serialize packet
    auto data = serialize(packet);

    std::cout << "\nPacket size: "
              << data.size() << " bytes\n";

    std::cout << "Serialized packet (HEX):\n";

    for (uint8_t byte : data) {
        std::cout << std::hex
                  << std::uppercase
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(byte) << " ";
    }

    std::cout << std::dec << "\n";

    // Deserialize packet
    auto decoded = deserialize(data);

    if (decoded.has_value()) {
        std::cout << "\nPacket successfully decoded!\n";
        std::cout << "Version: "
                  << static_cast<int>(decoded->version)
                  << "\n";
        std::cout << "Payload: "
                  << decoded->payload << "\n";
    } else {
        std::cerr << "Invalid packet!\n";
        return 1;
    }

    return 0;
}

