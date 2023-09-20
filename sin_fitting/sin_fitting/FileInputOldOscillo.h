#pragma once
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
	FileInput(std::string _filename);

	std::vector<std::vector<double>> fileData;//CSVs”(CSV—ñ”)
	std::vector<std::vector<double>> fileDataNom;//CSV—ñ”(CSVs”)
	std::vector<std::vector<double>> dataInput(std::string filename);
	std::vector<std::string> split(std::string& input, char delimiter);
	std::vector<double> dataDivider(int line);
	std::vector<std::vector<double>> getNormValue(std::vector<std::vector<double>>);
	std::string timeStamp;
	double resolution;
	std::vector<std::string> traceName;
	~FileInput();
};


