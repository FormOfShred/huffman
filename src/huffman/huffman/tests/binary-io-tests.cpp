#ifdef TEST_BUILD
#include "catch.hpp"
#include "util.h"
#include "io/memory-buffer.h"
#include "io/binary-io.h"

namespace
{
    void check(u64 n, unsigned nbits)
    {
        io::MemoryBuffer<2> buffer;
        auto input = buffer.source()->create_input_stream();
        auto output = buffer.destination()->create_output_stream();
        io::write_bits(n, nbits, *output);
        auto result = io::read_bits(nbits, *input);

        REQUIRE(n == result);
    }
}

TEST_CASE("Write/Read bits with 1-bit values") {
    check(0, 1);
    check(1, 1);
}

TEST_CASE("Write/Read bits with 2-bit values") {
    check(0, 2);
    check(1, 2);
    check(2, 2);
    check(3, 2);
}

TEST_CASE("Write/Read bits with 8-bit values") {
    check(0, 8);
    check(1, 8);
    check(42, 8);
    check(255, 8);
}

#endif