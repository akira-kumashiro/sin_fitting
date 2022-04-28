#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
class GetFolderFiles
{
private:
	
public:	
	//std::string folderPath;
	std::vector<std::filesystem::path> fileList;
	GetFolderFiles(std::string _folderPath);
	bool getFileNames(std::string folderPath);
};

