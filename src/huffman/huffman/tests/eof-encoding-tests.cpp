#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/eof-encoding.h"
#include "io/memory-buffer.h"


/*TEST_CASE("Memory buffer stream")
{
    auto original_data = std::make_shared<std::vector<Datum>>();
    original_data->push_back(0);
    original_data->push_back(1);
    original_data->push_back(2);
    original_data->push_back(3);

    auto input_stream = io::create_memory_input_stream(original_data);
    auto data_receiver = std::make_shared<std::vector<Datum>>();
    auto output_stream = io::create_memory_output_stream(data_receiver);
}

TEST_CASE("Memory buffer")
{
    io::MemoryBuffer<10> inbuffer;
    auto data = inbuffer.destination()->create_output_stream();
    data->write(1);
    data->write(2);
    data->write(3);
    data->write(4);
    data->write(5);
    data->write(6);
    data->write(7);
    data->write(8);
    data->write(9);
    data->write(10);

    io::MemoryBuffer<11> outbuffer;

    auto source = inbuffer.source();
    auto destination = outbuffer.destination();
    auto encoding = encoding::eof_encoding<10>();

    encoding::encode<10, 11>(source, destination, encoding);
}

TEST_CASE("2 buffers | 3 values in | should end up at 4")
{
    io::MemoryBuffer<20> buffer1_20_encode;
    buffer1_20_encode.data()->push_back(0);
    buffer1_20_encode.data()->push_back(1);
    buffer1_20_encode.data()->push_back(2);
    io::MemoryBuffer<21> buffer2_21_encode;
    const auto test = encoding::eof_encoding<20>();
    encode(buffer1_20_encode.source(), buffer2_21_encode.destination(), test);     REQUIRE(buffer1_20_encode.data()->size() == buffer2_21_encode.data()->size() - 1);
}*/

#endif