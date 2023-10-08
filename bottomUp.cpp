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
			cout << "size: " << size << endl;
			cout << "denom: " << denoms[i] << endl;
			cout << "k: " << k << " num: " << sol[size] << endl;
			cout << "-----------------------" << endl;
			if (sol[size] < best) {
				best = sol[size] + 1;
			}
		}
		sol[k] = best;
		best = INT_MAX;
	}
	solution = sol[problem];
	return solution;
}
