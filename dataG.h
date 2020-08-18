#pragma once

#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

namespace GPG {
	typedef vector<string> vst;

	class GPU {
	public:
		char lsh;
		char rsh;
		pair<int, int> indlevs;
		unsigned int stateNum;
	};

	typedef vector<GPU> GPUs;

	typedef vector<GPUs> GPBs;

	class dataG {

	public:

		dataG(std::string filename) :fs(filename) {}

		string getCode();

		vst getAss(char label);

		void getGPUs();

		void getGPBs();

		bool isSS(GPU, GPU);

		GPU SScomp(GPU p, GPU& c);

		bool isTS(GPU, GPU);

		GPU TScomp(GPU, GPU&);

		void TSandSSop();

		void deadGPU();





	public:

		GPUs gpus;

		GPBs gpbs;

	private:

		fstream fs;

		string code;

		stringstream ss;

		vst stdAss;

		//GPU gpu;

	};

}