#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;

//This class is used in the recursive functions
//It fits right into the sol[] array to make implementation similar to BottomUp
class man_satchel {
public:
	int value;
	vector<int> coin;
	man_satchel() {
		this->value = -1;
	}
};

//Static array so recursive calls don't need the whole array passed to them
static man_satchel* sol = nullptr;

string bottomUp(vector <int> denoms, int problem) {
	string solution;
	int bestDenom;
	int sol[problem];
	int jmpSize[problem];
	sol[0] = 0;
	jmpSize[0] = 0;
	int best = INT_MAX;
	//Loop structure exhibits the "Bottom Up" nature of this solution
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
		return to_string(sol[problem].value);
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

string topDown(vector <int> denoms, int problem, bool init) {
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
	
	//Iterate through each denom
	for (int k = 0; k < denoms.size(); k++) {
		int size = problem - denoms[k];
		if (size < 0) {//Prevents evaluation of denoms that are too large
			continue;
		}
		int coins = stoi(topDown(denoms, size, false));
		
		if (coins != INT_MAX && (coins + 1) < best) {
			best = coins + 1;
			sol[problem].coin = sol[size].coin;
            sol[problem].coin[k]++;
		}
	}
	sol[problem].value = best;
	return to_string(sol[problem].value);
}

//Used to format data to put into graphs
void write2CSV(const string &filename, const vector<pair<int, int> > &data){
    ofstream f(filename);
    if(!f.is_open()){
        cerr << "Could not open csv file\n";
        return;}
    //Print the header row of the CSV file
    f << "n, Time\n"; 
    //Print to the file for each pair in the vector
    for(const auto &row : data){
        f << row.first << ", " << row.second << "\n";}
    f.close();
}

int main() {
	// Reading Input
	string line = "";
	vector <int> file;

	//Use this block to get input from test file
	ifstream input("test.txt", ios::in);
	while (getline(input, line)) {
		file.push_back(stoi(line, nullptr, 10));
	}
	
	// Use this block to use input from stdin
	// int x;
	// while (cin >> x) {
    	//  	file.push_back(x);
	// }

	//Get n from the first line of the input
	int n = file[0];

	//Populate denoms vector with the next n lines of input
	vector <int> denoms;
	for (int i = 1; i < (n + 1); i++) {
		denoms.push_back(file[i]);
	}

	//Get k from the n+1 line of input
	//int k = file[n + 1];

	//Populate the problems vector with input lines from k to the end of input
	vector <int> problems;
	for (int i = 0; i < 1000; i += 5) {
		problems.push_back(i);
	}

	vector <string> solutions;

	vector<pair<int, int> > deltaTimes;
	for (int i = 0; i < problems.size(); i++) {
	    // if (problems[i] > 70) {
	    //     continue;
	    // }
		auto start = chrono::high_resolution_clock::now();
		solutions.push_back(bottomUp(denoms, problems[i]));
		//solutions.push_back(topDownMemo(denoms, problems[i], true));
		//solutions.push_back(topDown(denoms, problems[i], true));
		auto end = chrono::high_resolution_clock::now();
        	auto timeDelta = chrono::duration_cast<chrono::microseconds>(end-start).count();
		deltaTimes.emplace_back(problems[i], timeDelta);

		//Print formatted output
		/*
		cout << problems[i] << " cents =";
		for (int j = denoms.size() - 1; j >= 0; j--) {
			if(sol[problems[i]].coin[j]){
				cout << " " << denoms[j] << ":" << sol[problems[i]].coin[j];
			}
		}
		cout << "\n";
		}*/
	
	write2CSV("BottomUp", deltaTimes);
	return 0;
}
