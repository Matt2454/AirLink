#include "packet.hpp"
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

    // Payload length (big-endian)
    data.push_back(static_cast<uint8_t>(length >> 8));
    data.push_back(static_cast<uint8_t>(length & 0xFF));

    // Payload
    data.insert(data.end(),
                packet.payload.begin(),
                packet.payload.end());

    return data;
}

std::optional<Packet> deserialize(
    const std::vector<uint8_t>& data
) {
    if (data.size() < 3) {
        return std::nullopt;
    }

    if (data[0] != 1) {
        return std::nullopt;
    }

    uint16_t length =
        (static_cast<uint16_t>(data[1]) << 8) |
        data[2];

    if (data.size() != 3u + length) {
        return std::nullopt;
    }

    Packet packet;
    packet.version = data[0];
    packet.payload.assign(data.begin() + 3, data.end());

    return packet;
}