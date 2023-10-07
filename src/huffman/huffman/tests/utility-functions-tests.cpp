#ifdef TEST_BUILD
#include "catch.hpp"
#include "../util.h"
#include <type_traits>

/*TEST_CASE("Bits_needed test")
{
    REQUIRE(bits_needed(2) == 1);
    REQUIRE(bits_needed(3) == 2);
    REQUIRE(bits_needed(4) == 2);
    REQUIRE(bits_needed(5) == 3);
    REQUIRE(bits_needed(6) == 3);
    REQUIRE(bits_needed(7) == 3);
    REQUIRE(bits_needed(8) == 3);
    REQUIRE(bits_needed(9) == 4);
    REQUIRE(bits_needed(128) == 7);
    REQUIRE(bits_needed(129) == 8);
    REQUIRE(bits_needed(1000000) == 20);
}

TEST_CASE("Bytes_needed test")
{
    REQUIRE(bytes_needed(2) == 1);
    REQUIRE(bytes_needed(128) == 1);
    REQUIRE(bytes_needed(129) == 1);
    REQUIRE(bytes_needed(255) == 1);
    REQUIRE(bytes_needed(256) == 1);
    REQUIRE(bytes_needed(257) == 2);
    REQUIRE(bytes_needed(1000000) == 3);
}

void test_types()
{
#define CHECK_TYPE(N, TYPE) static_assert(std::is_same<SelectIntegerTypeByBytes<N>::type, TYPE>::value, "SelectIntegerTypeByBytes<" #N "> is not " #TYPE)
    CHECK_TYPE(1, uint8_t);
    CHECK_TYPE(2, uint16_t);
    CHECK_TYPE(3, uint32_t);
    CHECK_TYPE(4, uint32_t);
    CHECK_TYPE(5, uint64_t);
    CHECK_TYPE(6, uint64_t);
    CHECK_TYPE(7, uint64_t);
    CHECK_TYPE(8, uint64_t);
#undef CHECK_TYPE

#define CHECK_TYPE(N, TYPE) static_assert(std::is_same<SelectIntegerTypeByDomainSize<N>::type, TYPE>::value, "SelectIntegerTypeByDomainSize<" #N "> is not " #TYPE)
    CHECK_TYPE(2, uint8_t);
    CHECK_TYPE(255, uint8_t);
    CHECK_TYPE(256, uint8_t);
    CHECK_TYPE(65535, uint16_t);
    CHECK_TYPE(65536, uint16_t);
    CHECK_TYPE(65537, uint32_t);
    CHECK_TYPE(4294967295, uint32_t);
    CHECK_TYPE(4294967296, uint32_t);
    CHECK_TYPE(4294967297, uint64_t);
#undef CHECK_TYPE
}*/

#endif