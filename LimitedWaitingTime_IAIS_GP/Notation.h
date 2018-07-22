#pragma once

#ifndef _NOTATION_H //���û�ж�������� 
#define _NOTATION_H //���������
#include"GlobalHead.h"

//������������
class ENV
{
public:
	int n;
	vector<int> p1;
	vector<int> p2;
	vector<int> s1;
	vector<int> r;
	int W;
	int B;
	int A;
	int D;
	int C;
	int F;
	int G;
	clock_t start_time;
	clock_t end_time;
	int time_limit;
};
//���忹�����
class Antibody
{
public:
	//antibody �а�����id����
	vector<int> jobid;
	//bestobj
	double obj;
	//antibody��Ŀ��ֵ
	double GetSumCompletofSB(vector<int>& jobid,ENV& env);
	double GetSumCompletofBB(vector<int>& jobid, ENV& env);
};
//������Ⱥ
class Population
{
public:
	//ÿ����������antibody����
	vector<Antibody> pop;
	//��ѿ���
	Antibody bestbody;
};
//���������
class Generation
{
public:
	//��Ѹ���
	vector<Antibody> Bestbody;
	//���Ŀ��ֵ
	vector<double> Bestobj;
};
//��������
class Batch
{
public:
	int capacity;
	int sumofsecprocess;
	int maxsecprocess;
	int releasetime;
	int timeofbatchprocess;
	int sumofbatchsec;
	int FSUMPTB;
	int FMINPTB;
	int SMINPTB;
	int Priority;
	vector<int> jobid;
};
//���建����
class Buffer
{
public:
	vector<int> jobid;
	int getSPTnum(Buffer& buffer, ENV& env, ExpressionMgr * scheme);
	int getSPTnumsimple(Buffer& buffer, ENV& env);
};
#endif 