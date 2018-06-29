#pragma once
#ifndef _BBIAIS_H //���û�ж�������� 
#define _BBIAIS_H //���������

#include "IDG.h"
#include"Notation.h"

double BBIAIS(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B, int A, int D, int C, int F,int G, int timelimit);
void Isotype_Switching_BB(Population& pop1, ENV& env);
void Process_BB(ENV& env, Generation& TotalGen);
void IgA_BB(Antibody& body, ENV& env);
void IgG_BB(Antibody& body, ENV& env);
void IgE_BB(Antibody& body, ENV& env);
bool operator <(const Batch &batch1, const Batch &batch2);

#endif