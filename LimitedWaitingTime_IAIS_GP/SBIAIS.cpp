#include"SBIAIS.h"

/*
Parameter Setting
A: The number of poplation in each generation
N: The number of jobs selected in each antibody during Somatic Recombination
R: The number of repeated times during IgM
*/
double SBIAIS(int n,vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r,int W,int B,int A, int D, int C,int timelimit)
{
	clock_t startTime, endTime;
	startTime = clock();
	////////////////////////////////////////////////////////////////////////////
	//定义生产环境
	ENV env;
	env.B = B;
	env.n = n;
	env.p1 = p1;
	env.p2 = p2;
	env.s1 = s1;
	env.W = W;
	env.r = r;
	env.A = A;
	env.D = D;
	env.C = C;
	env.time_limit = timelimit;
	env.start_time = startTime;
	/////////////////////////////////////////////////////////////////////////////
	Generation TotalGen;	
	Process_SB(env, TotalGen);//运行一代
	endTime = clock();
	while ((double)(endTime - startTime) / CLOCKS_PER_SEC < env.time_limit
		&& count(TotalGen.Bestobj.begin(), TotalGen.Bestobj.end(), TotalGen.Bestobj[TotalGen.Bestobj.size() - 1]) < 2000)
	{
		Process_SB(env, TotalGen);
		endTime = clock();
	}	
	return  *std::min_element(std::begin(TotalGen.Bestobj), std::end(TotalGen.Bestobj));
}

void Process_SB(ENV& env, Generation& TotalGen)
{
	/*////////////////////////////////
	Step 1 Generate a poplution of A antibodies
	if the Totalgen has available antibodies, we choose the last antibody into the popultion generated sooner, otherwise, we 
	generate the full antibodies
	*/////////////////////////////////
	Population pop1;
	if (TotalGen.Bestbody.size() == 0)
	{
		for (int cycle = 0; cycle < env.A; cycle++)//cycle为生成A数量时的循环变量
		{
			Antibody body;
			for (int idnum = 0; idnum < env.n; idnum++)//idnum是生成抗体序列的循环变量
			{
				body.jobid.push_back(idnum);
			}
			pop1.pop.push_back(body);//将0123...n-1数列输入抗体个体中
			//将抗体数列进行转换，生成不同个体
			unsigned seed = 19960809;
			std::shuffle(pop1.pop[cycle].jobid.begin(), pop1.pop[cycle].jobid.end(), std::default_random_engine(seed));
		}
	}
	else
	{
		for (int cycle = 0; cycle < env.A - 1; cycle++)//cycle为生成A数量时的循环变量
		{
			Antibody body;
			for (int idnum = 0; idnum < env.n; idnum++)//idnum是生成抗体序列的循环变量
			{
				body.jobid.push_back(idnum);
			}
			pop1.pop.push_back(body);//将0123...n-1数列输入抗体个体中
			 //将抗体数列进行转换，生成不同个体
			unsigned seed = 19960809;
			std::shuffle(pop1.pop[cycle].jobid.begin(), pop1.pop[cycle].jobid.end(), std::default_random_engine(seed));
		}
		pop1.pop.push_back(TotalGen.Bestbody[TotalGen.Bestbody.size() - 1]);
	}
	/*////////////////////////////////
	Step 2 Calculate makespan of each antibody
	*/////////////////////////////////
	vector<double> objofpop1;
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		objofpop1.push_back(pop1.pop[i].GetSumCompletofSB(pop1.pop[i].jobid, env));
	}
	pop1.bestbody = pop1.pop[std::distance(std::begin(objofpop1), std::min_element(std::begin(objofpop1), std::end(objofpop1)))];
	pop1.bestbody.obj = *std::min_element(std::begin(objofpop1), std::end(objofpop1));
	/*////////////////////////////////
	Step 3 Somatic Recombination
	//随机挑选D个位置，进行Somatic Recombination
	*/////////////////////////////////
	vector<int> SelectedPosition;
	for (int i = 0; i < env.n; i++)
	{
		SelectedPosition.push_back(i);
	}
	random_shuffle(SelectedPosition.begin(), SelectedPosition.end());//随机生成1-N的元素，选取前D个
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		for (int j = 0; j < env.D; j++)
		{
			int Selectedid = pop1.bestbody.jobid[SelectedPosition[j]];//最好抗体相应位置的job代码
																	  //把抗体对应位置的元素和最佳抗体所找到的元素对调一下
			swap
			(
				pop1.pop[i].jobid[SelectedPosition[j]],
				pop1.pop[i].jobid[
					std::distance(std::begin(pop1.pop[i].jobid),
						find(pop1.pop[i].jobid.begin(), pop1.pop[i].jobid.end(), Selectedid)
					)
				]
			);
		}
	}
	/*////////////////////////////////
	Step 4 Somatic hypermutation
	///////进行IgM的Somatic hypermutation
	*/////////////////////////////////
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		//随机生成两个数M1,M2 in [1,n]
		random_shuffle(SelectedPosition.begin(), SelectedPosition.end());//随机生成1-N的元素，选取前2个
		int M1 = SelectedPosition[0];
		int M2 = SelectedPosition[1];
		reverse(pop1.pop[i].jobid.begin() + std::min(M1,M2), pop1.pop[i].jobid.begin() + std::max(M1,M2));//inverse
	}
	/*////////////////////////////////
	Step 5 Isotype Switching
	//Recombination IgM之后的个体通过Isotype Switching，直到获得比之前个体pop1更好的种群pop
	*/////////////////////////////////	
	Isotype_Switching_SB(pop1, env);
	Population pop = pop1;
	/*////////////////////////////////
	Step 6 Store the best antibody and makespan
	*/////////////////////////////////
	TotalGen.Bestbody.push_back(pop.bestbody);
	TotalGen.Bestobj.push_back(pop.bestbody.obj);
}

