#include "FileInput.h"

FileInput::FileInput(std::string _filename)
{
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
	while (std::getline(ifs, line))
	{
		std::vector < std::string> strvec = split(line, ',');
		std::vector<double> lineData(2);
		if (line.size() == 0)
		{
			//printf("null!\n");
			break;
		}
		/*else
		{
			std::cout << line << std::endl;
		}*/
	}
	while (std::getline(ifs, line))
	{
		std::vector < std::string> strvec = split(line, ',');
		std::vector<double> lineData(2);
		for (int i = 1; i < 3; i++)
		{
			//printf("%5.4f", stof(strvec.at(i)));
			lineData[i - 1] = stof(strvec.at(i));
		}
		//puts("");
		fileData.push_back(lineData);
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
	std::vector<std::vector<double>> result(fileData[0].size(),std::vector<double>(fileData.size()));
	double average = 0.0;
	for (int j = 0; j < fileData[0].size(); j++)
	{
		for (int i = 0; i < fileData.size(); i++)
		{
			double value = fileData[i][j];
			result[j][i]=value;
			average += value / fileData.size();
		}
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
