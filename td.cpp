#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class man_satchel {
public:
	int value;
	vector<int> coin;
	man_satchel() {
		this->value = -1;
	}
};

static man_satchel* sol = nullptr;

string topDownMemo(vector <int> denoms, int problem, bool init) {
	string solution;
	int best = INT_MAX;
	
	//Only initialize array on first recursion
	if (init) {
		if (sol != nullptr) {
			delete[] sol;
		}
		sol = new man_satchel[problem + 1]();
		for (int i = 0; i <= problem; i++) {
			sol[i].value = -1;
			sol[i].coin.resize(denoms.size(), 0);
		}
	}

	//Base
	if (problem == 0) {
		return to_string(problem);
	}
	//Check if solution is found
	if (sol[problem].value != -1) {
		//return to_string(sol[problem].value);
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
			sol[problem].coin = sol[size].coin;
            sol[problem].coin[k]++;
		}
	}
	sol[problem].value = best;
	return to_string(sol[problem].value);
}

int main() {
	// Reading Input
	string line = "";
	vector <int> file;

	// From stdin
	int x;
	while (cin >> x) {
     	file.push_back(x);
	}

	//Get n from the first line of the input
	int n = file[0];

	//Populate denoms vector with the next n lines of input
	vector <int> denoms;
	for (int i = 1; i < (n + 1); i++) {
		denoms.push_back(file[i]);
	}

	//Get k from the n+1 line of input
	int k = file[n + 1];

	//Populate the problems vector with input lines from k to the end of input
	vector <int> problems;
	for (int i = (n + 2); i < (k + n + 2); i++) {
		problems.push_back(file[i]);
	}

	vector <string> solutions;


	for (int i = 0; i < problems.size(); i++) {
		solutions.push_back(topDownMemo(denoms, problems[i], true));
		cout << problems[i] << " cents =";
		for (int j = denoms.size() - 1; j >= 0; j--) {
		    if(sol[problems[i]].coin[j]){
                cout << " " << denoms[j] << ":" << sol[problems[i]].coin[j];
		    }
        }
        cout << "\n";
	}

	return 0;
}
