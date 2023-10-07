#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



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


	int n = file[0];
	cout << "N: " << n << "\n";

	vector <int> denoms;
	for (int i = 1; i < n + 1; i++) {
		denoms.push_back(file[i]);
	}
	
	for (int i = 0; i < denoms.size(); i++) {
		cout << "DENOMS[" << i << "]: " << denoms[i] << "\n";
	}
	

	return 0;
}
