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
#define FREQ 1000

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

	for (int j = 0; j < folderFilesList.fileList.size(); j++)
	{
		/*std::ostringstream fileNumber;
		fileNumber << folderTarget << "\\" << std::setfill('0') << std::setw(2) << j + 1 << ".CSV";
		std::string fileFullPath = fileNumber.str();
		std::cout << fileFullPath << std::endl;*/

		//FileInput fileio(fileFullPath);
		FileInput fileio(folderFilesList.fileList[j].string());
		std::cout << folderFilesList.fileList[j] << std::endl;

		for (int i = 0; i < fileio.fileDataNom.size(); i++)
		{
			GA ga(MAX_GENOM_LIST, VAR_NUM, vMax, vMin, fileio.dataDivider(i));//遺伝的アルゴリズム諸関数をまとめたクラスの宣言
			ga.timeDiv = fileio.resolution;
			ga.freq = FREQ;
			//ga.init();//変数の初期化

			for (int i = 0; i <= MAX_GENERATION; i++)//メインのループ
			{
				bool change = ga.selection();//選択

				ga.blxAlphaCrossover();//交叉
#ifdef ENABLE_MUTATION
				ga.mutation();//突然変異
				//ga.blxAlphaMutation();
#endif
#ifdef DEBUG
				if (i % (MAX_GENERATION / 10) == 0 || change)
				{
					//std::cout << "i=" << std::to_string(i) << std::endl;
					ga.calc(true);//評価関数の計算
				}
				else
					ga.calc(false);//評価関数の計算
#endif			
			}
			ga.eliteData.showData();
			eliteData[j][i] = ga.eliteData;
			eliteData[j][i].id = folderFilesList.fileList[j].filename().string() + "," + fileio.timeStamp;
			eliteData[j][i].name = fileio.traceName[i];
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
	for (int i = 0; i < eliteData[0].size(); i++)
	{
		for (int j = 0; j < identifier.size(); j++)
		{
			std::cout << eliteData[0][i].name + identifier[j] << ",";
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < eliteData.size(); i++)
	{
		std::cout << eliteData[i][0].id << ",";
		for (int j = 0; j < eliteData[i].size(); j++)
		{
			for (int k = 0; k < eliteData[i][j].x.size(); k++)
			{
				printf("%8.7f,", eliteData[i][j].x[k]);
			}
			printf("%8.7f,", eliteData[i][j].functionValue);
		}
		puts("");
	}
	return 0;
}

