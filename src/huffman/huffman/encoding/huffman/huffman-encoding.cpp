#include "encoding/eof-encoding.h"
#include "data/frequency-table.h"
#include "data/binary-tree.h"
#include <ppltasks.h>
#include <ppltasks.h>
#include "tree-encoding.h"

namespace {
    std::vector<Datum> copy_to_vector(io::InputStream& input) {
        std::vector<Datum> data;

        while (!input.end_reached()) {
            data.push_back(input.read());
        }

        return data;
    }

    int calculate_weight(const data::Node<std::pair<Datum, unsigned>>& tree) {
        assert(&tree != nullptr);

        if (tree.isLeaf()) {
            auto& leaf = static_cast<const data::Leaf<std::pair<Datum, unsigned>>&>(tree);
            assert(&tree != nullptr);
            assert(leaf.getValue().second < 100);
            return leaf.getValue().second;
        }

        int totalWeight = 0;
        auto& branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>&>(tree);

        const auto& leftChild = branch.getLeftChild();
        if (&leftChild != nullptr)
            totalWeight += calculate_weight(leftChild);

        auto& rightChild = branch.getRightChild();
        if (&rightChild != nullptr)
            totalWeight += calculate_weight(rightChild);

        assert(totalWeight < 100);
        return totalWeight;
    }

    struct CustomGreater {
        bool operator()(const std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& a,
            const std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& b) const {
            return calculate_weight(*a) > calculate_weight(*b);
        }
    };

    std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> build_tree(
        const std::shared_ptr<data::FrequencyTable<Datum>>& frequencyTable) {

        std::vector<std::pair<Datum, unsigned>> pairs = frequencyTable->pairs();

        std::vector<std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>> nodeList;
        nodeList.reserve(pairs.size() - 1);
        for (auto pair : pairs) {
            nodeList.push_back(std::make_unique<data::Leaf<std::pair<Datum, unsigned>>>(
                std::pair<Datum, unsigned>(pair.first, pair.second)));
        }

        assert(pairs.size() == nodeList.size());

        while (nodeList.size() > 1) {
            std::sort(nodeList.begin(), nodeList.end(), CustomGreater());
            auto rightLeaf = std::move(nodeList.back());
            nodeList.pop_back();
            assert(rightLeaf != nullptr);

            auto leftLeaf = std::move(nodeList.back());
            nodeList.pop_back();
            assert(leftLeaf != nullptr);

            auto newBranch = std::make_unique<data::Branch<std::pair<Datum, unsigned>>>(std::move(leftLeaf),
                std::move(rightLeaf));
            nodeList.push_back(std::move(newBranch));
        }

        assert(nodeList.size() == 1);
        auto root = std::move(nodeList.at(0));

        return root;
    }

    std::vector<Datum> addBit(const std::vector<Datum>& bits, Datum bit)
    {
        std::vector<Datum> updatedBits = bits;
        updatedBits.push_back(bit);
        return updatedBits;
    }

    void build_vector(const data::Node<Datum>& node, const std::vector<Datum>& bits,
        std::map<Datum, std::vector<Datum>>& codes, unsigned depth)
    {
        if (node.isLeaf())
        {
            auto& currentLeaf = static_cast<const data::Leaf<Datum>&>(node);
            assert(&currentLeaf != nullptr);
            std::vector<Datum> code(bits.end() - depth, bits.end());

            codes.insert(std::pair<Datum, std::vector<Datum>>(currentLeaf.getValue(), bits));
            return;
        }
        else
        {
            const auto& currentBranch = static_cast<const data::Branch<Datum>&>(node);
            assert(&currentBranch != nullptr);
            unsigned newDepth = depth + 1;
            if (&currentBranch.getLeftChild() != nullptr)
                build_vector(currentBranch.getLeftChild(), addBit(bits, 0), codes, newDepth);
            if (&currentBranch.getRightChild() != nullptr)
                build_vector(currentBranch.getRightChild(), addBit(bits, 1), codes, newDepth);
        }
    }

    std::map<Datum, std::vector<Datum>> build_codes(const data::Node<Datum>& root)
    {
        std::map<Datum, std::vector<Datum>> codes;
        std::vector<Datum> bits;
        build_vector(root, bits, codes, 0);
        assert(!codes.empty());
        assert(codes.size() < 1000);
        return codes;
    }

    void encoding(std::map<Datum, std::vector<Datum>>& codes, const std::vector<Datum>& data, io::OutputStream& outputStream)
    {
        for (auto value : data)
        {
            auto bits = codes[value];
            for (auto bit : bits)
            {
                outputStream.write(bit);
            }
        }
    }

    Datum decode_single_datum(io::InputStream& input, const data::Node<Datum>& root)
    {
        assert(!root.isLeaf());
        const data::Node<Datum>* current = &root;

        while (true)
        {
            if (input.end_reached())
            {
                return 0; // Return 0 as the datum when end of stream is reached
            }

            const auto value = input.read();

            if (value == 0)
            {
                current = &static_cast<const data::Branch<Datum>&>(*current).getLeftChild();
            }
            else
            {
                current = &static_cast<const data::Branch<Datum>&>(*current).getRightChild();
            }

            if (current->isLeaf())
            {
                return static_cast<const data::Leaf<Datum>&>(*current).getValue();
            }
        }
    }

    void decode_bits(io::InputStream& input, io::OutputStream& output, const data::Node<Datum>& root)
    {
        int i = 0;
        while (!input.end_reached())
        {
            Datum data = decode_single_datum(input, root);
            output.write(data);
            if (data == 0)
            {
                break;
            }
            i++;
        }
        assert(i > 0);
    }

	class HuffmanEncodingImplementation: public encoding::EncodingImplementation
	{
	private:
        const Datum _domain_size;

	public:

        HuffmanEncodingImplementation(const Datum domain_size) : EncodingImplementation(), _domain_size(domain_size) {}

        void encode(io::InputStream& inputStream, io::OutputStream& outputStream) override
        {

            const auto data = copy_to_vector(inputStream);
            const auto frequencyTable = std::make_shared<data::FrequencyTable<Datum>>();
            for (auto datum : data)
            {
                frequencyTable->increment(datum);
            }


            const auto root = build_tree(frequencyTable);
            auto newroot = data::map<std::pair<Datum, unsigned>, Datum>(*root, [](std::pair<Datum, unsigned> pair) { return pair.first; });
            int actualbits = bits_needed(_domain_size);
            encoding::huffman::encode_tree(*newroot, actualbits, outputStream);

            auto codes = build_codes(*newroot);
            encoding(codes, data, outputStream);

        }

        void decode(io::InputStream& inputStream, io::OutputStream& outputStream) override
        {
            auto root = encoding::huffman::decode_tree(bits_needed(_domain_size), inputStream);
            assert(!root->isLeaf());
            decode_bits(inputStream, outputStream, *root);
        }

	};
}

std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(u64 domain_size)
{
    return std::make_shared<HuffmanEncodingImplementation>(domain_size);
}