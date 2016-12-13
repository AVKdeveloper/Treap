#include "treap.h"

BinaryTree::Node::Node(const std::pair<int, int>& data_of_node) {
	data_ = data_of_node;
	parent_ = nullptr;
	left_ = nullptr; 
	right_ = nullptr;
}

int BinaryTree::Node::GetHeight() const {
	if (left_ == nullptr && right_ == nullptr) {
		return 1;
	} else {
		return std::max(left_->GetHeight(), right_->GetHeight()) + 1;
	}
}

BinaryTree::BinaryTree() {
	root_ = nullptr;
}

void BinaryTree::AddNode(const std::pair<int, int>& data_of_node) {
	std::shared_ptr<Node> node_ptr(new Node(data_of_node));
	if (root_ == nullptr) {
		root_ = node_ptr;
	} else {
		std::shared_ptr<Node> current_node_ptr;
		std::shared_ptr<Node> next_node_ptr = root_;
		while (next_node_ptr != nullptr) {
			current_node_ptr = next_node_ptr;
			if (node_ptr->data_.first < next_node_ptr->data_.first) {
				next_node_ptr = next_node_ptr->left_;
			} else {
				next_node_ptr = next_node_ptr->right_;
			}
		}
		node_ptr->parent_ = current_node_ptr;
		if (node_ptr->data_.first < current_node_ptr->data_.first) {
			current_node_ptr->left_ = node_ptr;
		} else {
			current_node_ptr->right_ = node_ptr;
		}
	}
}

int BinaryTree::GetHeight() const {
	if (root_ == nullptr) {
		return 0;
	} else {
		return root_->GetHeight();
	}
}