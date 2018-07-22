#include"GBLWT.h"


double LB(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B)
{
	vector<vector<double>> Obj_BB;
	vector<double> obj_temp;
	obj_temp.push_back(4772);
	obj_temp.push_back(4695);
	Obj_BB.push_back(obj_temp);
	obj_temp.clear();
	obj_temp.push_back(8138);
	obj_temp.push_back(7863);
	Obj_BB.push_back(obj_temp);
	obj_temp.clear();
	obj_temp.push_back(12169);
	obj_temp.push_back(11772);
	Obj_BB.push_back(obj_temp);

	//对特征点进行处理
	std::sort(p1.begin(), p1.end(), less<int>());
	std::sort(p2.begin(), p2.end(), less<int>());
	int nb = n / B;
	double LB1 = 0.0;
	for (int i = 0; i < nb; i++)
	{
		for (int j = i*B; j < (i + 1)*B; j++)
		{
			LB1 += (nb - i)*p1[j];
		}
	}
	for (int i = 0; i < B; i++)
	{
		for (int j = i*nb; j < (i + 1)*nb; j++)
		{
			LB1 += (B - i)*p2[j];
		}
	}
	double LB2 = 0.0;
	for (int j = 0; j < n; j++)
	{
		LB2 += p1[0] + (n - j)*p2[j];
	}
	return std::max(LB1,LB2);
}