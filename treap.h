#ifndef TREAP_H
#define TREAP_H

#include <memory> // shared_ptr 
#include <algorithm>

class BinaryTree {
	struct Node {
		std::shared_ptr<Node> parent_;
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		std::pair<int, int> data_;
	public:
		Node(const std::pair<int, int>& data_of_node);
		int GetHeight() const;
	};
	std::shared_ptr<Node> root_;
public:
	BinaryTree();
	void AddNode(const std::pair<int, int>& data_of_node);
	int GetHeight() const;
};


#endif // TREAP_H
