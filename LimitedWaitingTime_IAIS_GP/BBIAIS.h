#pragma once

#include "IDG.h"
#include"Notation.h"

double BBIAIS(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B, int A, int D, int C, int timelimit);
void Isotype_Switching(Population& pop1, ENV& env);
void Process(ENV& env, Generation& TotalGen);
void IgA(Antibody& body, ENV& env);
void IgG(Antibody& body, ENV& env);
void IgE(Antibody& body, ENV& env);
bool operator <(const Batch &batch1, const Batch &batch2);

