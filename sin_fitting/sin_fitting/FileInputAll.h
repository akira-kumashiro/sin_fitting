#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>

class FileInputAll
{
public:
	FileInputAll(std::string _folderPath);

	std::vector<std::vector<double>> fileData;
	std::vector<std::vector<double>> fileDataNom;
	std::vector<std::vector<double>> dataInput(std::string filename);
	std::vector<std::string> split(std::string& input, char delimiter);
	std::vector<double> dataDivider(int line);
	std::vector<std::vector<double>> getNormValue(std::vector<std::vector<double>>);
	std::vector<std::string> getFileNames(std::string folderPath);
	~FileInputAll();
};

