#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
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
					if (top->key > tree[top->right].min_key) {
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

int main() {
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i) {
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (nodes == 0 || IsBinarySearchTree(tree)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	return 0;
}
