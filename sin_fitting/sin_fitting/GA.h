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
	int max_genom_list;//個体数
	int var_num;//座標の数
	double individualMutationRate = 0.1;//個体突然変異率
	int minNum = 0, maxNum = 0;
	double alpha = 0.5;
	std::vector<double> varMax, varMin;//変数の最小値・最大値
public:
	
	double timeDiv;// = 1.0e-4;
	double freq;// = 50;
	double resultSumValue;//評価関数の合計
	std::vector<double> rawData;//csvからの読み込み値
	class Data//データ格納用クラス
	{
	private:
		int var_num;//変数の数
	public:
		std::vector<double> x;//座標
		double functionValue;//与えられた関数の値
		double result;
		std::string id;
		std::string name;

		Data(int _var_num)//コンストラクタ
		{
			var_num = _var_num;
			functionValue = 0;
			result = 0;
			id = "";

			x.resize(var_num);//isIncludedの配列の長さの設定
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

	std::vector<Data> data, prev_data;//操作前後で値を保持するために2個
	Data eliteData;
	GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin, std::vector<double> _rawData);	//コンストラクタ
	bool init();//初期化
	bool selection();//選択

	bool blxAlphaCrossover();
	bool blxAlphaMutation();
	bool mutation();//突然変異
	bool calc(bool enableDisplay);//評価関数の計算
private:
	bool calcResult(bool enableSort);
	int random(int min, int max);
	double random(int min, double max);
	double random(double min, int max);
	double random(double min, double max);
	bool displayValues();
	double getFunctionErrorSum(std::vector<double> param);
; public:
	~GA();//デコンストラクタ
};


