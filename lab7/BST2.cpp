#include <iostream>
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

template <class T>
class BST
{
	class TreeNode
	{
		public:
			T data;
			TreeNode *left;
			TreeNode *right;
			TreeNode *parent;
			TreeNode(T val)
			{
				data=val;
				left=nullptr;
				right=nullptr;
				parent=nullptr;
			}
	};
	private:
	TreeNode *root;
	bool insertSubtree(TreeNode * subtree, T elem)
	{
		bool result = false;
		if(subtree->data == elem)
			return result;
		if(subtree->data < elem) {
			if(!subtree->right) {
				subtree->right = new TreeNode(elem);
				subtree->right->parent = subtree;
				result = true;
			} else {
				result = insertSubtree(subtree->right, elem);
			}
		}
		if(subtree->data > elem) {
			if(!subtree->left) {
				subtree->left = new TreeNode(elem);
				subtree->left->parent = subtree;
				result = true;
			} else {
				result = insertSubtree(subtree->left, elem);
			}
		}   
		return result;
	}
	void printSubtree(TreeNode * subtree)
	{
		if(subtree->left != nullptr)
			printSubtree(subtree->left);
		if (subtree->parent != nullptr)
			cout << "    " << subtree->data << " parent: " << subtree->parent->data << endl;
		else
			cout << "    " << subtree->data << endl;
		if(subtree->right != nullptr)
			printSubtree(subtree->right);
	}
	bool containsSubtree(TreeNode * subtree, T elem)
	{
		bool result = false;
		if(subtree->data > elem) {
			if(subtree->left != nullptr)
				result = containsSubtree(subtree->left, elem);
		}
		if(subtree->data == elem)
			result = true;
		if(subtree->data < elem) {
			if(subtree->right != nullptr)
				result = containsSubtree(subtree->right, elem);
		}
		return result;
	}
	bool remove(TreeNode* ptr, T elem)
	{
		while (true) {
			if (ptr == nullptr)
				return(false);
			if (ptr->data == elem) {
                break;
            }
			if (elem < ptr->data) {
				ptr = ptr->left;
			} else {
				ptr = ptr->right;
			}
		}
		/*======[Case 1: No children]======*/
		if (ptr->left == nullptr && ptr->right == nullptr) {
            if (ptr == root) {
                root = nullptr;
            } else if (ptr->parent->data > ptr->data) {
				ptr->parent->left = nullptr;
            } else if (ptr->parent->data < ptr->data) {
				ptr->parent->right = nullptr;
            }
			return true;
		}
		/*======[Case 3: Two children]======*/
		if ((ptr->left != nullptr) && (ptr->right != nullptr)) {
            T temp = min(ptr->right);
            if (temp > ptr->data) {
                remove(ptr->right, temp);
            } else if (temp < ptr->data) {
                remove(ptr->left, temp);
            }
            ptr->data = temp;
            return true;
		}
		/*======[Case 2: One child]======*/
        if (ptr == root) {
            if (ptr->left == nullptr) {
                ptr->right->parent = nullptr;
                root = ptr->right;
            } else if (ptr->right == nullptr) {
                ptr->left->parent = nullptr;
                root = ptr->left;
            }
            return true;
        } else if (ptr->left == nullptr) {
			ptr->right->parent = ptr->parent;
			if (ptr->parent->data > ptr->right->data)
				ptr->parent->left = ptr->right;
			else if (ptr->parent->data < ptr->right->data)
				ptr->parent->right = ptr->right;
			return true;
		} else if (ptr->right == nullptr) {
			ptr->left->parent = ptr->parent;
			if (ptr->parent->data > ptr->left->data)
				ptr->parent->left = ptr->left;
			else if (ptr->parent->data < ptr->left->data)
				ptr->parent->right = ptr->left;
			return true;
		}
		return false;
	}
	void DestroyNode(TreeNode * subtree)
	{
		if(subtree != nullptr) {
			DestroyNode(subtree->left);
			DestroyNode(subtree->right);
			delete subtree;
		}
	}
	T min(TreeNode *subtree)
	{
		while (subtree->left != nullptr)
			subtree = subtree->left;
		return subtree->data;
	}
	T max(TreeNode *subtree)
	{
		while (subtree->right != nullptr)
			subtree = subtree->right;
		return subtree->data;
	}
	T predecessor(TreeNode *subtree, T elem)
	{
		if (subtree->data == elem) {
			if (subtree->left != nullptr) {
				return max(subtree->left);
			} else if (subtree->data < subtree->parent->data) {
				TreeNode *target = subtree;
				while (target->data < subtree->parent->data) {
					target = subtree;
					subtree = subtree->parent;
				}
				return subtree->parent->data;
			} else if (subtree->data > subtree->parent->data) {
				return subtree->parent->data;
			}
		} else if (subtree->data > elem) {
			return predecessor(subtree->left, elem);
		} else if (subtree->data < elem) {
			return predecessor(subtree->right, elem); 
		}
		return elem;
	}
	T successor(TreeNode *subtree, T elem)
	{
		if (subtree->data == elem) {
			if (subtree->right != nullptr) {
				return min(subtree->right);
			} else if (subtree->data > subtree->parent->data) {
				TreeNode *target = subtree;
				while (target->data > subtree->parent->data) {
					target = subtree;
					subtree = subtree->parent;
				}
				return subtree->parent->data;
			} else if (subtree->data < subtree->parent->data) {
				return subtree->parent->data;
			}
		} else if (subtree->data > elem) {
			return successor(subtree->left, elem);
		} else if (subtree->data < elem) {
			return successor(subtree->right, elem); 
		}
		return elem;
	}
	public:
	BST()
	{
		root = nullptr;
	}
	~BST()
	{
		DestroyNode(root);       
	}
	bool empty()
	{
		return (root == nullptr);
	}

