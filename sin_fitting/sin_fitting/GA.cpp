#include "stdafx.h"
#include "GA.h"

GA::GA(int _max_genom_list, int _var_num, std::vector<double> _varMax, std::vector<double> _varMin, std::vector<double> _rawData) :
	data(std::vector<Data>(_max_genom_list, _var_num)),//data�̏�����
	eliteData(_var_num),
	rawData(_rawData.size(),0.0)
{
	//��������ϐ����N���X���ϐ��Ɋi�[
	max_genom_list = _max_genom_list;
	var_num = _var_num;
	varMax = _varMax;
	varMin = _varMin;

	rawData = _rawData;
#ifdef DEBUG
	for (int i = 0; i < 10; i++)
	{
		printf("%f\n", rawData[i]);
	}
#endif

	for (int i = 0; i < max_genom_list; i++)
	{
		for (int j = 0; j < var_num; j++)
		{
			data[i].x[j] = random(varMin[j], varMax[j]);//��`�q�̏����ݒ�
		}
	}
	prev_data = data;
	calcResult(true);
#ifdef DEBUG
	displayValues();
#endif
}

bool GA::init()
{
	for (int i = 0; i < max_genom_list; i++)
	{
		for (int j = 0; j < var_num; j++)
		{
			data[i].x[j] = random(varMin[j], varMax[j]);//��`�q�̏����ݒ�
			printf_s("%10.7lf", data[i].x[j]);
		}
		printf_s(" \t f(x,y)=%10.7lf\t Result=%10.7lf\n", data[i].functionValue, data[i].result);
	}
	prev_data = data;
	calcResult(true);
	return true;
}

bool GA::selection()
{
	int max_num = 0;//�ł��]���̗ǂ��̂̔ԍ�
	bool ret = false;

	calc(false);

	for (int i = 0; i < max_genom_list; i++)//���[���b�g�I��p�ɕ]���֐��̍��v�ƈ�ԕ]���̗ǂ��ԍ����擾
	{
		if (data[i].result > data[max_num].result)
			max_num = i;
	}

	eliteData = data[max_num];//�ł��]���̗ǂ��̂�ێ�
	if (prev_data[max_num].functionValue - eliteData.functionValue != 0)//�ł��]���̗ǂ��̂̕ω��̊Ď�(�f�o�b�O�p)
		ret = true;
	prev_data = data;
	for (int i = 0; i < max_genom_list; i++)
	{
		double selector = random(0.0, 1.0);//�����𐶐�
		double needle = 0;//���[���b�g�̐j�𐶐�
		int j = 0;
		for (; ; j++)
		{
			needle += (prev_data[j].result / resultSumValue);//���[���b�g�̐j�𗐐��̒l�܂Ői�߂�
			if (needle > selector)
				break;
			if (j == (max_genom_list - 1))
				break;
		}
		data[i] = prev_data[j];
	}
	return ret;
}

bool GA::blxAlphaCrossover()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2������
	{
		for (int j = 0; j < var_num; j++)
		{
			double ave = (data[i].x[j] + data[i + 1].x[j]) / 2;
			double length = std::abs((data[i].x[j] - data[i + 1].x[j]));

			data[i].x[j] = random(ave - length * (1 + alpha * 2) / 2, ave + length * (1 + alpha * 2) / 2);
			data[i + 1].x[j] = random(ave - length * (1 + alpha * 2) / 2, ave + length * (1 + alpha * 2) / 2);
		}
	}
	return true;
}

bool GA::mutation()
{
	for (int i = 0; i < max_genom_list; i++)
	{
		for (int j = 0; j < var_num; j++)
		{
			if (random(0.0, 1.0) <= individualMutationRate)//�̓ˑR�ψٗ��̌v�Z
			{
				double range = varMax[j] - varMin[j];
				data[i].x[j] += random(-0.005 * range, 0.005 * range);
				//blxAlphaMutation();
			}
		}
	}
	return true;
}

