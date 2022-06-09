#pragma once

#include<vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <sstream>

class GA
{
private:
	int max_genom_list;//�̐�
	int var_num;//���W�̐�
	double individualMutationRate = 0.1;//�̓ˑR�ψٗ�
	int minNum = 0, maxNum = 0;
	double alpha = 0.5;
	std::vector<double> varMax, varMin;//�ϐ��̍ŏ��l�E�ő�l
public:
	
	double timeDiv;// = 1.0e-4;
	double freq;// = 50;
	double resultSumValue;//�]���֐��̍��v
	std::vector<double> rawData;//csv����̓ǂݍ��ݒl
	class Data//�f�[�^�i�[�p�N���X
	{
	private:
		int var_num;//�ϐ��̐�
	public:
		std::vector<double> x;//���W
		double functionValue;//�^����ꂽ�֐��̒l
		double result;
		std::string id;
		std::string name;

		Data(int _var_num)//�R���X�g���N�^
		{
			var_num = _var_num;
			functionValue = 0;
			result = 0;
			id = "";

			x.resize(var_num);//isIncluded�̔z��̒����̐ݒ�
		}
		void showData()
		{
			printf("apm,ph,functionValue\n");
			for (int i = 0; i < x.size(); i++)
			{
				printf("%8.7f,", x[i]);
			}
			printf("%8.7f\n", functionValue);
		}

		~Data()
		{
			//std::cout << "deleted" << std::endl;
		}
	};

	std::vector<Data> data, prev_data;//����O��Œl��ێ����邽�߂�2��
	Data eliteData;
	GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin, std::vector<double> _rawData);	//�R���X�g���N�^
	bool init();//������
	bool selection();//�I��

	bool blxAlphaCrossover();
	bool blxAlphaMutation();
	bool mutation();//�ˑR�ψ�
	bool calc(bool enableDisplay);//�]���֐��̌v�Z
private:
	bool calcResult(bool enableSort);
	int random(int min, int max);
	double random(int min, double max);
	double random(double min, int max);
	double random(double min, double max);
	bool displayValues();
	double getFunctionErrorSum(std::vector<double> param);
; public:
	~GA();//�f�R���X�g���N�^
};


