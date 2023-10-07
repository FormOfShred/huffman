#ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H

#include "util.h"
#include "encoding.h"

namespace encoding
{
	template<u64 N1, u64 N2, u64 N3>
	class EncodingCombinerImplementation : public encoding::EncodingImplementation
	{
	private:
		const Encoding<N1, N2> E1;
		const Encoding<N2, N3> E2;
	public:
		EncodingCombinerImplementation(const Encoding<N1, N2>E1, const Encoding<N2, N3> E2) : E1(E1), E2(E2) { }

		void encode(io::InputStream& input, io::OutputStream& output) override
		{
			auto temp_buffer = io::MemoryBuffer<N1, u64>();
			auto out = temp_buffer.destination()->create_output_stream();
			auto in = temp_buffer.source()->create_input_stream();
			E1->encode(input, *out);
			E2->encode(*in, output);
		}

		void decode(io::InputStream& input, io::OutputStream& output) override
		{
			auto temp_buffer = io::MemoryBuffer<N1, u64>();
			auto out = temp_buffer.destination()->create_output_stream();
			auto in = temp_buffer.source()->create_input_stream();
			E2->decode(input, *out);
			E1->decode(*in, output);

		}
	};

	template<u64 N1, u64 N2, u64 N3>
	encoding::Encoding<N1, N3> operator | (const Encoding<N1, N2>E1, const Encoding<N2, N3> E2)
	{
		auto encodercombiner = std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(E1, E2);
		return Encoding<N1, N3>(encodercombiner);
	}
}

#endif
