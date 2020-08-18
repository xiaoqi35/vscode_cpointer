#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include"dataG.h"

using namespace std;
using namespace GPG;

int main() {
	//string filename = "assignment.txt";
	string filename = "source.txt";
	dataG mydata(filename);
	string code = mydata.getCode();
	cout << "---------------------source code---------------------------" << endl;
	cout << code << endl;
	vst stdAss = mydata.getAss('\n');
	cout << "--------------------standard assignment---------------------" << endl;
	for (auto a : stdAss) {
		cout << a << endl;
	}
	mydata.getGPUs();

	cout << "---------------------GPUs list---------------------------" << endl;

	for (auto gpu : mydata.gpus) {

		cout << gpu.stateNum << ": " << gpu.lsh << " " << gpu.indlevs.first << " " << gpu.indlevs.second << " " << gpu.rsh << endl;
	}
	mydata.TSandSSop();
	cout << "---------------------TS and SS GPUs list---------------------------" << endl;
	for (auto gpu : mydata.gpus) {

		cout << gpu.stateNum << ": " << gpu.lsh << " " << gpu.indlevs.first << " " << gpu.indlevs.second << " " << gpu.rsh << endl;
	}
	mydata.deadGPU();
	cout << "---------------------no dead GPUs list---------------------------" << endl;

	for (auto gpu : mydata.gpus) {

		cout << gpu.stateNum << ": " << gpu.lsh << " " << gpu.indlevs.first << " " << gpu.indlevs.second << " " << gpu.rsh << endl;
	}
	mydata.getGPBs();
	GPBs ss = mydata.gpbs;
	cout << "---------------------GPBs list---------------------------" << endl;
	for (auto s : ss) {
		for (auto t : s) {
			cout << t.stateNum << ":" << t.lsh << " " << t.indlevs.first << " " << t.indlevs.second << " " << t.rsh << endl;
		}
		cout << "--------------" << endl;
	}

	system("pause");
	return 0;
}