void Isotype_Switching_SB(Population& pop1, ENV& env)
{
	//找出初始种群的最佳个体
	vector<double> objofpop1_Somatic;
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		objofpop1_Somatic.push_back(pop1.pop[i].GetSumCompletofSB(pop1.pop[i].jobid, env));
	}
	while(*std::min_element(std::begin(objofpop1_Somatic), std::end(objofpop1_Somatic)) >= pop1.bestbody.obj)
	{
		clock_t end_time;
		end_time = clock();
		if (end_time - env.start_time > env.time_limit)
			return;
		objofpop1_Somatic.clear();
		objofpop1_Somatic.shrink_to_fit();
		for (int i = 0; i < pop1.pop.size(); i++)
		{
			for (int j = 0; j < env.C; j++)
			{
				srand(time(0));
				int random = rand() % 3 + 1;
				if (random == 1)
				{
					IgA_SB(pop1.pop[i],env);
				}
				if (random == 2)
				{
					IgE_SB(pop1.pop[i], env);
				}
				if (random == 3)
				{
					IgG_SB(pop1.pop[i], env);
				}
			}
			objofpop1_Somatic.push_back(pop1.pop[i].GetSumCompletofSB(pop1.pop[i].jobid, env));
		}	
	}
	return;
}
void IgA_SB(Antibody& body,ENV& env)
{
	int i = rand() % env.n;
	int j = rand() % env.n;
	body.jobid.erase(body.jobid.begin()+ std::distance(std::begin(body.jobid),find(body.jobid.begin(), body.jobid.end(), i)));
	body.jobid.insert(body.jobid.begin()+j, i);
}
void IgE_SB(Antibody& body, ENV& env)
{
	IgG_SB(body,env);
	IgA_SB(body, env);
}
void IgG_SB(Antibody& body, ENV& env)
{
	int i = rand() % env.n;
	int j = rand() % env.n;
	swap(body.jobid[i],body.jobid[j]);
}

//为保证map容器可以使用自定义的Batch变量，重新构建运载符<，
//说明详见： https://blog.csdn.net/q_l_s/article/details/52575924
//bool operator <(const Batch &batch1, const Batch &batch2)
//{
//	return true;
//}
//为直接使用map容器的性质，直接定义对比法则，在构建map的同时，直接对组批的releasetime进行排序
/*
如map形式为
BATCH1(RELEASETIME=5)
BATCH2(RELEASETIME=6)
BATCH3(RELEASETIME=3)
BATCH4(RELEASETIME=5)
使用对比法则后，map可直接变成
BATCH3 3
BATCH1 1
BATCH4 4
BATCH2 2
*/
struct CmpByRelease {
	bool operator()(const Batch& k1, const Batch& k2) const
	{
		return k1.releasetime < k2.releasetime;
	}
};

