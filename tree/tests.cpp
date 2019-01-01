#include "tree.h"
#include <cassert>

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

	//Test adding children to a node.
	Tree<int>::Node* n7 = new Tree<int>::Node(1);
	n7->addChild();
	Tree<int>::Node* n8 = n7->addChild(5);
	n8->addChild(10);

	//Run with valgrind to ensure no memory is leaked
	delete n7;

	//Test deleting children manually in various ways
	Tree<int>::Node* n9 = new Tree<int>::Node(1);
	n9->addChild(1);
	n9->addChild(2);
	n9->addChild(3);
	n9->addChild(4);
	Tree<int>::Node* n10 = n9->addChild(5);
	n10->addChild(100);
	n10->addChild(200);
	n9->addChild(43);

	n9->deleteFirstChild();
	n9->deleteNthChild(2);
	n9->deleteLastChild();

	//Run with valgrind to ensure no memory is leaked
	delete n9;

	//Test the Tree constructor and destructor
	Tree<int> t1;

	return 0;
}