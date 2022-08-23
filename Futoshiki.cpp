using namespace std;
#include <iostream>
#include <vector>
#include <ranges>

int main() {
	int n;
	cout << "Enter the size of the puzzle: ";
	cin >> n; 

	// std::vector<std::vector<int>> puzzle = {{1, 2, 3}, {2, 3, 1}, {3, 1, 0}};
	std::vector<std::vector<std::vector<int>>> Puzzle = {{{1}, {2}, {3}}, {{2}, {3}, {1}}, {{3}, {1}, {1, 2, 3}}};

}

bool solve(const int n, std::vector<std::vector<std::vector<int>>> &puzzle) {
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			
		}
		
	}
	
}