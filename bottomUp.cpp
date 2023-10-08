#include <iostream>
#include <string>
#include <vector>

using namespace std;

int bottomUp(vector <int> denoms, int problem) {
	int solution;
	int sol[problem];
	sol[0] = 0;
	int best = INT_MAX;
	for (int k = 1; k <= problem; k++) {
		//Iterate through each denom
		for (int i = 0; i <= denoms.size(); i++) {
			int size = k - denoms[i];
			if (size < 0) {
				continue;
			}
			if (sol[k - denoms[i]] < best) {
				best = sol[k - denoms[i]] + 1;
			}
		}
		sol[k] = best;
		best = INT_MAX;
	}
	return solution;
}
