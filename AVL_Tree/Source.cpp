#include <iostream>
using namespace std;

struct node
{
	int value;
	node* right = nullptr;
	node* left = nullptr;
	int height = 1;
};

int balanceindex(node*& a)
{
	if (a == nullptr)
	{
		return 0;
	}
	return (a->right != nullptr ? a->right->height : 0) - (a->left != nullptr ? a->left->height : 0);
}

void changeheight(node*& a)
{
	if (a == nullptr)
	{
		return;
	}
	int hl = (a->left != nullptr ? a->left->height : 0);
	int hr = (a->right != nullptr ? a->right->height : 0);
	a->height = __max(hl, hr) + 1;
}

node* bigleftturn(node*& a)
{
	node* b = a->right;
	node* c = b->left;
	a->right = c->left;
	b->left = c->right;
	c->right = b;
	c->left = a;
	changeheight(a);
	changeheight(b);
	changeheight(c);
	return c;
}

node* smallrightturn(node*& a)
{
	node* b = a->left;
	a->left = b->right;
	b->right = a;
	changeheight(a);
	changeheight(b);
	return b;
}

node* bigrightturn(node*& a)
{
	node* b = a->left;
	node* c = b->right;
	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;
	changeheight(a);
	changeheight(b);
	changeheight(c);
	return c;
}

node* smallleftturn(node*& a)
{
	node* b = a->right;
	a->right = b->left;
	b->left = a;
	changeheight(a);
	changeheight(b);
	return b;
}

node* balance(node*& a)
{
	changeheight(a);
	if (balanceindex(a) == 2)
	{
		if (balanceindex(a->right) < 0)
		{
			return bigleftturn(a);
		}
		return smallleftturn(a);
	}
	if (balanceindex(a) == -2)
	{
		if (balanceindex(a->left) > 0)
		{
			return bigrightturn(a);
		}
		return smallrightturn(a);
	}
	return a;
}

node* insert(node* root, int value)
{
	if (root == nullptr)
	{
		node* p = new node;
		p->value = value;
		return p;
	}
	if (value == root->value)
	{
		return root;
	}
	if (value < root->value)
	{
		root->left = insert(root->left, value);
	}
	else
	{
		root->right = insert(root->right, value);
	}
	return balance(root);
}

node* searchmin(node* root)
{
	if (root == nullptr)
	{
		return root;
	}
	if (root->left == nullptr)
	{
		return root;
	}
	searchmin(root->left);
}

node* deletemin(node* root/*, node*& min*/)
{
	if (root->left == nullptr)
	{
		//min = root;
		//delete root;
		//delete
		return  root->right;
	}
	//node* minnode = nullptr;
	root->left = deletemin(root->left/*, minnode*/);
	return balance(root);
}

node* erase(node* root, int value)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (value < root->value)
	{
		root->left = erase(root->left, value);
		return balance(root);
	}
	if (value > root->value)
	{
		root->right = erase(root->right, value);
		return balance(root);
	}
	if (value == root->value)
	{
		node* left = root->left;
		node* right = root->right;
		delete root;
		if (right == nullptr)
		{
			return left;
		}
		node* min = searchmin(right);
		min->right = deletemin(right);
		min->left = left;
		return balance(min);
	}
}

void printtree(node* root, int level)
{
	
	if (root == nullptr)
	{
		int i = 0;
		for (i; i < level - 1; i++)
		{
			cout << "|  ";
		}
		if (i < level)
		{
			cout << "|_";
		}
		cout << endl;
		return;
	}
	int i = 0;
	for (i; i < level - 1; i++)
	{
		cout << "|  ";
	}
	if (i < level)
	{
		cout << "|__";
	}
	cout << root->value;
	cout << endl;
	
	printtree(root->right, level + 1);
	printtree(root->left, level + 1);
}

void printprefix(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	cout << root->value << " ";
	printprefix(root->left);
	printprefix(root->right);
	return;
}

void printinfix(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	printinfix(root->left);
	cout << root->value << " ";
	printinfix(root->right);
	return;
}

void printpostfix(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	printpostfix(root->left);
	printpostfix(root->right);
	cout << root->value << " ";
	return;
}

int main()
{
	node* root = nullptr;
	/*root = insert(root, 5);
	root = insert(root, 6);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 4);
	printinfix(root);
	//root = erase(root, 4);
	//cout << endl;
	//printinfix(root);
	//root = erase(root, 6);
	//cout << endl;
	//printinfix(root);
	cout << endl << endl;
	printtree(root, 0);*/
	int x;
	bool again = true;
	cout << "1: insert\n2: erase\n3: print tree\n4: print prefix\n5: print infix\n6: print postfix\n0: exit\n";
	while (again)
	{
		cin >> x;
		switch (x)
		{
		case 0:
			again = false;
			continue;
		case 1:
			cout << "enter number to insert:" << endl;
			cin >> x;
			root = insert(root, x);
			break;
		case 2:
			cout << "enter number to erase:" << endl;
			cin >> x;
			root = erase(root, x);
			break;
		case 3:
			cout << endl;
			printtree(root, 0);
			break;
		case 4:
			printprefix(root);
			break;
		case 5:
			printinfix(root);
			break;
		case 6:
			printpostfix(root);
			break;
		default:
			continue;
		}
		cout << "enter next command:" << endl;
	}
	return 0;
}