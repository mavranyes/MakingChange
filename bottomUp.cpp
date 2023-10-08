#include <iostream>
#include <string>
#include <vector>

using namespace std;

string bottomUp(vector <int> denoms, int problem) {
	string solution;
	int bestDenom;
	int sol[problem];
	int jmpSize[problem];
	sol[0] = 0;
	jmpSize[0] = 0;
	int best = INT_MAX;
	for (int k = 1; k <= problem; k++) {
		//Iterate through each denom
		for (int i = 0; i < denoms.size(); i++) {
			int size = k - denoms[i];
			if (size < 0) {
				continue;
			}
			if (sol[size] < best) {
				best = sol[size] + 1;
				bestDenom = denoms[i];
			}
		}
		jmpSize[k] = bestDenom;
		sol[k] = best;
		best = INT_MAX;
	}
	//Format Solution
	solution = to_string(sol[problem]) + " cents = ";
	int* denomCount = new int[denoms[denoms.size() - 1] + 1]();
	//Find purse
	while (problem != 0) {
		denomCount[jmpSize[problem]]++;
		problem -= jmpSize[problem];
	}
	//Format Purse output
	for (int i = denoms.size() - 1; i >= 0; i--) {
		if (denomCount[denoms[i]] != 0) {
			solution += to_string(denoms[i]) + ":" + to_string(denomCount[denoms[i]]) + " ";
		}
	}
	return solution;
}
