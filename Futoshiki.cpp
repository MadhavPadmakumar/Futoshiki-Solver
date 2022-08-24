using namespace std;
#include <iostream>
#include <vector>
#include <ranges>
#include <map>

bool solve(const int n, std::vector<std::vector<int>> &puzzle);
bool is_valid(const int n, int row, int col, int val, const std::vector<std::vector<int>> &puzzle);

int main() {
	int n;
	cout << "Enter the size of the puzzle: ";
	cin >> n; 

	// Initalise an empty nxn Latin square.
	std::vector<std::vector<int>> puzzle(n, std::vector<int>(n, 0));

	// Generate and all possible Futoshikis of order n with n-1 constraints.
	std::vector<std::vector<int>> constraints;
	std::vector<std::vector<int>> allConstraints;
	generate_constraints(n, allConstraints);

	// Attempt to solve all possible Futoshikis of order n with n-1 constraints.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			while(constraints.size() < n - 1) {
				
			}
		}
	}

	// std::vector<std::vector<int>> puzzle = {{1, 2, 3}, {2, 3, 1}, {3, 1, 0}};
	// std::vector<std::vector<std::vector<int>>> Puzzle = {{{1}, {2}, {3}}, {{2}, {3}, {1}}, {{3}, {1}, {1, 2, 3}}};
	if (solve(n, puzzle)){
		cout << "Puzzle solved:" << endl;
		for (std::vector<int> row : puzzle) {
			for (int col : row) {
				cout << col << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Puzzle not solvable." << endl;
	}
}

bool solve(const int n, std::vector<std::vector<int>> &puzzle) {
	int row = 0;
	int col = 0;
	int val = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (puzzle[i][j] == 0) {
				row = i;
				col = j;
				val = 1;
				break;
			}
		}
	}
	if (val == 0) {
		return true;
	}
	for (int i = 1; i <= n; i++) {
		if (is_valid(n, row, col, i, puzzle)) {
			puzzle[row][col] = i;
			if (solve(n, puzzle)) {
				return true;
			}
			puzzle[row][col] = 0;
		}
	}
	return false;
}

bool is_valid(const int n, int row, int col, int val, const std::vector<std::vector<int>> &puzzle) {
	for (int i = 0; i < n; i++) {
		if (puzzle[row][i] == val) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		if (puzzle[i][col] == val) {
			return false;
		}
	}
	
	return true;
}

void generate_constraints(const int n, std::vector<std::vector<int>> &constraints) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != 0) {
				constraints.push_back({i, j, i - 1, j});
			}
			if(j != 0) {
				constraints.push_back({i, j, i, j - 1});
			}
			if(i != n - 1) {
				constraints.push_back({i, j, i + 1, j});
			}
			if(j != n - 1) {
				constraints.push_back({i, j, i, j + 1});
			}
		}
	}
}