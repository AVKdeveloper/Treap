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
		treap.AddNode(data_of_node);
	}
	int height = tree.GetHeight();
	std::pair<Treap, Treap> treaps = treap.Split(25);
	return 0;
}