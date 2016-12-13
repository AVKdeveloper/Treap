#include "binary_tree.h"

BinaryTree::Node::Node(const std::pair<int, int>& data_of_node) {
	data_ = data_of_node;
	parent_ = nullptr;
	left_ = nullptr; 
	right_ = nullptr;
}

int BinaryTree::Node::GetHeight() const {
	int left_height;
	int right_height;
	if (left_ == nullptr) {
		left_height = 0;
	} else {
		left_height = left_->GetHeight();
	}
	if (right_ == nullptr) {
		right_height = 0;
	} else {
		right_height = right_->GetHeight();
	}
	return std::max(left_height, right_height) + 1;
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