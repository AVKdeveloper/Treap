// Эта программа выводит разницу высот обычного бинарного дерева поиска и дерамиды.

#include <fstream>
#include "binary_tree.h"
#include "treap.h"

int main() {
	std::fstream file;
	file.open("input.txt", std::fstream::in);
	int quantity_of_nodes;
	file >> quantity_of_nodes;
	BinaryTree tree;
	Treap treap;
	std::pair<int, int> data_of_node;
	for (int i = 0; i < quantity_of_nodes; ++i) {
		file >> data_of_node.first >> data_of_node.second;
		tree.AddNode(data_of_node.first);
		treap.Insert(data_of_node);
	}
	file.close();
	int height_tree = tree.GetHeight();
	int height_treap = treap.GetHeight();
	file.open("output.txt", std::fstream::out);
	file << height_tree - height_treap;
	file.close();
	return 0;
}