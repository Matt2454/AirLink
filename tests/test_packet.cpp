#include "packet.hpp"
#include <cassert>
#include <iostream>

int main() {
    Packet packet;
    packet.payload = "Hello";

    auto data = serialize(packet);

    // Verify packet structure
    assert(data.size() == 8);
    assert(data[0] == 1);
    assert(data[1] == 0);
    assert(data[2] == 5);

    // Verify round-trip
    auto decoded = deserialize(data);

    assert(decoded.has_value());
    assert(decoded->version == 1);
    assert(decoded->payload == "Hello");

    // Invalid packets
    assert(!deserialize({}).has_value());
    assert(!deserialize({1, 0}).has_value());
    assert(!deserialize({2, 0, 0}).has_value());
    assert(!deserialize({1, 0, 5, 65}).has_value());

    // Empty payload
    Packet empty;
    auto result = deserialize(serialize(empty));

    assert(result.has_value());
    assert(result->payload.empty());

    std::cout << "All packet tests passed!\n";

    return 0;
}