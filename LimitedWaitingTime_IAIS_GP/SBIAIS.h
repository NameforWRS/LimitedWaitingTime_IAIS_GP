#pragma once
#ifndef _SBIAIS_H //如果没有定义这个宏 
#define _SBIAIS_H //定义这个宏

#include "BBIAIS.h"


double SBIAIS(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B, int A, int D, int C, int timelimit);
void Isotype_Switching_SB(Population& pop1, ENV& env);
void Process_SB(ENV& env, Generation& TotalGen);
void IgA_SB(Antibody& body, ENV& env);
void IgG_SB(Antibody& body, ENV& env);
void IgE_SB(Antibody& body, ENV& env);
//bool operator <(const Batch &batch1, const Batch &batch2);

#endif

