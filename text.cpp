#include <iostream>
#include <string>
#include <vector>

using namespace std;

class man_satchel {
public:
	int value;
	//man_satchel* prevCoin;
	string prevCoin;
	man_satchel() {
		this->value = -1;
		this->prevCoin = "";
	}
};

string topDownMemo(vector <int> denoms, int problem, bool init) {
	string solution;
	static man_satchel* sol = nullptr;
	int best = INT_MAX;

	//Only initialize array on first recursion
	if (init) {
		if (sol != nullptr) {
			delete sol;
		} 
		sol = new man_satchel[problem + 1]();
		for (int i = 0; i <= problem; i++) {
			sol[i].value = -1;
		}
	}

	//Base
	if (problem == 0) {
		return to_string(problem);
	}
	//Check if solution is found
	if (sol[problem].value != -1) {
		return to_string(sol[problem].value);
	}

	//Iterate through each denom
	for (int k = 0; k < denoms.size(); k++) {
		int size = problem - denoms[k];
		if (size < 0) {//Prevents evaluation of denoms that are too large
			continue;
		}
		int coins = stoi(topDownMemo(denoms, size, false));
		//sol[problem].prevCoin += to_string(denoms[k]);
		if (coins != INT_MAX && (coins + 1) < best) {
			best = coins + 1;
		}
	}
	sol[problem].value = best;
	return to_string(sol[problem].value);
}