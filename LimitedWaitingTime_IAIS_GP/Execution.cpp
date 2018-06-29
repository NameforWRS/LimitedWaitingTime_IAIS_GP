#include"IDG.h"
#include"SBIAIS.h"
#include"Notation.h"
#include"GBLWT.h"

//Control Console
int main()
{
	vector<int> n;
	vector<vector<int>> p1;
	vector<vector<int>> p2;
	vector<vector<int>> s1;
	vector<vector<int>> r;
	vector<int> W;
	vector<int> B;
	int A = 10;
	int N = 4;
	int R = 10;
	int seed = 1234567889;
	IDG_1(n, p1, p2, s1,r, W, B, seed);
	for (int i = 0; i < n.size(); i++)
	{
		for (int batch = 0; batch < B.size(); batch++)
		{
			cout << GBLWT(n[i], p1[i], p2[i], s1[i], r[i], W[i], B[batch]) << endl;
			cout << SBIAIS(n[i], p1[i], p2[i], s1[i],r[i], W[i], B[batch], A, N, R,10)<<endl;			
		}		
	}
	return 0;

}