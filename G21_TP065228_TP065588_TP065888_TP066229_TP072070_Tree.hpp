#include <iostream>
#include <iomanip>

using namespace std;

struct node
{
	string data;
	node* left;
	node* right;

};

class BinaryTree
{
	node* root;
	int size;
public: 
	~BinaryTree()
	{
		cout << "Tree is deleted from the memory!" << endl;
	}

	void buildtree(string* arraypointer)
	{
		root = insert(arraypointer, 0);
	}
	node* insert(string* a, int currentindex)
	{
		if (currentindex >= 30) {
			return nullptr; 
		}

		node* temp = new node;
		temp->data = a[currentindex];
		temp->left = insert(a, 2 * currentindex + 1); // Insert left child
		temp->right = insert(a, 2 * currentindex + 2); // Insert right child

		return temp;
	}

	void printTree(node* current, int level) const {
		if (current == nullptr) {
			return;
		}

		printTree(current->right, level + 1);

		for (int i = 0; i < level; i++) {
			cout << setw(4) << "        "; 
		}
		cout << current->data << endl;

		printTree(current->left, level + 1);
	}

	void printTop30Tree() const {
		cout << "Top 30 Tree:" << endl;
		printTree(root, 0);
	}
	bool searchNode(string& data)
	{
		return searchNode(root, data);
	}
	
private:
	bool searchNode(node* root, string& data)
	{
		if (root == nullptr) {
			return false;
		}
		else if (root->data == data) {
			return true;
		}
		else {
			return searchNode(root->left, data) || searchNode(root->right, data);
		}
	}
	
};