#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <optional>

struct Packet {
    uint8_t version = 1;
    std::string payload;
};

std::vector<uint8_t> serialize(const Packet& packet);

std::optional<Packet> deserialize(
    const std::vector<uint8_t>& data
);