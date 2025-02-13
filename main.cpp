#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using std::string;

int main(int argc, char** argv) {

	string x;
	std::fstream file("main.cpp");

	while (std::getline(file, x)) {
		std::cout << x << '\n';
	}

	file.close();
	return 0;
}