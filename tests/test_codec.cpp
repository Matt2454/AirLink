#include "codec.hpp"
#include <iostream>
#include <cassert>

int main() {
    assert(encode("A") == "01000001");
    assert(decode("01000001") == "A");

    assert(decode(encode("hello world")) == "hello world");
    assert(decode(encode("hewwo :3")) == "hewwo :3");

    assert(encode("").empty());
    assert(decode("010").empty());
    assert(decode("abcdefgh").empty());

    std::cout << "All codec tests passed!\n";

    return 0;
}