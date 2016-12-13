#include "treap.h"

Treap::Node::Node(const std::pair<int, int>& data_of_node) {
	data_ = data_of_node;
	left_ = nullptr;
	right_ = nullptr;
}

int Treap::Node::GetHeight() const {
	int left_height;
	int right_height;
	if (left_ == nullptr) {
		left_height = 0;
	}
	else {
		left_height = left_->GetHeight();
	}
	if (right_ == nullptr) {
		right_height = 0;
	}
	else {
		right_height = right_->GetHeight();
	}
	return std::max(left_height, right_height) + 1;
}

std::pair<std::shared_ptr<Treap::Node>, std::shared_ptr<Treap::Node>> Treap::Node::Split(const int& key, 
	                                                                                    std::shared_ptr<Node> this_) {
	std::shared_ptr<Node> left_node_ptr;
	std::shared_ptr<Node> right_node_ptr;
	if (data_.first < key) {
		if (right_ != nullptr) {
			std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> new_nodes_ptr = right_->Split(key, right_);
			left_node_ptr = new_nodes_ptr.first;
			right_node_ptr = new_nodes_ptr.second;
		}
		right_ = left_node_ptr;
		return { this_, right_node_ptr };
	} else {
		if (left_ != nullptr) {
			std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> new_nodes_ptr = left_->Split(key, left_);
			left_node_ptr = new_nodes_ptr.first;
			right_node_ptr = new_nodes_ptr.second;
		}
		left_ = right_node_ptr;
		return{ left_node_ptr, this_ };
	}
}

Treap::Treap() {
	root_ = nullptr;
}

Treap::Treap(std::shared_ptr<Node> node_ptr) {
	root_ = node_ptr;
}

void Treap::AddNode(const std::pair<int, int>& data_of_node) {
	std::shared_ptr<Node> node_ptr(new Node(data_of_node));
	if (root_ == nullptr) {
		root_ = node_ptr;
	}
	else {
		std::shared_ptr<Node> current_node_ptr;
		std::shared_ptr<Node> next_node_ptr = root_;
		while (next_node_ptr != nullptr) {
			current_node_ptr = next_node_ptr;
			if (node_ptr->data_.first < next_node_ptr->data_.first) {
				next_node_ptr = next_node_ptr->left_;
			}
			else {
				next_node_ptr = next_node_ptr->right_;
			}
		}
		if (node_ptr->data_.first < current_node_ptr->data_.first) {
			current_node_ptr->left_ = node_ptr;
		}
		else {
			current_node_ptr->right_ = node_ptr;
		}
	}
}

int Treap::GetHeight() const {
	if (root_ == nullptr) {
		return 0;
	}
	else {
		return root_->GetHeight();
	}
}

std::pair<Treap, Treap> Treap::Split(const int& key) {
	std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> new_nodes = root_->Split(key, root_);
	Treap left_treap(new_nodes.first);
	Treap right_treap(new_nodes.second);
	return{ left_treap, right_treap };
}