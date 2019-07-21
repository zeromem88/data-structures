#include <iostream>
#include <string>
#include <vector>
#include <limits>

using std::string;
typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

constexpr size_t multiplier = 3;
constexpr size_t prime = 13;

size_t hash_func(const string& s, size_t start, size_t end)  {
	unsigned long long hash = 0;
	for (size_t i = end; i >= start && i != std::numeric_limits<size_t>::max(); --i)
		hash = (hash * multiplier + s[i]) % prime;
	return hash;
}

std::vector<size_t> rabin_precompute(const Data& input) {
	size_t y = 1;
	size_t text_size = input.text.size();
	size_t pattern_size = input.pattern.size();
	size_t m = text_size - pattern_size;
	std::vector<size_t> H(m + 1);

	H[m] = hash_func(input.text, m, text_size - 1);

	for (size_t i = 0; i < pattern_size; ++i) {
		y = (y * multiplier) % prime;
	}

	for (size_t i = m - 1; i >= 0 && i != std::numeric_limits<size_t>::max(); --i) {
		H[i] = (multiplier * H[i + 1] + input.text[i] - (y * input.text[i + pattern_size]) % prime) % prime;
	}

	return H;
}

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<size_t>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<size_t> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<size_t> ans;
    /*for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);*/
	const auto& precomp = rabin_precompute(input);
	size_t phash = hash_func(s, 0, s.size() - 1);
	for (size_t i = 0; i < precomp.size(); ++i) {
		if (phash != precomp[i]) {
			continue;
		}
		
		if (t.compare(i, s.size(), s) == 0) {
			ans.push_back(i);
		}
	}
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
