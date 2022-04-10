#include "stdafx.h"
#include "Query.h"
//#include "F2 mouseDlg.h"

void wordQuery::loadIndex()
{
	string tword;
	int tfreq;
	char head=' ';
	char rear=' ';
	int indexh=0;
	int indexr=0;
	dataUnit tUnit;
	//load files into data
	ifstream infile("nywf.txt");
    while(!infile.eof())    
    {  
         infile>>tword;
		 infile>>tfreq;
		 head=tword.at(0);
		 rear=tword.at(tword.length()-1);
		 if(head>='a'&&head<='z')
		 {
			 tUnit.word=tword;
			 tUnit.freq=tfreq;
			 indexh=head-'a';
			 indexr=rear-'a';
			 wddb[indexh][indexr].push_back(tUnit);
		 }
		 else
		 {
			 //MessageBox(_T("wordselection error"));
		 }
		 //cout<<tword<<"	"<<tfreq<<endl;
	} 
    infile.close();
	//examine data
	/*
	for(int i=0;i<wddb['t'-'a']['y'-'a'].size();i++)
	{
		cout<<wddb['t'-'a']['y'-'a'].at(i).word<<"	"<<wddb['t'-'a']['y'-'a'].at(i).freq<<endl;
	}*/
}

void wordQuery::refineInput()
{
	//first & last ? ! , . dealt outside in MFC
	cap_flag=0;
	//all to lower case & Mark for recovery
	if(input.at(0)>='A'&&input.at(0)<='Z')
	{
		cap_flag=1;
		if(input.size()>1)
		{
			if(input.at(1)>='A'&&input.at(1)<='Z')
			    cap_flag=2;
		}
	}
	if(cap_flag==1)
		input.at(0)+=32;  //a---97 A----65
	if(cap_flag==2)
	for(int i=0;i<input.length();i++)
	    input.at(i)+=32;
}

bool wordQuery::isContainedWord(string l,string s)
{
	//build counting Matrix
    l=string(" ")+l;
	s=string(" ")+s;
	int column=l.length();
	int row=s.length();
	int **pMatrix=new int *[row];
	for(int i=0;i<row;i++)
	   pMatrix[i]=new int[column];
	//signal Matrix to retrive common subsequence
	int **sMatrix=new int *[row];
	for(int i=0;i<row;i++)
	   sMatrix[i]=new int[column];
    //initialization
	for(int i=0;i<row;i++)
		for(int j=0;j<column;j++)
		{
			pMatrix[i][j]=0;
			sMatrix[i][j]=0;
		}
    //dynamic programming find longest common subsequence
    for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(i==0||j==0)
			{
				pMatrix[i][j]=0;
			}
			if(i>0&&j>0&&l.at(j)==s.at(i))
			{
				pMatrix[i][j]=pMatrix[i-1][j-1]+1;
				sMatrix[i][j]=1;
			}
			if(i>0&&j>0&&l.at(j)!=s.at(i))
			{
				pMatrix[i][j]=(pMatrix[i][j-1]>pMatrix[i-1][j]?pMatrix[i][j-1]:pMatrix[i-1][j]); //selection expression 
				sMatrix[i][j]=(pMatrix[i][j-1]>pMatrix[i-1][j]?2:3);
			}
		}
	}
	//print result
	string retrivedword="";
	int prow=s.length()-1;
	int pcolumn=l.length()-1;
	while(prow>0&&pcolumn>0)
	{
		if(sMatrix[prow][pcolumn]==1)
		{
			retrivedword+=s.at(prow);
			prow--;
			pcolumn--;
		}
		if(sMatrix[prow][pcolumn]==2)
		{
			pcolumn--;
		}
		if(sMatrix[prow][pcolumn]==3)
		{
			prow--;
		}
	}
	//cout<<pMatrix[row-1][column-1]<<endl;
	reverse(retrivedword.begin(), retrivedword.end()); 
	//cout<<retrivedword<<endl;
	//judgement
	if(s.length()-1==pMatrix[row-1][column-1])
	{
		//delete counting Matrix
	    for(int i=0;i<row;i++)
	    {
		    delete pMatrix[i];
		    delete sMatrix[i];
	    }
	    delete pMatrix;
	    delete sMatrix;
		return true;
	}
	else
	{
		//delete counting Matrix
	    for(int i=0;i<row;i++)
	    {
		    delete pMatrix[i];
		    delete sMatrix[i];
	    }
	    delete pMatrix;
	    delete sMatrix;
		return false;
	}
}

void wordQuery::getQResult(string &in,q_Result& qResult)
{
	char ihead=' ';
	char irear=' ';
	int qwordlength=0;
	input=in;
	//q_Result tresult;
	//loadIndex();
	refineInput();
	ihead=input.at(0)-'a';
	irear=input.at(input.length()-1)-'a';
	qwordlength=input.length();
	dataUnit temp;

	//search in corresponding speed-up block
	int i;
	for(i=0;i<wddb[ihead][irear].size();i++)
	{
		temp=wddb[ihead][irear].at(i);
		if(temp.word.length()<=qwordlength&&isContainedWord(input,temp.word))
		{
			//restoration
			if(cap_flag==1)
				temp.word.at(0)-=32;
			if(cap_flag==2)
			{
				for(int j=0;j<temp.word.length();j++)
					temp.word.at(j)-=32;
			}
			qResult.push_back(temp);
		}
	}
	//check results
	/*
	for(int i=0;i<qResult.size();i++)
	{
		cout<<qResult.at(i).word<<"	"<<qResult.at(i).freq<<endl;
	}*/
}