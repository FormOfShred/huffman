#ifdef TEST_BUILD

#include "catch.hpp"
#include "../data/binary-tree.h"

/*TEST_CASE("Branch test")
{
	auto left_child = std::make_unique<data::Leaf<int>>(1);
	auto right_child = std::make_unique<data::Leaf<int>>(2);
	data::Branch<int> branch(std::move(left_child), std::move(right_child));
	const auto& left_child_ref = static_cast<const data::Leaf<int>&>(branch.getLeftChild());
	const auto& right_child_ref = static_cast<const data::Leaf<int>&>(branch.getRightChild());
	REQUIRE(left_child_ref.getValue() == 1);
	REQUIRE(right_child_ref.getValue() == 2);
}

TEST_CASE("Leaf test")
{
	data::Leaf<int> leaf(1);
	REQUIRE(leaf.getValue() == 1);
}

TEST_CASE("Map test")
{
    data::Leaf<int> leaf(1);
    std::function<double(const int&)> int_to_double = [](const int& x) { return static_cast<double>(x); };
    auto mapped_leaf = data::map<int, double>(leaf, int_to_double);
    const auto& casted_mapped_leaf = static_cast<const data::Leaf<double>&>(*mapped_leaf);
    REQUIRE(casted_mapped_leaf.getValue() == 1);

    auto left_child = std::make_unique<data::Leaf<int>>(1);
    auto right_child = std::make_unique<data::Leaf<int>>(2);
    data::Branch<int> branch(std::move(left_child), std::move(right_child));
    auto mapped_branch = data::map<int, double>(branch, int_to_double);
    const auto& casted_mapped_branch = static_cast<const data::Branch<double>&>(*mapped_branch);
    const auto& left_child_ref = static_cast<const data::Leaf<double>&>(casted_mapped_branch.getLeftChild());
    const auto& right_child_ref = static_cast<const data::Leaf<double>&>(casted_mapped_branch.getRightChild());
    REQUIRE(left_child_ref.getValue() == 1);
    REQUIRE(right_child_ref.getValue() == 2);
}*/

#endif