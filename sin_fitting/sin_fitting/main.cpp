#include "stdafx.h"
#include "GA.h"
#include"FileInput.h"
#include"GetFolderFiles.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#define MAX_GENERATION 1000
#define MAX_GENOM_LIST 100
#define VAR_NUM 2	//変数の数
#define FREQ 50

//#define DEBUG
#define ENABLE_MUTATION

int main()
{
	double varMax[] = { 10.0,180.0 ,51 };//Amp, phase(deg), freq(Hz)
	double varMin[] = { 0,-180.0 ,49 };//Amp, phase(deg), freq(Hz)


	//配列をstd::vectorへ変換
	std::vector<double> vMax(varMax, std::end(varMax));
	std::vector<double> vMin(varMin, std::end(varMin));
	std::string folderTarget;
	std::cout << "ファイルのフルパスは？" << std::endl;
	std::cin >> folderTarget;
	//std::cout << folderTarget << std::endl;
	GetFolderFiles folderFilesList(folderTarget);

	FileInput fileIOTemp(folderFilesList.fileList[0].string());

	std::vector<std::vector<GA::Data>> eliteData(folderFilesList.fileList.size(), std::vector<GA::Data>(fileIOTemp.fileDataNom.size(), GA::Data(VAR_NUM)));

	for (int fileNumber = 0; fileNumber < folderFilesList.fileList.size(); fileNumber++)
	{
		/*std::ostringstream fileNumber;
		fileNumber << folderTarget << "\\" << std::setfill('0') << std::setw(2) << j + 1 << ".CSV";
		std::string fileFullPath = fileNumber.str();
		std::cout << fileFullPath << std::endl;*/

		//FileInput fileio(fileFullPath);
		FileInput fileio(folderFilesList.fileList[fileNumber].string());
		std::cout << folderFilesList.fileList[fileNumber] << std::endl;

		for (int dataNumber = 0; dataNumber < fileio.fileDataNom.size(); dataNumber++)
		{
			GA ga(MAX_GENOM_LIST, VAR_NUM, vMax, vMin, fileio.dataDivider(dataNumber));//遺伝的アルゴリズム諸関数をまとめたクラスの宣言
			ga.timeDiv = fileio.resolution;
			ga.freq = FREQ;
			//ga.init();//変数の初期化

			for (int epoch = 0; epoch <= MAX_GENERATION; epoch++)//メインのループ
			{
				bool change = ga.selection();//選択

				ga.blxAlphaCrossover();//交叉
#ifdef ENABLE_MUTATION
				ga.mutation();//突然変異
				//ga.blxAlphaMutation();
#endif
#ifdef DEBUG
				if (epoch % (MAX_GENERATION / 10) == 0)// || change
				{
					std::cout << "itr=" << std::to_string(epoch)<<"	";
					ga.calc(true);//評価関数の計算
				}
				else
					ga.calc(false);//評価関数の計算
#endif			
			}
			ga.eliteData.showData();
			eliteData[fileNumber][dataNumber] = ga.eliteData;
			eliteData[fileNumber][dataNumber].id = folderFilesList.fileList[fileNumber].filename().string() + "," + fileio.timeStamp;
			eliteData[fileNumber][dataNumber].name = fileio.traceName[dataNumber];
#ifdef DEBUG
			while (1)
				if (_kbhit() && _getch() == 27)
					break;
#endif			
		}
		puts("");
	}
	std::vector<std::string> identifier = { "amp","ph","functuonValue" };
	std::cout << "fileName,timeStamp,";
	for (int dataNumber = 0; dataNumber < eliteData[0].size(); dataNumber++)
	{
		for (int optParam = 0; optParam < identifier.size(); optParam++)
		{
			std::cout << eliteData[0][dataNumber].name + identifier[optParam] << ",";
		}
	}
	std::cout << std::endl;
	for (int fileNumber = 0; fileNumber < eliteData.size(); fileNumber++)
	{
		std::cout << eliteData[fileNumber][0].id << ",";
		for (int dataNumber = 0; dataNumber < eliteData[fileNumber].size(); dataNumber++)
		{
			for (int optParam = 0; optParam < eliteData[fileNumber][dataNumber].x.size(); optParam++)
			{
				printf("%8.7f,", eliteData[fileNumber][dataNumber].x[optParam]);
			}
			printf("%8.7f,", eliteData[fileNumber][dataNumber].functionValue);
		}
		puts("");
	}
	return 0;
}

