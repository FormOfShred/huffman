#include "encoding.h"
#include "io/binary-io.h"

namespace
{
	class BitGrouperImplementation : public encoding::EncodingImplementation
	{
	private:
		u64 _group_size;

	public:
		BitGrouperImplementation(u64 group_size) : _group_size(group_size) { }

		void encode(io::InputStream& input, io::OutputStream& output) override
		{
			while (!input.end_reached())
			{
				u64 data = io::read_bits(_group_size, input);
				output.write(data);
			}
		}

		void decode(io::InputStream& input, io::OutputStream& output) override
		{
			while (!input.end_reached())
			{
				u64 data = input.read();
				io::write_bits(data, _group_size, output);
			}
		}
	};

}

std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(u64 group_size)
{
	return std::make_shared<BitGrouperImplementation>(group_size);
}