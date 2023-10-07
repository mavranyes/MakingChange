#include <iostream>

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	// Reading Input
	string line = "";
	vector <string> file;
		// From File
	
	ifstream input("test.txt", ios::in);
	while (getline(input, line)) {
		file.push_back(line);
		}
		
		// From stdin




	return 0;
}

