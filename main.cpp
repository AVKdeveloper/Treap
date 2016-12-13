#include <fstream>
#include "treap.h"

int main() {
	std::fstream file;
	file.open("input.txt", std::fstream::in);
	int quantity_of_nodes;
	file >> quantity_of_nodes;
	BinaryTree tree;
	std::pair<int, int> data_of_node;
	for (int i = 0; i < quantity_of_nodes; ++i) {
		file >> data_of_node.first >> data_of_node.second;

	}
	return 0;
}