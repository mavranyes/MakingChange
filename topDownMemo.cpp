#include <iostream>
#include <string>
#include <vector>

using namespace std;

string topDownMemo(vector <int> denoms, int problem) {
	string solution;
	int best = INT_MAX;
	int* sol = new int[problem]();
	//Base
	if (problem < 2) {
		return to_string(problem);
	}
	//Check if solution is found
	if (sol[problem] != 0) {
		return to_string(problem);
	}

	//Iterate through each denom
	for (int k = 0; k < denoms.size(); k++) {
		int size = problem - denoms[k];
		if (size < 0) {//Prevents evaluation of denoms that are too large
			continue;
		}
		sol[size] = stoi(topDownMemo(denoms, size));
		if (sol[size] < best) {
			best = sol[size];
		}
	}
	sol[problem] = best + 1;
	return to_string(sol[problem]);
}
