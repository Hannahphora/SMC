#include <cstdlib>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <format>

int main(int argc, char** argv, char** envp) {

	// get path to executable
	char cwdBuf[100];
	GetModuleFileNameA(NULL, cwdBuf, 100);
	bool out1 = std::filesystem::path(cwdBuf).parent_path().stem().string() == "out1";
	std::string rootdir = std::filesystem::path(cwdBuf).parent_path().parent_path().parent_path().string();

	// open main.cpp
	std::fstream file(std::format("{}\\src\\main.cpp", rootdir));
	if (!file.good()) {
		std::cout << "failed to open main.cpp\n";
		return -1;
	}
	
	// print contents of main.cpp
	std::string prtstr;
	while (std::getline(file, prtstr)) std::cout << prtstr << '\n';
	file.close();

	// recompile source, to out2 if currently running from out1 and vice versa
	system(std::format(
		"C:\\\"Program Files\"\\\"Microsoft Visual Studio\"\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\
		 && msbuild {}\\SMC.sln -t:Clean\
		 && msbuild {}\\SMC.vcxproj /t:Build /p:Configuration=Release;OutDir={}\\build\\{}\\",
		rootdir, rootdir, rootdir, (out1 ? "out2" : "out1")).c_str());

	std::cout << "\n" << (out1 ? "out2 recompiled from out1" : "out1 recompiled from out2") << '\n';
	system("pause");

	system(std::format("start {}\\build\\{}\\SMC.exe", rootdir, (out1 ? "out2" : "out1")).c_str());

	return 0;
}