#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <filesystem>

class FileInput
{
private:

public:
	FileInput(std::string _filename,int _oscilloscopeType);

	std::vector<std::vector<double>> fileData;//CSV行数(CSV列数)
	std::vector<std::vector<double>> fileDataNom;//CSV列数(CSV行数)
	std::vector<std::vector<double>> dataInput(std::string filename);
	std::vector<std::string> split(std::string& input, char delimiter);
	std::vector<double> dataDivider(int line);
	std::vector<std::vector<double>> getNormValue(std::vector<std::vector<double>>);
	std::string timeStamp;
	double resolution;
	std::vector<std::string> traceName;
	int oscilloscopeType;
	~FileInput();
};

