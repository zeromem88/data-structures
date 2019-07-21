#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) const {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;

	int output = -1;

    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
			opening_brackets_stack.emplace(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
			if (!opening_brackets_stack.empty()) {
				const Bracket& b = opening_brackets_stack.top();
				if (b.Matchc(next)) {
					opening_brackets_stack.pop();
				}
				else {
					output = position + 1;
					break;
				}
			}
			else {
				output = position + 1;
				break;
			}
        }
    }

	if (output == -1 && !opening_brackets_stack.empty()) {
		const Bracket& b = opening_brackets_stack.top();
		output = b.position + 1;
	}

    // Printing answer, write your code here
	if (output == -1) {
		std::cout << "Success" << std::endl;
	}
	else {
		std::cout << output << std::endl;
	}

    return 0;
}
