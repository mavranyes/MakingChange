#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <chrono>

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

	
	ifstream input("test.txt", ios::in);
	while (getline(input, line)) {
		file.push_back(stoi(line, nullptr, 10));
	}

	// From stdin
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
	for (int i = 0; i < 100; i += 5) {
		problems.push_back(i);
	}

	vector <string> solutions;

	vector<pair<int, int> > deltaTimes;
	for (int i = 0; i < problems.size(); i++) {
	    if (problems[i] > 80) {
	        continue;
	    }
		auto start = chrono::high_resolution_clock::now();
		solutions.push_back(topDown(denoms, problems[i], true));
		auto end = chrono::high_resolution_clock::now();
        auto timeDelta = chrono::duration_cast<chrono::microseconds>(end-start).count();
		deltaTimes.emplace_back(problems[i], timeDelta);
		// cout << problems[i] << " cents =";
		// for (int j = denoms.size() - 1; j >= 0; j--) {
		//     if(sol[problems[i]].coin[j]){
        //         cout << " " << denoms[j] << ":" << sol[problems[i]].coin[j];
		//     }
        // }
        // cout << "\n";
	}
	write2CSV("TopDown", deltaTimes);
	return 0;
}
