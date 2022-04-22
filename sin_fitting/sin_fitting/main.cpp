#include "stdafx.h"
#include "GA.h"
#include"FileInput.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#define MAX_GENERATION 1000
#define MAX_GENOM_LIST 100
#define VAR_NUM 3	//�ϐ��̐�

//#define DEBUG
#define ENABLE_MUTATION

int main()
{
	double varMax[] = { 0.7,-100 ,51 };//Amp, phase(deg), freq(Hz)
	double varMin[] = { 0.02,-190 ,49 };//Amp, phase(deg), freq(Hz)
	std::vector<std::vector<GA::Data>> eliteData(24, std::vector<GA::Data>(2,GA::Data(VAR_NUM)));

	//�z���std::vector�֕ϊ�
	std::vector<double> vMax(varMax, std::end(varMax));
	std::vector<double> vMin(varMin, std::end(varMin));
	std::string folderTarget;
	std::cout << "�t�@�C���̃t���p�X�́H" << std::endl;
	std::cin >> folderTarget;
	for (int j = 0; j < eliteData.size(); j++)
	{
		std::ostringstream fileNumber;
		fileNumber << folderTarget << "\\" << std::setfill('0') << std::setw(2) << j + 1 << ".CSV";
		std::string fileFullPath = fileNumber.str();
		std::cout << fileFullPath << std::endl;

		FileInput fileio(fileFullPath);

		for (int i = 0; i < 2; i++)
		{
			GA ga(MAX_GENOM_LIST, VAR_NUM, vMax, vMin, fileio.dataDivider(i));//��`�I�A���S���Y�����֐����܂Ƃ߂��N���X�̐錾

		   //ga.init();//�ϐ��̏�����

			for (int i = 0; i <= MAX_GENERATION; i++)//���C���̃��[�v
			{
				bool change = ga.selection();//�I��

				ga.blxAlphaCrossover();//����
#ifdef ENABLE_MUTATION
				ga.mutation();//�ˑR�ψ�
				//ga.blxAlphaMutation();
#endif
#ifdef DEBUG
				if (i % (MAX_GENERATION / 10) == 0 || change)
				{
					//std::cout << "i=" << std::to_string(i) << std::endl;
					ga.calc(true);//�]���֐��̌v�Z
				}
				else
					ga.calc(false);//�]���֐��̌v�Z
#endif			
			}
			ga.eliteData.showData();
			eliteData[j][i] = ga.eliteData;
			eliteData[j][i].id = j + 1;
#ifdef DEBUG
			while (1)
				if (_kbhit() && _getch() == 27)
					break;
#endif
			puts("");
		}
	}
	printf(",Vamp,Vph,Vfreq,VfunctuonValue,Aamp,Aph,Afreq,AfunctuonValue\n");
	for (int i = 0; i < eliteData.size(); i++)
	{
		printf("%d,",eliteData[i][0].id);
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

