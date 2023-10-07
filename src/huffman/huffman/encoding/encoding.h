#ifndef ENCODING_H
#define ENCODING_H

#include "io/memory-buffer.h"

namespace encoding
{
	class EncodingImplementation
	{
	public:
		virtual ~EncodingImplementation() 
		{
			// EMPTY
		}

		virtual void encode(io::InputStream& input, io::OutputStream& output)
		{
			// EMPTY
		}
		virtual void decode(io::InputStream& input, io::OutputStream& output) 
		{
			// EMPTY
		}
	};

	template<u64 IN, u64 OUT>
	class Encoding 
	{
	private:
		std::shared_ptr<EncodingImplementation> _implementation;

	public:
		Encoding(std::shared_ptr<EncodingImplementation> implementation) : _implementation(implementation)
		{
			// EMPTY
		}

		const std::shared_ptr<EncodingImplementation> operator -> () const
		{
			return _implementation;
		}

		std::shared_ptr<EncodingImplementation> operator -> ()
		{
			return _implementation;
		}
	};

	template<u64 IN, u64 OUT>
	void encode(io::DataSource<IN> source, io::DataDestination<OUT> destination, Encoding<IN, OUT> encoding)
	{
		auto input_stream = source->create_input_stream();
		auto output_stream = destination->create_output_stream();
		encoding->encode(*input_stream, *output_stream);
	};

	template<u64 IN, u64 OUT>
	void decode(io::DataSource<IN> source, io::DataDestination<OUT> destination, Encoding<IN, OUT> encoding)
	{
		auto input_stream = source->create_input_stream();
		auto output_stream = destination->create_output_stream();
		encoding->decode(*input_stream, *output_stream);
	};
}

#endif