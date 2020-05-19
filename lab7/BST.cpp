/* Nicholas Jordan
 * CMPS3120 Algorithm Analysis
 * Lab07
 */
#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

#include <iostream>
using namespace std;

template <class T>
struct BST {
	struct node {
		public:
			T key;
			node *left;
			node *right;
			node *parent;
			node(T data) {
				key = data;
				left = nullptr;
				right = nullptr;
				parent = nullptr;
			}
	};
	node* root;
    BST()
    {
        root = nullptr;
    }
	node* newNode(T data)
	{
		node* temp = (node*)malloc(sizeof(struct node));
		temp->key = data;
		temp->left = nullptr;
		temp->right = nullptr;
		return temp;
	}
	void inOrder(node* root)
	{
		if (root != nullptr) {
			inOrder(root->left);
			cout << root->key << ", ";
			inOrder(root->right);
		}
	}
	bool search(node* root, T data)
	{
		bool result = false;
		if (data == root->key)
			result = true;
		else if (data < root->key && root->left != nullptr)
			result = search(root->left, data);
		else if (data > root->key && root->right != nullptr)
			result = search(root->right, data);
		return result;
	}
	node* insert(node* object, T data)
	{
		if (object == nullptr)
			return newNode(data);
		if (data < object->key)
			object->left = insert(object->left, data);
		else if (data > object->key)
			object->right = insert(object->right, data);
		return object;
	}
	node* remove(node* root, T key) 
	{ 
		if (root == NULL)
			return root; 
		if (key < root->key) {
			root->left = remove(root->left, key); 
		} else if (key > root->key) {
			root->right = remove(root->right, key); 
		} else { 
			if (root->left == NULL) { 
				struct node *temp = root->right; 
				free(root); 
				return temp; 
			} else if (root->right == NULL) { 
				node *temp = root->left; 
				free(root); 
				return temp; 
			} 
			node* temp = min(root->right); 
			root->key = temp->key; 
			root->right = remove(root->right, temp->key); 
		} 
		return root; 
	}
	node* min(node* object)
	{
		node* temp = object;
		while ((temp != nullptr) && (temp->left != nullptr))
			temp = temp->left;
		return temp;
	}

	node* max(node *object)
	{
		node* temp = object;
		while ((temp != nullptr) && (temp->right != nullptr))
			temp = temp->right;
		return temp;
	}	
	/*T predecessor(node* root, T data) 
	{
		T result = data;
        if (root->left == nullptr)
            return result;
		if (root->key == data) {
			node* temp = root->left;
			while (temp->right != nullptr)
				temp = temp->right;
			result = temp->key;
		} else if (root->key > data) {
			result = predecessor(root->left, data);
		} else if (root->key < data) {
			result = predecessor(root->right, data);
		}
		return result;
	}
	T successor(node* root, T data) 
	{
		T result = data;
        if (root->right == nullptr)
            return result;
		if (root->key == data) {
			node* temp = root->right;
			while (temp->left != nullptr)
				temp = temp->left;
			result = temp->key;
		} else if (root->key < data) {
			result = predecessor(root->left, data);
		} else if (root->key > data) {
			result = predecessor(root->right, data);
		}
		return result;
	}*/
    node* findNode(node* root, T data)
    {
        while (root != nullptr) {
            if (data > root->key)
                root = root->right;
            else if (data < root->key)
                root = root->left;
            else
                return root;
        }
        return root;
    }
    T successor(node* root, T data)
    {
        node* succ = findNode(root, data);
        if (succ->right != nullptr) {
            succ = min(root->right);
            return succ->key;
        }
        return data; 
    }
    T predecessor(node* root, T data)
    {
        node* pred = nullptr;
        if (root->left != nullptr) {
            pred = max(root->left);
            return pred->key;
        }
        return data; 
    }
};

void showMenu()
{
	printf("\t\tBinary Search Tree\n");
	printf("======================================================\n");
	printf("i\tInsert a value into the tree\n");
	printf("s\tSearch for a value in the tree\n");
	printf("d\tDelete a value from the tree\n");
	printf("-\tPrint the predecessor for a value from the tree\n");
	printf("+\tPrint the successor for a value from the tree\n");
	printf("p\tPrint the values of the tree in sorted order\n");
	printf("x\tExit\n");
	printf("======================================================\n");
}

int main()
{
	BST<ELEMTYPE> tree;
	ELEMTYPE data;
	char selection;
    tree.root = tree.insert(tree.root, 20);
    tree.insert(tree.root, 59);
    tree.insert(tree.root, 12);
    tree.insert(tree.root, 76);
    tree.insert(tree.root, 45);
    tree.insert(tree.root, 65);
    tree.insert(tree.root, 32);
    tree.insert(tree.root, 87);
    tree.insert(tree.root, 0);
    tree.insert(tree.root, -1);
	showMenu();
    printf("\t\tInitial Values\n");
    tree.inOrder(tree.root);
	printf("\n======================================================\n");
	do {
		cin >> selection;
		if (selection == 'm') {
				showMenu();
		} else if (selection == 'i') {
				printf("Enter element to insert into the tree: ");
				cin >> data;
				tree.insert(tree.root, data);
        } else if (selection == 's') {
				printf("Enter element to be searched for in the tree: ");
				cin >> data;
				if (tree.search(tree.root, data))
					cout << data << " was found in the tree!\n";
				else
					cout << data << " was not found in the tree.\n";
        } else if (selection == 'd') {
				printf("Enter element to delete from the tree: ");
				cin >> data;
				tree.root = tree.remove(tree.root, data);
        } else if (selection == 'p') {
				tree.inOrder(tree.root);
				printf("\n");
        } else if (selection == '-') {
				printf("Enter element of the tree for which you want the predecessor of: ");
				cin >> data;
				if (tree.predecessor(tree.root, data) == data)
                    cout << tree.predecessor(tree.root, data) << " has no predecessor.\n";
                else
                    cout << tree.predecessor(tree.root, data) << " is the predecessor.\n";
        } else if (selection == '+') {
				printf("Enter element of the tree for which you want the successor of: ");
				cin >> data;
				if (tree.successor(tree.root, data) == data)
                    cout << tree.successor(tree.root, data) << " has no successor.\n";
                else
                    cout << tree.successor(tree.root, data) << " is the successor.\n";
        }

	} while (selection != 'x');
	return 0;
}
