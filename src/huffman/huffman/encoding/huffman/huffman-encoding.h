#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "data/binary-tree.h"
#include "encoding/encoding.h"
#include "data/frequency-table.h"
#include "util.h"

std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(u64 domain_size);

namespace encoding
{
	namespace huffman
	{
		template<u64 N>
		encoding::Encoding<N, 2> huffman_encoding()
		{
			auto encoder = Encoding<N, 2>(create_huffman_implementation(N));
			return encoder;
		}
	}
}

#endif