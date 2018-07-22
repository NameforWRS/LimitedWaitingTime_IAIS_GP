#pragma once
#ifndef _GBLWT_H //���û�ж�������� 
#define _GBLWT_H //���������

#include"GlobalHead.h"
#include"Notation.h"
#include"IDG.h"
typedef map<string, Object> Environment;

double LB(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B);
double GBLWT_GP(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B,
	vector<ExpressionMgr *> scheme_batchformation, vector<ExpressionMgr *> scheme_batchsequence, vector<ExpressionMgr *> scheme_jobsequence);
double GBLWT(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B);
int Findbestpriority_batchformation(ExpressionMgr * scheme, Batch formedbatch, vector<int>& unshceduledjobs, ENV env);
string eval_batchformation(ExpressionMgr * &tree, Environment env, string RT, string FPT, string SPT, string FSUMPT, string FMAXPT, string FMINPT,
	string SSUMPT, string SMAXPT, string SMINPT, string RFSUMPT, string RFMAXPT, string RFMINPT, string RSSUMPT, string RSMAXPT, string RSMINPT);
string eval_batchsequence(ExpressionMgr * &tree, Environment env, string PTB, string FSUMPTB, string SSUMPTB, string FMINPTB, string SMINPTB,
	string SMAXPTB);
string eval_jobsequence(ExpressionMgr * &tree, Environment env, string RT, string PTS,
	string RSUMPTS, string RMINPTS, string RMAXPTS);
double Interpreter_batchformation(ExpressionMgr * scheme, string RT, string FPT, string SPT, string FSUMPT, string FMAXPT, string FMINPT,
	string SSUMPT, string SMAXPT, string SMINPT, string RFSUMPT, string RFMAXPT, string RFMINPT, string RSSUMPT, string RSMAXPT, string RSMINPT);
double Interpreter_batchsequence(ExpressionMgr * scheme, string PTB, string FSUMPTB, string SSUMPTB, string FMINPTB, string SMINPTB, string SMAXPTB);
double Interpreter_jobsequence(ExpressionMgr * scheme, string RT, string PTS, string RSUMPTS, string RMINPTS, string RMAXPTS);
#endif