#include <algorithm>
#include <stack>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;

struct Node {
	int key;
	int left;
	int right;
	int max_key;
	int min_key;

	Node() : key(0), left(-1), right(-1), max_key(0), min_key(0) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_), max_key(key_), min_key(key_) {}
};

int isBSTUtil(vector<Node>& tree, int idx, int min, int max)
{
	if (idx == -1)
		return 1;

	Node* node = &tree[idx];

	/* false if this node violates
	the min/max constraint */
	if (node->key < min || node->key > max)
		return 0;

	/* otherwise check the subtrees recursively,
	tightening the min or max constraint */
	return
		isBSTUtil(tree, node->left, min, node->key - 1) && // Allow only distinct values  
		isBSTUtil(tree, node->right, node->key + 1, max); // Allow only distinct values  
}

int IsBinarySearchTreeSlow(vector<Node>& tree) {
	return(isBSTUtil(tree, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}


bool IsBinarySearchTree(vector<Node>& tree) {
	// Implement correct algorithm here
	bool result = true;
	stack<Node*> stk;
	stk.push(&tree[0]);
	
	Node *curr = &(tree[0]);
	Node lastNode;

	while (!stk.empty() || (curr->left != -1)) {
		if (curr->left != -1) {
			stk.push(&(tree[curr->left]));
			curr = &(tree[curr->left]);
		}
		else {
			Node* top = stk.top();
			if (top->right != -1 && lastNode.key != tree[top->right].key) {
				stk.push(&(tree[top->right]));
				curr = &(tree[top->right]);
			}
			else {
				lastNode = *top;
				stk.pop();
				// result.push_back(key[top]);

				if (top->left != -1) {
					if (tree[top->left].max_key >= top->key) {
						result = false;
						break;
					}
					top->max_key = std::max(tree[top->left].max_key, top->max_key);
					top->min_key = std::min(tree[top->left].min_key, top->min_key);
				}

				if (top->right != -1) {
					if (top->key >= tree[top->right].min_key) {
						result = false;
						break;
					}
					top->max_key = std::max(tree[top->right].max_key, top->max_key);
					top->min_key = std::min(tree[top->right].min_key, top->min_key);
				}
			}
		}
	};

	return result;
}

static vector<int> used;

int make_tree(vector<Node>& tree, int idx, int nodes) {
	if (tree.size() == nodes)
		return 0;

	int r = rand() % 100;

	while (std::find(used.begin(), used.end(), r) != used.end()) {
		r = rand() % 100;
	}

	tree.emplace_back(Node(r, -1, -1));
	used.push_back(r);

	if (r > 50) {
		tree[idx].left = idx + 1;
	}
	else {
		tree[idx].right = idx + 1;
	}

	return make_tree(tree, idx + 1, nodes);
}

/*
Test case:
45
  \ 
   12
     \
	  46

	  Gives CORRECT. But that's incorrect.
*/
/*
void TestCase1(vector<Node>& tree, int& nodes) {
	nodes = 3;
	tree.clear();
	tree.emplace_back(Node(45, -1, 1));
	tree.emplace_back(Node(12, -1, 2));
	tree.emplace_back(Node(46, -1, -1));

	int slow = IsBinarySearchTreeSlow(tree);
	int fast = IsBinarySearchTree(tree);

	if (slow != fast) {
		std::cout << "WRONG!" << std::endl << "slow = " << slow << std::endl << "fast = " << fast;
		throw std::exception("SLOW != FAST");
	}
}*/

int main() {
	int nodes;
	vector<Node> tree;

	//TestCase1(tree, nodes);

	/*while (1) {
		tree.clear();
		used.clear();
		nodes = rand() % 97 + 3;
		
		used.push_back(rand() % 100);
		tree.emplace_back(Node(used[0], -1, -1));

		make_tree(tree, 0, nodes);

		int slow = IsBinarySearchTreeSlow(tree);
		int fast = IsBinarySearchTree(tree);

		if (slow == 1 || fast == 1) {
			std::cout << "GOT BST!" << std::endl;
		}

		if (slow != fast) {
			std::cout << "WRONG!" << std::endl << "slow = " << slow << std::endl << "fast = " << fast;
		}
		else {
			std::cout << "GOOD!" << std::endl;
		}
	};

	return 0;*/
	
	cin >> nodes;
	for (int i = 0; i < nodes; ++i) {
		int key, left, right;
		cin >> key >> left >> right;
		tree.emplace_back(Node(key, left, right));
	}
	if (nodes == 0 || IsBinarySearchTree(tree)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	
	return 0;
}
