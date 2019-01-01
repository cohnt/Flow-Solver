#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <list>

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
	size_t size;
	size_t height;

	Tree(const Tree &);
	Tree& operator=(const Tree &);

public:
	Tree();
	~Tree();

	size_t getSize() const;
	size_t getHeight() const;

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
}

//Child, given value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr, T t) : children(), parent(ptr), datum(t) {
	parent->children.emplace_back(this);
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

#endif