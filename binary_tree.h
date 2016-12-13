#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory> // shared_ptr 
#include <algorithm>

class BinaryTree {
	struct Node {
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		int data_;
	public:
		Node(const int& data_of_node);
		int GetHeight() const;
	};
	std::shared_ptr<Node> root_;
public:
	BinaryTree();
	void AddNode(const int& data_of_node);
	int GetHeight() const;
};

#endif // BINARY_TREE_H