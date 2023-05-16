#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StringBinaryTree
{
private:
	// builds the binary tree
	struct TreeNode
	{
		string value;
		shared_ptr <TreeNode> left;
		shared_ptr <TreeNode> right;
		TreeNode(string value1, shared_ptr <TreeNode> left1 = nullptr, shared_ptr <TreeNode> right1 = nullptr)
		{
			value = value1;
			left = left1;
			right = right1;
		}
	};

	shared_ptr <TreeNode> root; // pointer to the root of the tree

	// helper member functions
	void insert(shared_ptr <TreeNode> &, string);
	void remove(shared_ptr <TreeNode> &, string);
	void displayInOrder(shared_ptr <TreeNode>) const;
	void displayPreOrder(shared_ptr <TreeNode>) const;

public:
	// member functions are the public interface
	StringBinaryTree() 
	{
		root = nullptr;
	}
	void insert(string word)
	{
		insert(root, word);
	}
	bool search(string) const;
	void remove(string word)
	{
		remove(root, word);
	}
	void showInOrder(void) const
	{
		displayInOrder(root);
	}
	void showPreOrder() const
	{
		displayPreOrder(root);
	}
};

// inserts a word into binary tree
void StringBinaryTree::insert(shared_ptr <TreeNode> &tree, string word)
{
	//if (!tree)
	//{
	//	tree = new TreeNode(word);
	//	return;
	//}
	if (!tree)
	{
		tree = make_shared<TreeNode>(word);
		return;
	}

	if (tree->value == word)
		return;

	if (word < tree->value)
		insert(tree->left, word);
	else
		insert(tree->right, word);
}

// displays the values stored in the tree in inorder
void StringBinaryTree::displayInOrder(shared_ptr <TreeNode> tree) const
{
	if (tree)
	{
		displayInOrder(tree->left);
		cout << tree->value << "  " << endl;
		displayInOrder(tree->right);
	}
}

// displays the values stored in the tree in preorder
void StringBinaryTree::displayPreOrder(shared_ptr <TreeNode> tree) const
{
	if (tree)
	{
		cout << tree->value << "  " << endl;
		displayPreOrder(tree->left);
		displayPreOrder(tree->right);
	}	
}

// looks for a value in tree. if so it returns true. otherwise it returns false
bool StringBinaryTree::search(string word) const
{
	shared_ptr <TreeNode> tree = root;

	while (tree)
	{
		if (tree->value == word)
		{
			cout << word << " is in the tree\n";
			return true;
		}
		else if (word < tree->value)
			tree = tree->left;
		else
			tree = tree->right;
	}
	cout << word << " is not in the tree\n";
	return false;
}

// use of postorder traversal to free all nodes after tree object is deleted
// and displaying the node's word before it's deleted.
void StringBinaryTree::remove(shared_ptr <TreeNode> &tree, string word)
{
	if (tree == nullptr) return;
	remove(tree->left, word);
	remove(tree->right, word);
	cout << "Deleting node with value: " << tree->value << endl;
	// delete tree;
}

int main(int argc, char* argv[]) 
{
	StringBinaryTree tree;
	string file;
	file = argv[1];
	// checks command line
	if (argc != 2)
	{
		cout << ("Error: missing command line arguments\n");
		return 0;
	}
	string word;
	// opens file with specified in command line 
	ifstream myfile(file);
	if (!myfile.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}
	// reads file and inserts to tree
	while (!myfile.eof())
	{
		getline(myfile, word, '\n');
		tree.insert(word);
	}
	cout << "***** PreOrder: *****\n";
	tree.showPreOrder();
	
	cout << "***** InOrder: *****\n";
	tree.showInOrder();
	
	// prompts user for word search or q to delete tree 
	while (true)
	{
		cout << "Enter word to search for, or " << 'q' << " to quit --> ";
		string input;
		cin >> input;
		if (input == "q")
		{
			tree.remove(word);
			return false;
		}
		else
		{
			tree.search(input);
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
