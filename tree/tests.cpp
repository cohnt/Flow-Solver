#include "tree.h"

int main() {
	//Test the various Node constructors available.
	Tree<int>::Node* n1 = new Tree<int>::Node();
	Tree<int>::Node* n2 = new Tree<int>::Node(10);
	Tree<int>::Node* n3 = new Tree<int>::Node(n2);
	Tree<int>::Node* n4 = new Tree<int>::Node(n2, 20);
	Tree<int>::Node* n5 = new Tree<int>::Node(n2, 30);
	Tree<int>::Node* n6 = new Tree<int>::Node(n4, 40);

	//Suppress the unused variable warning -- they are being used.
	(void)n3;
	(void)n5;
	(void)n6;

	//Run with valgrind to ensure no memory is leaked
	delete n1;
	delete n2;

	//Test the Tree constructor and destructor
	Tree<int> t1;

	return 0;
}