	bool insert(T elem)
	{
		if(!root) {
			root = new TreeNode(elem);
			return true;
		} else {
			this->insertSubtree(root, elem);
		}
		return true;
	}
	void print()
	{
        if (!empty()) {
		cout << "BST values\n";
		cout << "=======================\n";
		if (root != nullptr)
			printSubtree(root);
		cout << "=======================\n";
        } else {
            cout << "* The tree is empty *\n";
        }
	}
	bool remove(T elem)
	{
		bool result = remove(root,elem);
		return result;
	}
	bool contains(T elem)
	{
		bool result = false;
		if(!empty()) {
			if(root->data == elem)
				result = true;
			if(!result)
				result = containsSubtree(root, elem);
		}
		return result;
	}
	void min()
	{
		cout << "The minimum value is " << min(root) << endl;
	}
	void max()
	{
		cout << "The maximum value is " << max(root) << endl;
	}
	void predecessor(T elem)
	{
		if (contains(elem)) {
			if (elem == min(root)) {
				cout << elem << " has no predecessor...\n";
				return;
			}
			T temp = predecessor(root, elem);
			if (temp != elem) {
				cout << "The predecessor of " << elem 
					<< " is " << temp << endl;
			} else {
				cout << elem << " has no predecessor...\n";
			}
		} else {
			cout << elem << " doesn't even exist...\n";
		}
	}
	void successor(T elem)
	{
		if (contains(elem)) {
			if (elem == max(root)) {
				cout << elem << " has no successor...\n";
				return;
			}
			T temp = successor(root, elem);
			if (temp != elem) {
				cout << "The successor of " << elem 
					<< " is " << temp << endl;
			} else {
				cout << elem << " has no successor...\n";
			}
		} else {
			cout << elem << " doesn't even exist...\n";
		}
	}
};

void showMenu()
{
	cout << "             Binary Search Tree\n";
	cout << "===============================================\n";
	cout << " i-----Insert a value into the tree\n";
	cout << " s-----Seach for a specific value\n";
	cout << " d-----Delete a value from the tree\n";
	cout << " p-----Print the values of the tree in sorted order\n";
	cout << " m-----Show this menu\n";
	cout << "(-)----Print the minimum value of the tree\n";
	cout << "(+)----Print the maximum value of the tree\n";
	cout << " o-----Print the predecessor of a value\n";
	cout << " u-----Print the successor of a value\n";
	cout << " x-----Exit\n";
	cout << "===============================================\n";
}

int main()
{
	BST<ELEMTYPE> tree;
    /*======[Initial Tree]======
	 *              20
     *             /   \
     *           18     22
     *          /         \
     *        15           39
     *          \         /
     *           17     24
     *                 /
     *               23 
     */
    tree.insert(20);
	tree.insert(18);
	tree.insert(22);
	tree.insert(39);
	tree.insert(24);
	tree.insert(23);
	tree.insert(15);
	tree.insert(17);
	ELEMTYPE elem;
	char selection;
	showMenu();
	tree.print();
	do {
		cout << "Enter selection: ";
		cin >> selection;
		switch (selection) {
			case 'x':
				break;
			case 'm':
				showMenu();
				break;
			case 'i':
				cout << "Enter element to insert: ";
				cin >> elem;
				if (!tree.insert(elem))
					cout << elem << " could not be added...\n";
				break;
			case 's':
				cout << "Enter element to find: ";
				cin >> elem;
				if (tree.contains(elem))
					cout << elem << " was found!\n";
				else
					cout << elem << " was not found...\n";
				break;
			case 'd':
				cout << "Enter element to delete: ";
				cin >> elem;
				if (!tree.remove(elem))
					cout << elem << " could not be removed...\n";
				break;
			case 'p':
				tree.print();
				break;
			case '-':
				tree.min();
				break;
			case '+':
				tree.max();
				break;
			case 'o':
				cout << "Enter element to find predecessor of: ";
				cin >> elem;
				tree.predecessor(elem);
				break;
			case 'u':
				cout << "Enter element to find successor of: ";
				cin >> elem;
				tree.successor(elem);
				break;
			default:
				cout << "Invalid menu option!\n";
		}
	} while (selection != 'x');
	return 0;
}
