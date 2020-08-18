#include <string>

#include <fstream>

#include <sstream>

#include <vector>

#include "dataG.h"

#include <iterator>

#include <regex>

#include <iostream>

using namespace std;

using namespace GPG;

string dataG::getCode()
{

	ss << fs.rdbuf();

	code = ss.str();

	return dataG::code;
}

vst dataG::getAss(char label = '\n')
{

	string stm = "";

	string::iterator it = code.begin();

	for (; it != code.end(); it++)
	{

		if (*it != label)
		{

			stm += *it;
		}

		else
		{

			if (stm.find('=') != string::npos)
			{

				stm = stm.substr(stm.find_first_not_of(' '), stm.find_last_not_of(' ') + 1);

				stdAss.push_back(stm);
			}

			stm = "";
		}
	}

	return stdAss;
}

void dataG::getGPUs()
{

	for (string ele : stdAss)
	{

		string lop, rop;

		size_t offset = ele.find("=");

		string sleft = ele.substr(0, offset);

		string sright = ele.substr(offset + 1, ele.size());

		vector<int> ind(3, 0);

		for (int t = 0; t < sleft.size(); t++)
		{

			if (sleft[t] == '*')
			{
				ind[0]++;
				continue;
			}

			lop = sleft.substr(t, sleft.size());
			break;
		}

		for (int t = 0; t < sright.size(); t++)
		{

			if (sright[t] == '*')
			{
				ind[1]++;
				continue;
			}

			if (sright[t] == '&')
			{
				ind[2]++;
				continue;
			}

			rop = sright.substr(t, sright.size());
			break;
		}

		if (ind[0] != 0 && ind[1] != 0)
		{

			int little = ind[0] < ind[1] ? ind[0] : ind[1];

			ind[0] -= little;

			ind[1] -= little;
		}

		GPU gpu_temp;

		gpu_temp.lsh = *lop.c_str();

		gpu_temp.rsh = *rop.c_str();

		if (ind[2] == 1)
		{

			gpu_temp.indlevs.first = ind[0] + 1;

			gpu_temp.indlevs.second = ind[1];
		}

		else
		{

			gpu_temp.indlevs.first = ind[0] + 1;

			gpu_temp.indlevs.second = ind[1] + 1;
		}

		gpus.push_back(gpu_temp);
	}

	for (int i = 0; i < gpus.size(); i++)
	{

		gpus[i].stateNum = i;
	}
}

bool dataG::isSS(GPU p, GPU c)
{

	int l = p.indlevs.second;

	int k = p.indlevs.first;

	int j = c.indlevs.second;

	int i = c.indlevs.first;

	if (p.lsh == c.lsh && p.rsh != c.rsh)
	{

		if (l <= k && k < i)
		{

			return true;
		}
	}

	return false;
}

GPU dataG::SScomp(GPU p, GPU &c)
{

	int l = p.indlevs.second;

	int k = p.indlevs.first;

	int j = c.indlevs.second;

	int i = c.indlevs.first;

	c.lsh = p.rsh;

	c.indlevs.first = l + i - k;

	c.indlevs.second = j;

	//std::cout << "GPUc:" << c.lsh << c.indlevs.first << c.indlevs.second << c.rsh << endl;

	return c;
}

bool dataG::isTS(GPU p, GPU c)
{

	int l = p.indlevs.second;

	int k = p.indlevs.first;

	int j = c.indlevs.second;

	int i = c.indlevs.first;

	if (p.lsh == c.rsh && p.rsh != c.lsh)
	{

		if (l <= k && k <= j)
		{

			return true;
		}
	}

	return false;
}

GPU dataG::TScomp(GPU p, GPU &c)
{

	int l = p.indlevs.second;

	int k = p.indlevs.first;

	int j = c.indlevs.second;

	int i = c.indlevs.first;

	c.rsh = p.rsh;

	c.indlevs.second = l + j - k;

	//c.indlevs.second = j;

	return c;
}

void dataG::deadGPU()
{

	for (int m = 0; m < gpus.size(); m++)
	{
		GPU c = gpus[m];

		for (int n = m + 1; n < gpus.size(); n++)
		{

			GPU p = gpus[n];

			int l = p.indlevs.second;

			int k = p.indlevs.first;

			int j = c.indlevs.second;

			int i = c.indlevs.first;

			if (c.lsh == p.lsh && i == k && l == j && j != 2)
			{

				gpus.erase(gpus.begin() + m);
			}
		}
	}
}

void dataG::getGPBs()
{

	//GPU g;

	//gpbs = {};

	vector<int> flag(gpus.size(), 0);

	for (int i = 0; i < gpus.size(); i++)
	{

		if (flag[i] == 1)
			continue;

		GPUs gpus_temp;

		GPU f = gpus[i];

		gpus_temp.push_back(f);

		flag[i] = 1;

		for (int j = 1; j < gpus.size(); j++)
		{

			if (flag[j] == 1)
				continue;

			GPU h = gpus[j];

			if (f.lsh == h.lsh || f.lsh == h.rsh || f.rsh == h.rsh || f.rsh == h.lsh)
			{

				gpus_temp.push_back(h);

				flag[j] = 1;
			}
		}

		gpbs.push_back(gpus_temp);
	}
}

void dataG::TSandSSop()
{

	for (int i = 0; i < gpus.size(); i++)
	{

		for (int j = 0; j < gpus.size(); j++)
		{

			if (isSS(gpus[i], gpus[j]))
				SScomp(gpus[i], gpus[j]);

			if (isTS(gpus[i], gpus[j]))
				TScomp(gpus[i], gpus[j]);
		}
	}
}
