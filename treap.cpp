#include "treap.h"

Treap::Node::Node(const std::pair<int, int>& data_of_node) {
	data_ = data_of_node;
	left_ = nullptr;
	right_ = nullptr;
}

int Treap::Node::GetHeight() const {
	// Рекурсивный обход дерамиды для нахождения наибольшей глубины.
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
	// Разбиение дерамиды на две по заданному ключу.
	// Приходиться передавать в метод указатель this_, т.к. сложно найти другой выход из ситуации, когда необходимо 
	// возвращать неконстантный this.
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

void Treap::NaiveTreeAddNode(const std::pair<int, int>& data_of_node) {
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

Treap Merge(Treap treap1, Treap treap2) {
	// Слияние двух дерамид в одну с сохранением свойств бинарного дерева и пирамиды
	// Операция корректно работает, если все ключи одной поддерамиды < ключей другой
	Treap left_subtreap;
	Treap right_subtreap;
	if (treap1.root_ == nullptr) {
		return treap2;
	} else {
		if (treap2.root_ == nullptr) {
			return treap1;
		}
	}
	// По ключам корней определяем правую и левую поддерамиду
	if (treap1.root_->data_.first < treap2.root_->data_.first) {
		left_subtreap = treap1;
		right_subtreap = treap2;
	} else {
		left_subtreap = treap2;
		right_subtreap = treap1;
	}
	Treap merged_treap;
	// Сливаем с учетом приоритета корней, чтобы выполнялось условие пирамиды
	if (left_subtreap.root_->data_.second > right_subtreap.root_->data_.second) {
		merged_treap.root_ = left_subtreap.root_;
		Treap left_right_subtreap(left_subtreap.root_->right_);
		merged_treap.root_->right_ = Merge(left_right_subtreap, right_subtreap).root_;
	} else {
		merged_treap.root_ = right_subtreap.root_;
		Treap right_left_subtreap(right_subtreap.root_->left_);
		merged_treap.root_->left_ = Merge(right_left_subtreap, left_subtreap).root_;
	}
	return merged_treap;
}

void Treap::Insert(const std::pair<int, int>& data_of_node) {
	// Добавление вершины в дерамиду
	std::shared_ptr<Node> node_ptr(new Node(data_of_node));
	// 1) Находим, куда добавить вершину
	// (идем вниз по дереву, пока приоритет добавочной вершины не станет больше текущего)
	std::shared_ptr<Node> current_node_ptr = nullptr;
	std::shared_ptr<Node> next_node_ptr = root_;
	while (next_node_ptr != nullptr && next_node_ptr->data_.second >= data_of_node.second) {
		current_node_ptr = next_node_ptr;
		if (data_of_node.first < next_node_ptr->data_.first) {
			next_node_ptr = next_node_ptr->left_;
		} else {
			next_node_ptr = next_node_ptr->right_;
		}
	}
	// 2) Разбиваем найденное поддерево по ключу добавленной вершины
	// Получившиеся два дерева делаем дочерними для добавленной вершины
	if (current_node_ptr != nullptr) {
		if (data_of_node.first < current_node_ptr->data_.first) {
			current_node_ptr->left_ = node_ptr;
		}
		else {
			current_node_ptr->right_ = node_ptr;
		}
	} else {
		root_ = node_ptr;
	}
	if (next_node_ptr != nullptr) {
		std::pair<Treap, Treap> split_treaps = next_node_ptr->Split(data_of_node.first, next_node_ptr);
		node_ptr->left_ = split_treaps.first.root_;
		node_ptr->right_ = split_treaps.second.root_;
	}
	// Функция Merge при данном добавлении вообще не используется
}