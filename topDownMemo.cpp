#include <iostream>
#include <string>
#include <vector>

using namespace std;


string topDownMemo(vector <int> denoms, int problem) {
	string solution;
	int best = INT_MAX;
	int* sol = new int[problem]();
	//int* coins = new int[problem]();
	//return to_string(mc(problem));
	
	//Base
	if (problem < 2) {
		return to_string(problem);
	}
	//Check if solution is found
	if (sol[problem - 1] != 0) {//Can you have sol[problem] if it is initalized with problem size
		return to_string(problem);
	}

	//Iterate through each denom
	for (int k = 0; k < denoms.size(); k++) {
		int size = problem - denoms[k];
		if (size < 0) {//Prevents evaluation of denoms that are too large
			continue;
		}
		if (sol[size] != 0) {
			continue;
		}
		sol[size] = stoi(topDownMemo(denoms, size));
		if (sol[size] < best) {
			best = sol[size];
		}
	}
	//sol[problem - 1] = best + 1;//THIS CAUSES SEG FAULT
	return to_string(best + 1);
}


// a.out(80957,0x1e0dc1300) malloc: tiny_free_list_remove_ptr: Internal invariant broken (prev ptr of next): ptr=0x12f869b50, next_prev=0x100000004
// a.out(80957,0x1e0dc1300) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./a.out
		// if (size > (sizeof(sol) / sizeof(sol[0]))) {
		// 	cout << "size too big: " << size << endl;
		// 	cout << "sol size: " << (sizeof(sol) / sizeof(sol[0])) << endl;
		// 	cout << "problem: " << problem << endl;
		// }