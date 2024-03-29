#include "FileInput.h"

FileInput::FileInput(std::string _filename, int _oscilloscopeType)
{
	oscilloscopeType = _oscilloscopeType;
	fileData = dataInput(_filename);
	fileDataNom = getNormValue(fileData);
}

std::vector<std::vector<double>> FileInput::dataInput(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		std::cerr << "Could not open the file - '"
			<< filename << "'" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	std::vector<double> result;
	std::vector<std::vector<double>> fileData;
	if (oscilloscopeType == 0)
	{
		while (std::getline(ifs, line))
		{
			std::vector < std::string> strvec = split(line, ',');
			if (line.size() == 0)
			{
				break;
			}
			else
			{
				if (strvec[0].find("TraceName") != std::string::npos)
				{
					for (int i = 1; i < strvec.size(); i++)
					{
						std::string temp = strvec[i];
						temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
						traceName.push_back(temp);
					}
				}
				else if (strvec[0].find("HResolution") != std::string::npos)
				{
					resolution = stof(strvec[1]);
				}
			}

		}
		while (std::getline(ifs, line))
		{
			std::vector < std::string> strvec = split(line, ',');
			std::vector<double> lineData;
			for (int i = 0; i < strvec.size(); i++)
			{
				//printf("%5.4f", stof(strvec.at(i)));
				if (strvec.at(i).find(":") == std::string::npos)
					lineData.push_back(stof(strvec.at(i)));
				else
					timeStamp = strvec.at(i);
			}
			//puts("");
			fileData.push_back(lineData);
		}
	}
	else if (oscilloscopeType == 1)
	{
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strvec = split(line, ',');
			std::vector<double> lineData;
			/*
			0列：設定ヘッダ
			1列：設定数値
			2列：空き
			3列：時間
			4列：波形の値
			*/
			for (int i = 4; i < strvec.size(); i++)
			{
				lineData.push_back(stof(strvec.at(i)));
			}
			fileData.push_back(lineData);
			if (strvec[0].find("Source") != std::string::npos)
			{
				traceName.push_back(strvec[1]);
			}
			else if (strvec[0].find("Sample Interval") != std::string::npos)
			{
				resolution = stof(strvec[1]);
			}
		}
	}
	return fileData;
}

std::vector<std::string> FileInput::split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, delimiter))
	{
		result.push_back(field);
	}

	return result;
}

std::vector<double> FileInput::dataDivider(int line)
{
	return fileDataNom[line];
}

std::vector<std::vector<double>> FileInput::getNormValue(std::vector<std::vector<double>>)
{
	std::vector<std::vector<double>> result(fileData[0].size(), std::vector<double>(fileData.size()));

	for (int j = 0; j < fileData[0].size(); j++)
	{
		double average = 0.0;

		for (int i = 0; i < fileData.size(); i++)
		{
			result[j][i] = fileData[i][j];
			//average += value / fileData.size();
		}
		average = std::accumulate(result[j].begin(), result[j].end(), 0.0) / result[j].size();
		//printf("%f\n", average);
		for (int i = 0; i < result[j].size(); i++)
		{
			result[j][i] -= average;
			//printf("%f\n", result[j][i]);
		}
	}

	return result;
}

FileInput::~FileInput()
{
}
