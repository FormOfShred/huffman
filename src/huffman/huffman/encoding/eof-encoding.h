#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H

#include <util.h>
#include "encoding.h"

// declare before to be used
std::shared_ptr<encoding::EncodingImplementation> create_eof_implementation(u64 domain_size);

namespace encoding
{
	template<u64 N>
	encoding::Encoding<N, N + 1> eof_encoding()
	{
		auto encoder = Encoding<N, N + 1>(create_eof_implementation(N));
		return encoder;
	}
}

#endif
