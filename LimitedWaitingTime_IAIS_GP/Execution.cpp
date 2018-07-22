#include"IDG.h"
#include"BBIAIS.h"
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
	int F = 10;
	int G = 50;
	//int seed = 19960809;
	int seed = 464587;
	int timelimit = 20;

	//导入派单规则
	vector<string> code_batchformation;
	vector<string> code_batchsequence;
	vector<string> code_jobsequence;

	

	vector<ExpressionMgr> mgrset1;
	ExpressionMgr mgr1;
	mgrset1.push_back(mgr1);
	ExpressionMgr mgr2;
	mgrset1.push_back(mgr2);
	//ExpressionMgr mgr3;
	//mgrset1.push_back(mgr3);
	//ExpressionMgr mgr4;
	//mgrset1.push_back(mgr4);
	//ExpressionMgr mgr5;
	//mgrset1.push_back(mgr5);
	//ExpressionMgr mgr6;
	//mgrset1.push_back(mgr6);

	vector<ExpressionMgr> mgrset2;
	ExpressionMgr mgr7;
	mgrset2.push_back(mgr7);
	//ExpressionMgr mgr8;
	//mgrset2.push_back(mgr8);
	//ExpressionMgr mgr9;
	//mgrset2.push_back(mgr9);
	//ExpressionMgr mgr10;
	//mgrset2.push_back(mgr10);
	//ExpressionMgr mgr11;
	//mgrset2.push_back(mgr11);
	//ExpressionMgr mgr12;
	//mgrset2.push_back(mgr12);

	vector<ExpressionMgr> mgrset3;
	ExpressionMgr mgr13;
	mgrset3.push_back(mgr13);
	//ExpressionMgr mgr14;
	//mgrset3.push_back(mgr14);
	//ExpressionMgr mgr15;
	//mgrset3.push_back(mgr15);
	//ExpressionMgr mgr16;
	//mgrset3.push_back(mgr16);
	//ExpressionMgr mgr17;
	//mgrset3.push_back(mgr17);
	//ExpressionMgr mgr18;
	//mgrset3.push_back(mgr18);

	

	//batch formation
	code_batchformation.push_back("(- (+ (* (max (div SMAXPT RSMAXPT) (max (* FSUMPT RSMINPT) (max SMAXPT SMAXPT))) (- (+ (If SMAXPT RSMINPT (div RSSUMPT SMAXPT)) (- (max SMINPT (+ FMAXPT RSMAXPT)) (- SMAXPT FMAXPT))) (- (max (- SMAXPT FMAXPT) (If SMAXPT (div FPT FPT) (* RSMAXPT SPT))) (max (- FMINPT FPT) (div RFMINPT (- (max (+ RSMINPT SMAXPT) (- FMINPT FPT)) (max (max (max SMINPT SPT) RSMAXPT) (+ RSMINPT FMAXPT)))))))) (- (max SMINPT (max SMINPT SPT)) (- SMAXPT FMAXPT))) (- (max (- SMAXPT FMAXPT) (div SMINPT RFMINPT)) (max (- FMINPT FPT) (max (max (div RSMAXPT FPT) RSSUMPT) RSSUMPT))))");
	//code_batchformation.push_back("(- (+ (- (- (- SMAXPT FSUMPT) FSUMPT) (div (- (* (* (+ FPT (* (div (* FPT RFMINPT) (- SSUMPT RSSUMPT)) (- SMAXPT FSUMPT))) (+ SMINPT FMINPT)) (- SMAXPT FSUMPT)) (div (- SSUMPT RSSUMPT) RSMAXPT)) RSMAXPT)) (+ FPT (* (div (* (+ FPT (* (div (* (div (* FPT RFMINPT) (- SSUMPT RSSUMPT)) (- SMAXPT FSUMPT)) (- SSUMPT RSSUMPT)) (- SMAXPT FSUMPT))) RSSUMPT) (* (+ FPT (* (div (- (- (* RSMINPT (+ FPT RFMAXPT)) (div (div (div (* FMINPT (- SMINPT SMAXPT)) RSMAXPT) SMAXPT) RSMAXPT)) (div (div (* FMINPT FPT) RSMAXPT) SMAXPT)) (- (* RSMINPT (+ FPT RFMAXPT)) RSSUMPT)) (- SMAXPT FSUMPT))) (- SMAXPT FSUMPT))) (- SMAXPT FSUMPT)))) (* (* (+ FPT (* (div FSUMPT (- SSUMPT RSSUMPT)) (- (div (div (- SSUMPT RSSUMPT) SMAXPT) RSMAXPT) FSUMPT))) (+ SMINPT FMINPT)) (- SMAXPT FSUMPT)))");
	code_batchformation.push_back("(* FPT)");
	/*code_batchformation.push_back("(max (- (If (+ (* (+ (* FMINPT FMAXPT) (+ RSMINPT RFMINPT)) (+ (- RSMINPT SMINPT) (+ SMINPT SMAXPT))) (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ RSMINPT RFMINPT) (max (* FPT RFMAXPT) FMAXPT))) (If FPT RFMINPT RSMINPT) (If (* (- (- RSMINPT SMINPT) FMINPT) FSUMPT) (* (+ (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (* (- (+ SPT SMAXPT) (+ SPT SMAXPT)) (- SPT SSUMPT))) (+ (- (max SMAXPT FPT) SSUMPT) (- RSMINPT SMINPT))) (- RSMINPT (max (- (If (div SPT SSUMPT) (div (max SMAXPT FMAXPT) (* SPT FMAXPT)) (max SMAXPT (* SMAXPT FMINPT))) (+ RFMAXPT FPT)) (+ (max (- RSSUMPT (+ RFMAXPT FPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT))) (- RSMINPT (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT))))))) (div (max SMAXPT FMAXPT) (* SPT FMAXPT))) (* (* FSUMPT RFMAXPT) (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))))) (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT (* SPT FMAXPT))) (+ RFMAXPT FPT)) (+ (max (- RSSUMPT (+ RFMAXPT FPT)) (+ (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT (* SPT FMAXPT))) (+ RFMAXPT FPT)) (+ (max (- RSSUMPT (+ RFMAXPT FPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT))) (- RSMINPT (div SMAXPT FMAXPT)))) (- RSMINPT SMINPT))) (- RSMINPT (div SMAXPT FMAXPT))))) (* (div (+ SMINPT SMAXPT) (If (* (max SPT FMINPT) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))) FSUMPT))");

	code_batchformation.push_back("(max (- (If (+ (* (+ (* FMINPT FMAXPT) (+ RSMINPT RFMINPT)) (+ (- (* FSUMPT FMAXPT) (+ SPT SMAXPT)) (+ SMINPT SMAXPT))) (If (div (max (* (If SMINPT SMAXPT SMAXPT) (* FMINPT SMAXPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT))) (- FMAXPT SMAXPT)) (+ (+ SSUMPT SSUMPT) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) (max FMAXPT SMAXPT)))) (div (If (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT)) (If (* FSUMPT RFMAXPT) (* SMAXPT FMINPT) (If FPT RFMINPT RSMINPT)) (* (max SPT FMINPT) (max RSMINPT RSMINPT))) (max (max (- SMAXPT FSUMPT) (If FMAXPT SMAXPT FPT)) (If (+ FPT (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))) (- SSUMPT FPT) FMINPT))) (If (* (- (- SMAXPT FSUMPT) (+ RFMAXPT FPT)) FSUMPT) (* (- (+ SPT SMAXPT) (+ SPT SMAXPT)) (div (max SMAXPT FMAXPT) (* SPT FMAXPT))) (* (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))))) (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (+ RFMAXPT FPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT)))) (* (div (div SSUMPT SMINPT) (If (* (max SPT FMINPT) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))) (+ (* (- FMAXPT SMAXPT) (max FSUMPT RSMAXPT)) (If (max RFMAXPT SMAXPT) (- FPT RSMAXPT) (div SMINPT FMAXPT)))))");

	code_batchformation.push_back("(max (- (If (+ (* (+ (* FMINPT FMAXPT) (+ RSMINPT RFMINPT)) (+ (- RSMINPT SMINPT) (+ SMINPT SMAXPT))) (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ (+ RFMAXPT SMAXPT) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) FMAXPT))) (div (If (max SMAXPT FMAXPT) (If (* FSUMPT RFMAXPT) (* SMAXPT FMINPT) (If FPT RFMINPT RSMINPT)) (* (max SPT FMINPT) (max RSMINPT RSMINPT))) (max (* (max SPT FMINPT) RSMINPT) (If (+ FPT (* (div (+ SMINPT SMAXPT) (If (* (max SPT FMINPT) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))) FSUMPT)) (- SSUMPT FPT) (* SMINPT FMINPT)))) (If (* (- (- RSMINPT SMINPT) FMINPT) FSUMPT) (* (+ (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (* (- (+ SPT SMAXPT) (+ SPT SMAXPT)) (div (max SMAXPT FMAXPT) (* SPT FMAXPT)))) (+ (- SPT SSUMPT) (- RSMINPT SMINPT))) (- RSMINPT (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT)))) (+ RFMAXPT FPT)) (* (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ (+ RFMAXPT SMAXPT) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) FMAXPT)) (If (If FSUMPT SMINPT FMINPT) (- FMAXPT SMAXPT) (max FMINPT SMINPT))))) (max (- (If (div SPT SSUMPT) (div FSUMPT (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT)) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) FMAXPT))) (max SMAXPT (* SPT FMAXPT))) (+ RFMAXPT FPT)) (+ (max (- RSSUMPT (* SMINPT FMINPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT))) (- RSMINPT (div SMAXPT FMAXPT))))) (* (div (+ SMINPT SMAXPT) (If (* (If (+ FPT (+ SMINPT SMAXPT)) (- SSUMPT FPT) (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT (* SPT FMAXPT)))) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))) FSUMPT))");
	code_batchformation.push_back("(max (- (If (+ (* (+ (* FMINPT FMAXPT) (+ RSMINPT RFMINPT)) (+ (- (+ SPT SMAXPT) (div (+ SMINPT SMAXPT) (If (* (max SPT FMINPT) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT)))) (div (+ SMINPT SMAXPT) (If (* (max SPT FMINPT) RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))))) (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ (+ SSUMPT SSUMPT) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) FMAXPT))) (div (If (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT)) (If (* FSUMPT RFMAXPT) (* SMAXPT FMINPT) (If FPT RFMINPT RSMINPT)) (* (max SPT FMINPT) (max RSMINPT RSMINPT))) (max (max (- SMAXPT FSUMPT) (If FMAXPT SMAXPT FPT)) (If (+ FPT (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))) (- SSUMPT FPT) (* SMINPT FMINPT)))) (If (* (If FMAXPT SMAXPT FPT) FSUMPT) (* (- (+ SPT SMAXPT) (+ SPT SMAXPT)) (div (max SMAXPT FMAXPT) (* SPT FMAXPT))) (* (* FSUMPT RFMAXPT) (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))))) (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT (* SPT FMAXPT))) (+ RFMAXPT FPT)) (+ (max (- (If (div SPT SSUMPT) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (+ RFMAXPT FPT)) (- SPT SSUMPT)) (- RSMINPT RFMINPT)))) (* (div (+ SMINPT SMAXPT) (If (* (max SPT FMINPT) RSMINPT) (div RSMINPT SMAXPT) (max (div SPT SSUMPT) (If FMAXPT SMAXPT FPT)))) FSUMPT))");*/
	//code_batchformation.push_back("(max (- (If (+ (If FPT RFMINPT RSMINPT) (If (div (div RSMINPT SMAXPT) (- FMAXPT SMAXPT)) (+ (+ SSUMPT SSUMPT) (- SMAXPT FMINPT)) (max (* FPT RFMAXPT) (max FMAXPT SMAXPT)))) (div (If (div (+ RFMAXPT SMAXPT) (+ SMAXPT FSUMPT)) (If (+ FPT RSSUMPT) (* SMAXPT FMINPT) (If FPT RFMINPT RSMINPT)) (* (max SPT FMINPT) (max RSMINPT RSMINPT))) (max (max (- SMAXPT FSUMPT) (If FMAXPT SMAXPT FPT)) (If (+ FPT RSSUMPT) (- SSUMPT FPT) (* SMINPT FMINPT)))) (If (* (- (- SMAXPT FSUMPT) (+ (- (- (- SMAXPT FSUMPT) (+ RFMAXPT FPT)) (+ (+ RSMINPT RSMINPT) FPT)) FPT)) FSUMPT) (* (- (* FSUMPT FMAXPT) (+ SPT SMAXPT)) (div (max SMAXPT FMAXPT) (* SPT FMAXPT))) (* (If (div (* RSMAXPT SMAXPT) (If FMAXPT RSMINPT SMAXPT)) (div FSUMPT RFMAXPT) (max SMAXPT FPT)) (If (If FSUMPT SMINPT FMINPT) (div SSUMPT SMINPT) (max FMINPT SMINPT))))) (max (* (If SMINPT SMAXPT SMAXPT) (* FMINPT SMAXPT)) (+ (- SPT SSUMPT) (- RSMINPT SMINPT)))) (* (div (div (+ SMAXPT FSUMPT) (If FMAXPT RSMINPT SMAXPT)) (If (* SMAXPT RSMINPT) (If SMINPT RSSUMPT SSUMPT) (div SMAXPT FMAXPT))) (+ SMINPT SMAXPT)))");
	//
	//batch sequence
	//code_batchsequence.push_back("(* (max (- (If PTB PTB FMINPTB) (max (+ SSUMPTB (+ (div SMAXPTB PTB) (div FMINPTB FMINPTB))) (+ SSUMPTB SMINPTB))) (If PTB SMINPTB SSUMPTB)) (max (div (If PTB PTB (div FMINPTB FMINPTB)) (max (- (If PTB PTB FMINPTB) (max (max (- (If PTB PTB FMINPTB) (div SMAXPTB PTB)) (+ SSUMPTB SMINPTB)) (+ (If PTB SMINPTB SSUMPTB) SMAXPTB))) (+ SSUMPTB (If PTB SMINPTB SSUMPTB)))) (+ SSUMPTB (+ (div FMINPTB FMINPTB) (+ (max SSUMPTB (max (+ SSUMPTB SMINPTB) (If PTB SMINPTB (div SMAXPTB PTB)))) (If (* (+ FSUMPTB FSUMPTB) (div SMAXPTB PTB)) (+ SSUMPTB (+ (div SMAXPTB PTB) (div FMINPTB FMINPTB))) (If (* (+ FSUMPTB FSUMPTB) FMINPTB) (+ FSUMPTB FSUMPTB) (max (- (If PTB PTB FMINPTB) (div SMAXPTB PTB)) (+ SSUMPTB SMINPTB)))))))))");
	code_batchsequence.push_back("(div (+ SMAXPTB SSUMPTB) (+ (* (If (* (max SSUMPTB (* SSUMPTB (max (max SSUMPTB (If (max SSUMPTB (max SMAXPTB PTB)) (+ (* (- SSUMPTB PTB) (If (+ (max SSUMPTB SMINPTB) (max (max SSUMPTB SMINPTB) SMINPTB)) PTB (* SMAXPTB SMINPTB))) (max SMAXPTB PTB)) (* SMAXPTB SMINPTB))) SMINPTB))) (If (* (max SSUMPTB SMINPTB) (max (+ (* (- SSUMPTB PTB) (If (max SSUMPTB SMINPTB) (max SMAXPTB (* (* PTB (max SSUMPTB SMINPTB)) SMINPTB)) (max SMAXPTB SMAXPTB))) SMAXPTB) SMINPTB)) PTB SMAXPTB)) PTB (If (* (max SSUMPTB SMINPTB) (max SSUMPTB (If (max SSUMPTB SMINPTB) (max SMAXPTB (- (max SMAXPTB PTB) PTB)) SSUMPTB))) PTB (max SMAXPTB PTB))) (max SSUMPTB SMINPTB)) (max SMAXPTB PTB)))");
	code_batchsequence.push_back("(div SMAXPTB PTB)");
	//code_batchsequence.push_back("(* SSUMPTB)");
	//code_batchsequence.push_back("(* (- (div (max PTB SSUMPTB) (* SMINPTB SMAXPTB)) (max PTB (div FMINPTB SMAXPTB))) (div (+ FSUMPTB FMINPTB) FMINPTB))");
	//code_batchsequence.push_back("(- (max (* FSUMPTB (* PTB SMAXPTB)) (- (max SMAXPTB PTB) FMINPTB)) (max SSUMPTB (If (div (+ FMINPTB (If FSUMPTB SMINPTB SMINPTB)) (If (* FSUMPTB (* PTB SMAXPTB)) (* FSUMPTB (* SMINPTB SMAXPTB)) SMINPTB)) (div (* (div (* SMAXPTB (+ SSUMPTB SMINPTB)) (* SSUMPTB FMINPTB)) (* (If (+ SMAXPTB PTB) (max (div (+ PTB SMINPTB) (+ FMINPTB (* FSUMPTB (* PTB (If FMINPTB FSUMPTB FMINPTB))))) (* (max (If FSUMPTB SMAXPTB SSUMPTB) (* FSUMPTB (* PTB (max (* FSUMPTB (* PTB SMAXPTB)) (max (* FSUMPTB (* PTB SMAXPTB)) (- (* PTB SMAXPTB) FMINPTB)))))) (* (* PTB SMAXPTB) SMINPTB))) (If SSUMPTB (- FSUMPTB SMAXPTB) SSUMPTB)) SMAXPTB)) SMAXPTB) (* PTB SMAXPTB))))");

	//job sequence
	code_jobsequence.push_back("(* PTS)");

	vector<ExpressionMgr *> tree_batchformation;
	///将表达式转换为树
	for (int i = 0; i < code_batchformation.size(); i++)
	{
		tree_batchformation.push_back(mgrset1[i].ParseAsIScheme(code_batchformation[i]));
	}
	vector<ExpressionMgr *> tree_batchsequence;
	///将表达式转换为树
	for (int i = 0; i < code_batchsequence.size(); i++)
	{
		tree_batchsequence.push_back(mgrset2[i].ParseAsIScheme(code_batchsequence[i]));
	}
	vector<ExpressionMgr *> tree_jobsequence;
	///将表达式转换为树
	for (int i = 0; i < code_jobsequence.size(); i++)
	{
		tree_jobsequence.push_back(mgrset3[i].ParseAsIScheme(code_jobsequence[i]));
	}

	IDG_1(n, p1, p2, s1,r, W, B, seed);
	for (int i = 0; i < n.size(); i++)
	{
		for (int batch = 0; batch < B.size(); batch++)
		{
			for (int w = 0; w < W.size(); w++)
			{
				cout << GBLWT(n[i], p1[i], p2[i], s1[i], r[i], W[w], B[batch]) << endl;
				cout<< GBLWT_GP(n[i], p1[i], p2[i], s1[i], r[i], W[w], B[batch], tree_batchformation, tree_batchsequence, tree_jobsequence)<<endl;
				cout << BBIAIS(n[i], p1[i], p2[i], s1[i], r[i], W[w], B[batch], A, N, R, F, G, timelimit) << endl;
				cout << SBIAIS(n[i], p1[i], p2[i], s1[i], r[i], W[w], B[batch], A, N, R, timelimit) << endl;
				cout<< LB(n[i], p1[i], p2[i], s1[i], r[i], W[w], B[batch])<<endl;
				cout << endl;
			}	
		}
		
		
	}
	return 0;

}