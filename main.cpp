#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bottomUp.cpp"
#include "topDown.cpp"
#include "topDownMemo.cpp"
#include <climits>

using namespace std;
/*
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

static man_satchel* sol = nullptr;

string topDownMemo(vector <int> denoms, int problem, bool init) {
	string solution;
	int best = INT_MAX;
	
	//Only initialize array on first recursion
	if (sol == nullptr) {
		sol = new man_satchel[problem + 1]();
		//for (int i = 0; i <= problem; i++) {
		//	sol[i].value = -1;
		//}
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
		sol[problem].prevCoin += to_string(denoms[k]);
		//Add which object was used to get result
		if (coins != INT_MAX && (coins + 1) < best) {
			best = coins + 1;
		}
	}

	sol[problem].value = best;
	return to_string(sol[problem].value);
}*/

int main() {
	// Reading Input
	string line = "";
	vector <int> file;

	// From File

	ifstream input("test.txt", ios::in);
	while (getline(input, line)) {
		file.push_back(stoi(line, nullptr, 10));
	}

	/*
	for (int i = 0; i < file.size(); i++) {
		cout << file[i] << "\n";
	}
	*/

	// From stdin
	/*
	int x;
	cout << "Enter the input below: \n";
	while (cin >> x) {
		file.push_back(x);
	}
	*/

	//Get n from the first line of the input
	int n = file[0];
	//cout << "N: " << n << "\n";		//Print n

	//Populate denoms vector with the next n lines of input
	vector <int> denoms;
	for (int i = 1; i < (n + 1); i++) {
		denoms.push_back(file[i]);
	}
	/*
	for (int i = 0; i < denoms.size(); i++) {
		cout << "DENOMS[" << i << "]: " << denoms[i] << "\n";
	}
	*/

	//Get k from the n+1 line of input
	int k = file[n + 1];
	//cout << "K: " << k << "\n";		//Print k

	//Populate the problems vector with input lines from k to the end of input
	vector <int> problems;
	for (int i = (n + 2); i < (k + n + 2); i++) {
		problems.push_back(file[i]);
	}
	/*
	for (int i = 0; i < problems.size(); i++) {
		cout << "PROBLEMS[" << i << "]: " << problems[i] << "\n";
	}
	*/

	vector <string> solutions;
	// for (int i = 0; i < problems.size(); i++) {
	// 	solutions.push_back(bottomUp(denoms, problems[i]));
	// }
	//for (int i = 0; i < problems.size(); i++) {
	//	solutions.push_back(topDown(denoms, problems[i]));
	//}

	for (int i = 0; i < problems.size(); i++) {
		solutions.push_back(topDownMemo(denoms, problems[i], true));
	}

	for (int i = 0; i < solutions.size(); i++) {
		cout << "Solution for " << problems[i] << ": \n" << solutions[i] << "\n";
	}

	return 0;
}
