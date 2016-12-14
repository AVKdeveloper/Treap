// Данная библиотека включает в себя класс дерамида.
#ifndef TREAP_H
#define TREAP_H

#include <memory> // shared_ptr 
#include <algorithm>

class Treap {
	struct Node {
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		std::pair<int, int> data_;
	public:
		Node(const std::pair<int, int>& data_of_node);
		int GetHeight() const;
		std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(const int& key, std::shared_ptr<Node> this_);
	};
	std::shared_ptr<Node> root_;
public:
	Treap();
	Treap(std::shared_ptr<Node> node_ptr);
	void NaiveTreeAddNode(const std::pair<int, int>& data_of_node);
	int GetHeight() const;
	std::pair<Treap, Treap> Split(const int& key);
	void Insert(const std::pair<int, int>& data_of_node);

	friend Treap Merge(Treap treap1, Treap treap2);
};

Treap Merge(Treap treap1, Treap treap2);

#endif // TREAP_H