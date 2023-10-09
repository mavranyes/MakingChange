#include <iostream>
#include <string>
#include <vector>

using namespace std;

string topDownMemo(vector <int> denoms, int problem, bool init) {
	string solution;
	static int* sol = nullptr;
	int best = INT_MAX;

	//Only initialize array on first recursion
	if (init) {
		if (sol != nullptr) {
			delete sol;
		} 
		sol = new int[problem + 1];
		for (int i = 0; i <= problem; i++) {
			sol[i] = -1;
		}
	}

	//Base
	if (problem == 0) {
		return to_string(problem);
	}
	//Check if solution is found
	if (sol[problem] != -1) {
		return to_string(sol[problem]);
	}

	//Iterate through each denom
	for (int k = 0; k < denoms.size(); k++) {
		int size = problem - denoms[k];
		if (size < 0) {//Prevents evaluation of denoms that are too large
			continue;
		}
		int coins = stoi(topDownMemo(denoms, size, false));
		if (coins != INT_MAX && (coins + 1) < best) {
			best = coins + 1;
		}
	}
	sol[problem] = best;
	return to_string(sol[problem]);
}


// a.out(80957,0x1e0dc1300) malloc: tiny_free_list_remove_ptr: Internal invariant broken (prev ptr of next): ptr=0x12f869b50, next_prev=0x100000004
// a.out(80957,0x1e0dc1300) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./a.out
		// if (size > (sizeof(sol) / sizeof(sol[0]))) {
		// 	cout << "size too big: " << size << endl;
		// 	cout << "sol size: " << (sizeof(sol) / sizeof(sol[0])) << endl;
		// 	cout << "problem: " << problem << endl;
		// }