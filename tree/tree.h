#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <list>
#include <algorithm>

template <typename T> class Tree {
public:
	struct Node {
		friend class Tree;
	private:
		std::list<Node*> children;
		Node* parent;

		Node(const Node &);
		Node& operator=(const Node &);

	public:
		T datum;

		Node();
		Node(T);
		Node(Node*);
		Node(Node*, T);
		~Node();
	};

private:
	Node* root;

	Tree(const Tree &);
	Tree& operator=(const Tree &);

	size_t sizeHelper(Node*) const;
	size_t heightHelper(Node*) const;

public:
	Tree();
	~Tree();

	size_t size() const;
	size_t height() const;

	Node* getRoot() const;
	Node* addChild(Node*, T);
	
	bool deleteFirstChild(Node*);
	bool deleteLastChild(Node*);
	bool deleteNthChild(Node*, size_t n);

	Node* getParent(Node*) const;

	size_t numChildren(Node*) const;
	Node* firstChild(Node*) const;
	Node* lastChild(Node*) const;
	Node* nthChild(Node*, size_t n) const;
};


/////////////////////////
// Node
/////////////////////////

//Root, default value constructor
template <typename T>
Tree<T>::Node::Node() : children(), parent(nullptr), datum() {
	// Do nothing
	//
}

//Root, given value constructor
template <typename T>
Tree<T>::Node::Node(T t) : children(), parent(nullptr), datum(t) {
	// Do nothing
	//
}

//Child, default value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr) : children(), parent(ptr), datum() {
	parent->children.emplace_back(this);
	//
}

//Child, given value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr, T t) : children(), parent(ptr), datum(t) {
	parent->children.emplace_back(this);
	//
}

//Destructor
template <typename T>
Tree<T>::Node::~Node() {
	//Recursively delete all children
	while(!children.empty()) {
		delete children.front(); //Delete the Node, freeing up the dynamic memory
		children.pop_front(); //Remove the Node from children
	}
}

//Copy constructor and assignment operator. These are private so that they can't be used.
template <typename T>
Tree<T>::Node::Node(const Tree<T>::Node & node) {}

template <typename T>
typename Tree<T>::Node& Tree<T>::Node::operator=(const typename Tree<T>::Node & node) {}

/////////////////////////
// Tree
/////////////////////////

//Constructor
template <typename T>
Tree<T>::Tree() : root(nullptr) {
	// Do nothing
	//
}

//Destructor
template <typename T>
Tree<T>::~Tree() {
	delete root; //Because root is dynamically-allocated, we must explicitly call delete
	root = nullptr;
}

//Get the size of the tree.
template <typename T>
size_t Tree<T>::size() const {
	//
	return 1+sizeHelper(root);
}

//Returns the total number of descendants from ptr. The size of the tree rooted at ptr is thus
//sizeHelper(ptr)+1.
template <typename T>
size_t Tree<T>::sizeHelper(Tree<T>::Node* ptr) const {
	if(ptr == nullptr) {
		return 0;
	}

	size_t total = 0;
	const size_t childrenSize = ptr->children.size();
	for(size_t i=0; i<childrenSize; ++i) {
		total += sizeHelper(ptr->children[i]);
	}
	return total;
}

//Get the height of the tree.
template <typename T>
size_t Tree<T>::height() const {
	//
	return heightHelper(root);
}

//Returns the height of the tree rooted at ptr
template <typename T>
size_t Tree<T>::heightHelper(Tree<T>::Node* ptr) const {
	if(ptr == nullptr) {
		return 0;
	}

	std::list<size_t> heights;
	const size_t childrenSize = ptr->children.size();
	for(size_t i=0; i<childrenSize; ++i) {
		heights.emplace_back(heightHelper(ptr->children[i]));
	}
	return 1 + *(std::max_element(heights.begin(), heights.end()));
}

//Return a ptr to the root node.
template <typename T>
Tree<T>::Node* Tree<T>::getRoot() const {
	//
	return root;
}

#endif