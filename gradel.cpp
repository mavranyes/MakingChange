#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

string bottomUp(vector <int> denoms, int problem) {
	string solution;
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
	solution = to_string(problem) + " cents =";
	int* denomCount = new int[denoms[denoms.size() - 1] + 1]();
	//Find purse
	while (problem != 0) {
		denomCount[jmpSize[problem]]++;
		problem -= jmpSize[problem];
	}
	//Format Purse output
	for (int i = denoms.size() - 1; i >= 0; i--) {
		if (denomCount[denoms[i]] != 0) {
			solution += " " + to_string(denoms[i]) + ":" + to_string(denomCount[denoms[i]]);
		}
	}
	return solution;
}

int main() {
	// Reading Input
	string line = "";
	vector <int> file;

	// From File
    /*
	ifstream input("test.txt", ios::in);
	while (getline(input, line)) {
		file.push_back(stoi(line, nullptr, 10));
	}
	*/

	/*
	for (int i = 0; i < file.size(); i++) {
		cout << file[i] << "\n";
	}
	*/

	// From stdin
	
	int x;
	while (cin >> x) {
		file.push_back(x);
	}
	

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
	for (int i = 0; i < problems.size(); i++) {
	 	solutions.push_back(bottomUp(denoms, problems[i]));
	 } 


	for (int i = 0; i < solutions.size(); i++) {
		cout << solutions[i] << "\n";
	}

	return 0;
}
