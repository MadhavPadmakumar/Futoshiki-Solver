using namespace std;
#include <iostream>
#include <vector>
#include <ranges>
#include <map>

bool solve(const int n, std::vector<std::vector<int>> &puzzle, std::vector<std::vector<int>> &constraints);
bool is_valid(const int n, int row, int col, int val, const std::vector<std::vector<int>> &puzzle, std::vector<std::vector<int>> &constraints);
void generate_constraints(const int n, std::vector<std::vector<int>> &constraints);
void choose_constraints(const int n,
						std::vector<std::vector<int>> &puzzle, 
						std::vector<std::vector<int>> &constraints, 
						std::vector<std::vector<int>> &allConstraints);
bool is_valid_constraint(const std::vector<std::vector<int>> &constraints, const std::vector<int> &newConstraint);
void counterexample(const std::vector<std::vector<int>> &puzzle, const std::vector<std::vector<int>> &constraints);
						

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
	choose_constraints(n, puzzle, constraints, allConstraints);

	// If no counterexample was found, conjecture is true for n.
	cout << "Conjecture is true for " << n << '.' << endl;
}

// Recursively solve the puzzle.
bool solve(const int n, std::vector<std::vector<int>> &puzzle, std::vector<std::vector<int>> &constraints) {
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
		if (is_valid(n, row, col, i, puzzle, constraints)) {
			puzzle[row][col] = i;
			if (solve(n, puzzle, constraints)) {
				return true;
			}
			puzzle[row][col] = 0;
		}
	}
	return false;
}

// Determines if a cell choice is valid.
bool is_valid(const int n, int row, int col, int val, const std::vector<std::vector<int>> &puzzle, std::vector<std::vector<int>> &constraints) {
	// No duplicates in row.
	for (int i = 0; i < n; i++) {
		if (puzzle[row][i] == val) {
			return false;
		}
	}

	// No duplicates in column.
	for (int i = 0; i < n; i++) {
		if (puzzle[i][col] == val) {
			return false;
		}
	}

	// Satisfies inequalities.
	for (vector<int> constraint : constraints) {
		if (constraint[0] == row & constraint[1] == col) {
			if (val > puzzle[constraint[2]][constraint[3]] & puzzle[constraint[2]][constraint[3]] != 0) {
				return false;
			}
		} else if (constraint[2] == row & constraint [3] == col) {
			if (val < puzzle[constraint[0]][constraint[1]]) {
				return false;
			}
		}
	}
	
	return true;
}

// Populates a vector with all possible inequality constraints.
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

// Recursively choose each combination of n-1 constraints, then solve them.
void choose_constraints(const int n,
						std::vector<std::vector<int>> &puzzle, 
						std::vector<std::vector<int>> &constraints, 
						std::vector<std::vector<int>> &allConstraints) {
	if (constraints.size() == n - 1) {
		if (solve(n, puzzle, constraints)) {
			// Continue recursing.
			return;
		} else {
			// Counterexample found.
			counterexample(puzzle, constraints);
			return;
		}
	}
	else {
		if(constraints.empty()){
			// Remove each restraint from the list once, then recurse.
			int steps = allConstraints.size();
			for(int i = 0; i < steps; i++){
				constraints.push_back(allConstraints[0]);
				allConstraints.erase(allConstraints.begin());
				choose_constraints(n, puzzle, constraints, allConstraints);
				constraints.pop_back();
			}
		} else{
			// Recurse.
			for (int i = 0; i < allConstraints.size(); i++) { 
				if(is_valid_constraint(constraints, allConstraints[i])){
					constraints.push_back(allConstraints[i]);
					choose_constraints(n, puzzle, constraints, allConstraints);
					constraints.pop_back();
				}
			}
		}
	}
}

// Checks if candidate constraint is valid.
bool is_valid_constraint(const std::vector<std::vector<int>> &constraints, const std::vector<int> &newConstraint){
	// // new constraint cannot be a duplicate of an existing constraint.
	// if (std::find(constraints.begin(), constraints.end(), newConstraint) != constraints.end()){
	// 	return false;
	// }

	for (int i = 0; i < constraints.size(); i++) {
		// new constraint cannot be a duplicate of an existing constraint.
		if (constraints[i][0] == newConstraint[0] & constraints[i][1] == newConstraint[1] &
		    constraints[i][2] == newConstraint[2] & constraints[i][3] == newConstraint[3]) {
			return false;
		}

		// new constraint cannot be the opposite of an existing constraint.
		if (constraints[i][0] == newConstraint[2] & constraints[i][1] == newConstraint[3] &
		    constraints[i][2] == newConstraint[0] & constraints[i][3] == newConstraint[1]) {
			return false;
		}
	}

	// Constraint is valid.
	return true;
}

// Output counterexample and terminate program.
void counterexample(const std::vector<std::vector<int>> &puzzle, const std::vector<std::vector<int>> &constraints) {
	cout << "Counterexample found:" << endl;
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle.size(); j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < constraints.size(); i++) {
		cout << "(" << constraints[i][0] << ", " << constraints[i][1] << ") < (" << constraints[i][2] << ", " << constraints[i][3] << ")" << endl;
	}
	exit(0);
}