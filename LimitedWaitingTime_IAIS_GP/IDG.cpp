#include"IDG.h"

double random()
{
	//srand(seed);
	return (double)rand() / RAND_MAX;
}
int random(int p)
{
	return (int)(random()*(p - 1) + 0.5);
}
int uniform(int l, int u)
{
	return (int)random(u - l) + l;
}

void IDG_simple(vector<int> &n, vector<vector<int>>& p1, vector<vector<int>>& p2, vector<vector<int>>& s1, vector<vector<int>>& r, vector<int> &W, vector<int> &B, long seed)
{
	n.push_back(30);
	n.push_back(40);
	n.push_back(50);

	W.push_back(40);
	B.push_back(5);
	B.push_back(10);
	srand(seed);
	for (int numb = 0; numb < n.size(); numb++)
	{
		vector<int> p1mid;
		vector<int> p2mid;
		vector<int> s1mid;
		vector<int> rmid;
		for (int j = 0; j < n[numb]; j++)
		{
			p1mid.push_back(uniform(8, 48));
			p2mid.push_back(uniform(1, 25));
			s1mid.push_back(1);
			rmid.push_back(0);
		}
		p1.push_back(p1mid);
		p2.push_back(p2mid);
		s1.push_back(s1mid);
		r.push_back(rmid);
	}
}

void IDG_1(vector<int> &n, vector<vector<int>>& p1, vector<vector<int>>& p2, vector<vector<int>>& s1, vector<vector<int>>& r, vector<int> &W, vector<int> &B, long seed)
{
	n.push_back(10);
	n.push_back(20);
	n.push_back(50);

	W.push_back(40);
	B.push_back(5);
	B.push_back(10);
	srand(seed);
	for (int numb = 0; numb < n.size(); numb++)
	{
		vector<int> p1mid;
		vector<int> p2mid;
		vector<int> s1mid;
		vector<int> rmid;
		for (int j = 0; j < n[numb]; j++)
		{
			p1mid.push_back(uniform(8, 48));
			p2mid.push_back(uniform(1, 25));
			s1mid.push_back(1);
			rmid.push_back(0);
		}
		p1.push_back(p1mid);
		p2.push_back(p2mid);
		s1.push_back(s1mid);
		r.push_back(rmid);
	}
}

void IDG_2(vector<int> &n, vector<vector<int>>& p1, vector<vector<int>>& p2, vector<vector<int>>& s1, vector<vector<int>>& r, vector<int> &W, vector<int> &B, long seed)
{
	n.push_back(100);
	n.push_back(250);
	//n.push_back(500);

	W.push_back(40);
	B.push_back(5);
	B.push_back(10);
	srand(seed);
	for (int numb = 0; numb < n.size(); numb++)
	{
		vector<int> p1mid;
		vector<int> p2mid;
		vector<int> s1mid;
		vector<int> rmid;
		for (int j = 0; j < n[numb]; j++)
		{
			p1mid.push_back(uniform(8, 48));
			p2mid.push_back(uniform(1, 25));
			s1mid.push_back(1);
			rmid.push_back(0);
		}
		p1.push_back(p1mid);
		p2.push_back(p2mid);
		s1.push_back(s1mid);
		r.push_back(rmid);
	}
}
