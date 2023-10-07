#include "io/streams.h"
#include "data/binary-tree.h"
#include "tree-encoding.h"
#include "io/binary-io.h"

namespace encoding{
	namespace huffman {
		void encoding::huffman::encode_tree(const data::Node<Datum>& root, Datum size, io::OutputStream& output)
		{
			if (root.isLeaf())
			{
				const data::Leaf<Datum>& leaf = dynamic_cast<const data::Leaf<Datum>&>(root);
				output.write(0);
				io::write_bits(leaf.getValue(), size, output);
			}
			else 
			{
				output.write(1);
				auto& branch = static_cast<const data::Branch<Datum>&>(root);
				encode_tree(branch.getLeftChild(), size, output);
				encode_tree(branch.getRightChild(), size, output);
			}
		}

		std::unique_ptr<data::Node<Datum>> decode_tree(Datum bits, io::InputStream& input)
		{
			if (input.read() == 0)
			{
				Datum data = io::read_bits(bits, input);
				return std::make_unique<data::Leaf<Datum>>(data);
			}
			else
			{
				std::unique_ptr<data::Node<Datum>> leftNode = decode_tree(bits, input);
				std::unique_ptr<data::Node<Datum>> rightNode = decode_tree(bits, input);
				return std::make_unique<data::Branch<Datum>>(std::move(leftNode), std::move(rightNode));
			}
		}
	}
}