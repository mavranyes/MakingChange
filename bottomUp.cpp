#include <iostream>
#include <string>
#include <vector>

using namespace std;

int bottomUp(vector <int> denoms, int problem) {
	int solution;
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
			// cout << "size: " << size << endl;
			// cout << "i: " << i << " denom: " << denoms[i] << endl;
			// cout << "k: " << k << " num: " << sol[size] << endl;
			// cout << "-----------------------" << endl;
			if (sol[size] < best) {
				best = sol[size] + 1;
				bestDenom = denoms[i];
			}
		}
		jmpSize[k] = bestDenom;
		sol[k] = best;
		best = INT_MAX;
	}

	int denomCount[denoms.size()];
	//Find purse
	while (problem != 0) {
		denomCount[denompos]++;
		problem -= jmpSize[problem];
	}

	solution = sol[problem];
	return solution;
}
