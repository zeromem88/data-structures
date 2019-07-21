#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::stack;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  vector <int> in_order() {
    vector<int> result;
	stack<int> stk;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	int curr_key   = key[0];
	int curr_left  = left[0];
	int curr_right = right[0];

	stk.push(0);

	while (!stk.empty() || (curr_left != -1)) {
		if (curr_left != -1) {
			stk.push(curr_left);
			curr_left = left[curr_left];
		}
		else {
			int top = stk.top();
			stk.pop();
			result.push_back(key[top]);
			curr_right = right[top];
			if (curr_right != -1) {
				stk.push(curr_right);
				curr_left = left[curr_right];
			}
		}
	};

    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
	stack<int> stk;

	stk.push(0);

	while (!stk.empty()) {
		int top = stk.top();
		stk.pop();
		int curr_key = key[top];
		int curr_left = left[top];
		int curr_right = right[top];
		result.push_back(curr_key);

		if (curr_right != -1) {
			stk.push(curr_right);
		}

		if (curr_left != -1) {
			stk.push(curr_left);
		}
	};
    
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	stack<int> stk;
	stk.push(0);
	int curr_key = key[0];
	int curr_left = left[0];
	int curr_right = right[0];

	int lastNode = -1;

	while (!stk.empty() || (curr_left != -1)) {
		if (curr_left != -1) {
			stk.push(curr_left);
			curr_left = left[curr_left];
		}
		else {
			int top = stk.top();
			curr_right = right[top];
			if (curr_right != -1 && lastNode != curr_right) {
				stk.push(curr_right);
				curr_left = left[curr_right];
			}
			else {
				lastNode = top;
				stk.pop();
				result.push_back(key[top]);
			}
		}
	};

    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

