#include <cstdlib>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <format>

int main(int argc, char** argv) {

	char cwdBuf[MAX_PATH];
	GetModuleFileNameA(NULL, cwdBuf, MAX_PATH);
	bool out1 = std::filesystem::path(cwdBuf).parent_path().stem().string() == "out1";
	std::string root = std::filesystem::path(cwdBuf).parent_path().parent_path().parent_path().string();

	std::ofstream file(std::format("{}\\main.cpp", root), std::ios::app);
	file << "\n// this comment was added programmatically";
	file.close();

	system(std::format(
		"C:\\\"Program Files\"\\\"Microsoft Visual Studio\"\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\
		 && msbuild {}\\SMC.sln /t:Clean\
		 && msbuild {}\\SMC.sln /t:Build /p:Configuration=Release;OutDir={}\\build\\{}\\\
		 && start {}\\build\\{}\\SMC.exe",
		root, root, root, (out1 ? "out2" : "out1"), root, (out1 ? "out2" : "out1")).c_str());

	return 0;
}