bool GA::blxAlphaMutation()
{
	prev_data = data;

	for (int i = 0; i < max_genom_list; i += 2)//2������
	{
		for (int j = 0; j < var_num; j++)
		{
			double ave = (data[i].x[j] + data[i + 1].x[j]) / 2;
			double length = std::abs((data[i].x[j] - data[i + 1].x[j])) * 10;

			data[i].x[j] = random(ave - length * (1 + alpha * 2) / 2, ave + length * (1 + alpha * 2) / 2);
			data[i + 1].x[j] = random(ave - length * (1 + alpha * 2) / 2, ave + length * (1 + alpha * 2) / 2);
		}
	}
	return true;
}

bool GA::calc(bool enableDisplay)
{
	calcResult(true);
	for (int i = 0; i < max_genom_list; i++)//�]���֐����ŏ��̓z�ƍő�̂������
	{
		if (data[i].result < data[minNum].result)
		{
			minNum = i;
		}
		if (data[i].result > data[maxNum].result)
		{
			maxNum = i;
		}
	}
	//�]���֐����ł��������ۑ�
	data[minNum] = eliteData;
	//printf("amp=%f,phase=%f,result=%f\n", data[minNum].x[0], data[minNum].x[1], data[minNum].result);

	calcResult(true);

	if (enableDisplay)
		displayValues();

	return true;
}

bool GA::calcResult(bool enableSort)
{
	int maxNum = 0;
	double seg;
	for (int i = 0; i < max_genom_list; i++)
	{
		data[i].functionValue = getFunctionErrorSum(data[i].x);
		if (data[maxNum].functionValue < data[i].functionValue)//���W�̒��ōł��֐����傫���������
		{
			maxNum = i;
		}
	}
	seg = data[maxNum].functionValue;//�]���֐��̐ؕЂ�^����ꂽ�֐����ł��傫����ɃZ�b�g
	resultSumValue = 0;

	for (int i = 0; i < max_genom_list; i++)
	{
		bool flag = true;
		double coefficient = 0.01;//�]���֐��p�̒萔
		for (int j = 0; j < var_num; j++)
		{
			if (data[i].x[j] > varMax[j] || data[i].x[j] < varMin[j])//���W����O�ɂ����̏���
				flag = false;
		}
		data[i].result = std::pow((data[i].functionValue - seg), 2.0);//�^����ꂽ�֐��̒l����ؕЂŐݒ肵���l��������2�悷�遨�^����ꂽ�֐��̒l����������������Ȃ�

		if (!flag)//��O�ɏo����̏���
			data[i].result *= coefficient;
		resultSumValue += data[i].result;
	}
	if (enableSort)
		std::sort(data.begin(), data.end(), [](const Data& x, const Data& y) { return x.functionValue > y.functionValue; });

	return true;
}

int GA::random(int min, int max)
{
	//�����̐ݒ�
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(engine);
}

double GA::random(int min, double max)
{
	return random((double)min, max);
}

double GA::random(double min, int max)
{
	return random(min, (double)max);
}

double GA::random(double min, double max)
{
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(engine);
}

bool GA::displayValues()
{
	/*for (int i = 0; i < max_genom_list; i++)
	{
		for (int j = 0; j < var_num; j++)
		{
			printf_s("%10.7lf,", data[i].x[j]);//�f�o�b�O�p
		}
		printf_s(" \t f(x,y)=%10.7lf\t Result=%10.7lf\n", data[i].functionValue, data[i].result);
	}*/

	for (int j = 0; j < var_num; j++)
	{
		printf_s("%10.7lf,", eliteData.x[j]);//�f�o�b�O�p
	}
	printf_s(" \t f(x,y)=%10.7lf\t Result=%10.7lf\n", eliteData.functionValue, eliteData.result);

	return true;
}

double GA::getFunctionErrorSum(std::vector<double> param)
{
	double result = 0.0;
	double omega;

	if (var_num == 3)
		omega = 2 * M_PI * param[2];
	else
		omega = 2 * M_PI * freq;

	for (int i = 0; i < rawData.size(); i++)
	{
		result += std::pow((param[0] * std::sin(omega * i * timeDiv + param[1] * M_PI / 180)) - rawData[i], 2.0);
	}
	return result;
}



GA::~GA()
{

}
