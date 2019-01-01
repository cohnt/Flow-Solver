A templated tree data structure. Example explanation:

Create an empty tree
```c++
Tree<int> t1;
```

Create a tree with a single element at the root
```c++
Tree<int> t2(5);
```

Set the root to a dynamically allocated `Node*` (deletion will be handled by the tree) or create a new Node with a given value. This erases the current tree.
```c++
t1.setRoot(new Tree<int>::Node(17));
t1.setRoot(6);
```

Get the size and height of a tree, print out the tree
```c++
std::cout << "size: " << t1.size() << std::endl;
std::cout << "height: " << t1.height() << std::endl;
t1.print();
```

Various ways of getting the root `Node*` of the tree
```c++
Tree<int>::Node* root = t1.getRoot();
auto r2 = t2.getRoot();
```

Add children to a `Node*`. These methods return a pointer to the added child node.
```c++
auto tempPtr = root->addChild();
tempPtr->datum = 15;
root->addChild()->datum = 16;
root->addChild(17);
```

Delete children from a `Node*`. These methods return false if the element to delete doesn't exist, and true if it was successfully deleted.
```c++
root->deleteFirstChild();
root->deleteLastChild();
root->deleteNthChild(3);
```

Access the children from a `Node*`
```c++
auto tempPtr2 = root->firstChild();
tempPtr2->datum = 1;
root->lastChild()->datum = -1;
root->nthChild(1)->datum = 43;
```

Get the parent of a `Node*`
```c++
child->getParent()->addChild(300);
```

Get the number of children of a `Node*`
```c++
std::cout << "root num children: " << root->numChildren() << std::endl;
```