double Antibody::GetSumCompletofSB(vector<int>& job, ENV& env)
{
	//Initialization
	vector<Batch> FormedBatch;
	vector<int> unsheduledjobs;
	unsheduledjobs = job;

	/*////////////////////////////////////////////////
	Step 1 Group the jobs into batches
	*////////////////////////////////////////////////
	while (unsheduledjobs.size() > 0)
	{
		Batch CurrentBatch;//重新生成一批
		vector<int> record_earse;//记录unscheduledjobs被组批后的位置
		for (int i = 0; i < unsheduledjobs.size(); i++)//这里循环次数有点多，后期需调整
		{
			if (CurrentBatch.capacity == env.B)
			{
				break;
			}
			if (CurrentBatch.capacity + 1 < env.B&&CurrentBatch.sumofsecprocess + env.p2[unsheduledjobs[i]] <= env.W)//如果容量约束和等待约束均满足的话
			{
				CurrentBatch.jobid.push_back(unsheduledjobs[i]);//将满足的job加入新批中
				CurrentBatch.sumofsecprocess += env.p2[unsheduledjobs[i]];
				CurrentBatch.capacity++;
				record_earse.push_back(unsheduledjobs[i]);//记录job位置
			}
		}
		for (int i = 0; i < record_earse.size(); i++)
		{
			unsheduledjobs.erase(unsheduledjobs.begin() + std::distance(std::begin(unsheduledjobs), find(unsheduledjobs.begin(), unsheduledjobs.end(), record_earse[i])));//去除unscheduledjob已组批的job
		}
		FormedBatch.push_back(CurrentBatch);//所有组好的批全部进入FormedBatch中
	}

	/*////////////////////////////////////////////////
	Step 2 Sequence Batches Formed
	*////////////////////////////////////////////////

	//Step2.1 Caculate the release time of batch
	//Step2.2 Sequence the release time

	vector<int> ReleaseTime_T;//计算每批job的释放时间集合，为得到每批释放时间提供支持
	multimap<Batch, int, CmpByRelease> Sequence;//用multimap构建自动对releasetime进行排序的sequence
	for (int i = 0; i < FormedBatch.size(); i++)
	{
		vector<int> ReleaseTime;
		vector<int> BatchTime;
		for (int j = 0; j < FormedBatch[i].capacity; j++)
		{
			ReleaseTime.push_back(env.r[FormedBatch[i].jobid[j]]);
			BatchTime.push_back(env.p1[FormedBatch[i].jobid[j]]);
		}
		FormedBatch[i].releasetime = *std::min_element(std::begin(ReleaseTime), std::end(ReleaseTime));
		FormedBatch[i].timeofbatchprocess = *std::max_element(std::begin(BatchTime), std::end(BatchTime));
		Sequence.insert(make_pair(FormedBatch[i], i));//得到Batch和释放时间顺序的map集合，第一个sequence就是最早释放的
	}
	//获得依次加工的batch
	vector<Batch> AdjustedBatch;
	for (multimap<Batch, int>::iterator iter = Sequence.begin(); iter != Sequence.end(); ++iter)
	{
		AdjustedBatch.push_back((*iter).first);
	}
	/*////////////////////////////////////////////////
	Step 3 Calculate the sum of job completion time
	*////////////////////////////////////////////////
	int SimulatedTime = 0;//initial time is 0
	int finishedjob = 0;//the finished job number
	int finishedbatch = 1;//the finished batch number
	int currentbatch = 0;// the current batch number
	int TimeofStep1 = AdjustedBatch[0].timeofbatchprocess;
	int spaceofbuffer = 0;
	Buffer buffer;//the current jobs in the buffer
	vector<int> CmpofBatch;
	CmpofBatch.push_back(0);//第0批完成时间
	int Obj=0;
	vector<vector<int>> CmpofJob;
	while (1)
	{
		if (SimulatedTime >= std::max(TimeofStep1,CmpofBatch[finishedbatch-1])&&spaceofbuffer == 0)//when Step 1 is finished and buffer is empty, namely the batch is released
		{
			SimulatedTime = std::max(TimeofStep1, CmpofBatch[finishedbatch - 1]);
			for (int i = 0; i < AdjustedBatch[currentbatch].jobid.size(); i++)
			{
				buffer.jobid.push_back(AdjustedBatch[currentbatch].jobid[i]);
			}
			spaceofbuffer = buffer.jobid.size();//the job in the batch is released
			currentbatch += 1;//we put the next batch into batch processor
			if (currentbatch < AdjustedBatch.size())
			{
				TimeofStep1 = SimulatedTime + AdjustedBatch[currentbatch].timeofbatchprocess;//boom! The batch is finished
			}
		}
		if (spaceofbuffer>0 && finishedjob <= env.n)//when the Step 2 is available and buffer has jobs and the process is continued
		{
			while (buffer.jobid.size() > 0)
			{
				int goin = buffer.getSPTnumsimple(buffer,env);	
				buffer.jobid.erase(buffer.jobid.begin() + std::distance(std::begin(buffer.jobid), find(buffer.jobid.begin(), buffer.jobid.end(), goin)));//去除buffer中已加工的job
				//在离散机器加工
				vector<int> tmpcmp;
				tmpcmp.push_back(goin);
				SimulatedTime += env.p2[goin];
				Obj += SimulatedTime;//record the objective function
				tmpcmp.push_back(SimulatedTime);
				CmpofJob.push_back(tmpcmp);//完成了
				finishedjob++;//计数+1				
			}
			spaceofbuffer = buffer.jobid.size();//buffer is empty
			CmpofBatch.push_back(SimulatedTime);
			finishedbatch++;
		}
		SimulatedTime++;
		if (finishedjob == env.n)
		{
			break;
		}
	}
	return Obj;
}

//int Buffer::getSPTnum(Buffer& Current,ENV& env)
//{
//	vector<int> p2;
//	for (int i = 0; i < Current.jobid.size(); i++)
//	{
//		p2.push_back(env.p2[Current.jobid[i]]);
//	}
//	return Current.jobid[std::distance(std::begin(p2), std::min_element(std::begin(p2), std::end(p2)))];
//}