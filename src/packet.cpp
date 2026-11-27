#include "packet.hpp"
#include "crc.hpp"
#include <stdexcept>

std::vector<uint8_t> serialize(const Packet& packet) {
    if (packet.payload.size() > 65535) {
        throw std::length_error("Payload too large");
    }

    std::vector<uint8_t> data;
    uint16_t length = static_cast<uint16_t>(
        packet.payload.size()
    );

    // Header
    data.push_back(packet.version);
    data.push_back(static_cast<uint8_t>(length >> 8));
    data.push_back(static_cast<uint8_t>(length & 0xFF));

    // Payload
    data.insert(data.end(),
                packet.payload.begin(),
                packet.payload.end());

    // CRC-16
    uint16_t checksum = crc16(data);

    data.push_back(static_cast<uint8_t>(checksum >> 8));
    data.push_back(static_cast<uint8_t>(checksum & 0xFF));

    return data;
}

std::optional<Packet> deserialize(
    const std::vector<uint8_t>& data
) {
    if (data.size() < 5) {
        return std::nullopt;
    }

    if (data[0] != 2) {
        return std::nullopt;
    }

    uint16_t length =
        (static_cast<uint16_t>(data[1]) << 8) |
        data[2];

    if (data.size() != 5u + length) {
        return std::nullopt;
    }

    // Extract received CRC
    uint16_t receivedCRC =
        (static_cast<uint16_t>(data[data.size() - 2]) << 8) |
        data.back();

    // Calculate expected CRC
    std::vector<uint8_t> content(
        data.begin(), data.end() - 2
    );

    if (crc16(content) != receivedCRC) {
        return std::nullopt;
    }

    Packet packet;
    packet.version = data[0];
    packet.payload.assign(
        data.begin() + 3, data.end() - 2
    );

    return packet;
}

