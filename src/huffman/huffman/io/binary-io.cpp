#include "util.h"
#include "streams.h"
#include "binary-io.h"

namespace io
{
	u64 read_bits(unsigned nbits, io::InputStream& input)
	{
        u64 bits = 0;
        unsigned bits_read = 0;
        while (bits_read < nbits && !input.end_reached()) {
            bits = (bits << 1) | input.read();
            bits_read++;
        }
        while (bits_read < nbits) {
            bits = (bits << 1);
            bits_read++;
        }
        return bits;
	}

    void write_bits(u64 value, unsigned nbits, OutputStream& output) {
        for (int i = nbits - 1; i >= 0; --i) {
            u64 bit = (value >> i) & 1;
            output.write(bit);
        }
    }

}