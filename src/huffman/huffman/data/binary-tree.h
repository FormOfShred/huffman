#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <functional>
#include <cassert>

namespace data
{
	template <typename T>
	class Node
	{
	public:
		virtual ~Node() {};
		virtual bool isLeaf() const 
		{
			return false;
		}
	};

	template <typename T>
	class Branch : public Node<T>
	{
	private:
		std::unique_ptr<Node<T>> _left_child;
		std::unique_ptr<Node<T>> _right_child;

	public:
		Branch(std::unique_ptr<Node<T>> left_child, std::unique_ptr<Node<T>> right_child) :
			_left_child(std::move(left_child)), _right_child(std::move(right_child))
		{
			// EMPTY EXCEPT FOR ASSERTIONS
			assert(_left_child != nullptr && _right_child != nullptr);
		}

		 const Node<T>& getLeftChild() const 
		 {
			 return *_left_child;
		 }

		 const Node<T>& getRightChild() const
		 {
			 return *_right_child;
		 }

		 bool isLeaf() const override
		 {
			 return false;
		 }
	};

	template <typename T>
	class Leaf : public Node<T>
	{
	private:
		const T _value;

	public:
		Leaf(const T& value) : _value(value) 
		{
			// EMPTY
		}
		const T& getValue() const
		{
			return _value;
		}

		bool isLeaf() const override
		{
			return true;
		}
	};

	template<typename IN, typename OUT>
	std::unique_ptr<Node<OUT>> map(const Node<IN>& tree, std::function<OUT(const IN&)> function)
	{
		if (dynamic_cast<const Leaf<IN>*>(&tree)) {
			const auto& L = static_cast<const Leaf<IN>&>(tree);
			return std::make_unique<Leaf<OUT>>(function(L.getValue()));
		}
		else {
			const auto& B = static_cast<const Branch<IN>&>(tree);
			auto new_left_child = map<IN, OUT>(B.getLeftChild(), function);
			auto new_right_child = map<IN, OUT>(B.getRightChild(), function);
			return std::make_unique<Branch<OUT>>(std::move(new_left_child), std::move(new_right_child));
		}
	}

}

#endif