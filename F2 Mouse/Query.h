#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define RESULT_NO 10

using namespace std;

//general sequence
class dataUnit
{
public:
	string word;
	int freq;
};
typedef vector<dataUnit> dataBlock; //ordered by first chara, last chara
typedef vector<dataUnit> q_Result; //first chara; second chara; length of index
class wordQuery 
{
	string input;
	int cap_flag;
	dataBlock wddb[26][26];
	q_Result qresult;
public:
	void loadIndex();   //step 0
	void refineInput(); //step 1
	bool isContainedWord(string l,string s); //middle
	void getQResult(string &input,q_Result& qResult);
};