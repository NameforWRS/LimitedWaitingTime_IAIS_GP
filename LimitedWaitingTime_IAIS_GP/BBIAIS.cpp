#include"BBIAIS.h"


/*
Parameter Setting
A: The number of poplation in each generation
N: The number of jobs selected in each antibody during Somatic Recombination
R: The number of repeated times during IgM
*/


double BBIAIS(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B, int A, int D, int C, int F, int G, int timelimit)
{
	clock_t startTime, endTime;
	startTime = clock();
	////////////////////////////////////////////////////////////////////////////
	//������������
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
	env.F = F;
	env.G = G;
	env.time_limit = timelimit;
	env.start_time = startTime;
	/////////////////////////////////////////////////////////////////////////////
	Generation TotalGen;
	Process_BB(env, TotalGen);//����һ��
	endTime = clock();
	int i = 0;
	
	while ((double)(endTime - startTime) / CLOCKS_PER_SEC < env.time_limit
		&& count(TotalGen.Bestobj.begin(), TotalGen.Bestobj.end(), TotalGen.Bestobj[TotalGen.Bestobj.size() - 1]) < 2000)
	{
		i++;
		Process_BB(env, TotalGen);
		endTime = clock();
	}
	return  *std::min_element(std::begin(TotalGen.Bestobj), std::end(TotalGen.Bestobj));
}

void Process_BB(ENV& env, Generation& TotalGen)
{
	/*////////////////////////////////
	Step 1 Generate a poplution of A antibodies
	if the Totalgen has available antibodies, we choose the last antibody into the popultion generated sooner, otherwise, we
	generate the full antibodies
	*/////////////////////////////////
	Population pop1;
	if (TotalGen.Bestbody.size() == 0)
	{
		for (int cycle = 0; cycle < env.A; cycle++)//cycleΪ����A����ʱ��ѭ������
		{
			Antibody body;
			for (int idnum = 0; idnum < env.n; idnum++)//idnum�����ɿ������е�ѭ������
			{
				body.jobid.push_back(idnum);//BB��ʽ�£�����ȫΪ0�ĸ���
			}
			pop1.pop.push_back(body);//��0�������뿹�������
									 //���������н���ת�������ɲ�ͬ����
									 //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			unsigned seed = 12345;
			std::shuffle(pop1.pop[cycle].jobid.begin(), pop1.pop[cycle].jobid.end(), std::default_random_engine(seed));
		}
	}
	else
	{
		for (int cycle = 0; cycle < env.A - 1; cycle++)//cycleΪ����A����ʱ��ѭ������
		{
			Antibody body;
			for (int idnum = 0; idnum < env.n; idnum++)//idnum�����ɿ������е�ѭ������
			{
				body.jobid.push_back(idnum);
			}
			pop1.pop.push_back(body);//��0�������뿹�������
									 //���������н���ת�������ɲ�ͬ����
									 //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			unsigned seed = 12345;
			std::shuffle(pop1.pop[cycle].jobid.begin(), pop1.pop[cycle].jobid.end(), std::default_random_engine(seed));
		}
		pop1.pop.push_back(TotalGen.Bestbody[TotalGen.Bestbody.size() - 1]);
	}
	/*////////////////////////////////
	Step 2 Calculate makespan of each antibody
	*/////////////////////////////////
	vector<double> objofpop1;

	for (int i = 0; i < pop1.pop.size() - 1; i++)
	{
		//vector<int> newjob;
		InvertSBtoBB(pop1.pop[i].jobid, env);
		objofpop1.push_back(pop1.pop[i].GetSumCompletofBB(pop1.pop[i].jobid, env));
	}
	if (TotalGen.Bestbody.size() == 0)
	{
		InvertSBtoBB(pop1.pop[pop1.pop.size() - 1].jobid, env);
		objofpop1.push_back(pop1.pop[pop1.pop.size() - 1].GetSumCompletofBB(pop1.pop[pop1.pop.size() - 1].jobid, env));
	}
	else
	{
		//it is no neccessary to invert the SB to BB
		objofpop1.push_back(pop1.pop[pop1.pop.size() - 1].GetSumCompletofBB(pop1.pop[pop1.pop.size() - 1].jobid, env));
	}
	pop1.bestbody = pop1.pop[std::distance(std::begin(objofpop1), std::min_element(std::begin(objofpop1), std::end(objofpop1)))];
	pop1.bestbody.obj = *std::min_element(std::begin(objofpop1), std::end(objofpop1));
	/*////////////////////////////////
	Step 3 Somatic Recombination
	//�����ѡD��λ�ã�����Somatic Recombination
	*/////////////////////////////////
	vector<int> SelectedPosition;
	for (int i = 0; i < env.n; i++)
	{
		SelectedPosition.push_back(i);
	}
	random_shuffle(SelectedPosition.begin(), SelectedPosition.end());//�������1-N��Ԫ�أ�ѡȡǰD��
																	 /////////////////here
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		for (int j = 0; j < env.D; j++)
		{
			int Selectedid = pop1.bestbody.jobid[SelectedPosition[j]];//��ÿ�����Ӧλ�õ�job����
																	  //�ѿ����Ӧλ�õ�Ԫ�غ���ѿ������ҵ���Ԫ�ضԵ�һ��
			if (find(pop1.pop[i].jobid.begin(), pop1.pop[i].jobid.end(), Selectedid) != pop1.pop[i].jobid.end())
			{
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
	}
	/*////////////////////////////////
	Step 4 Somatic hypermutation
	///////����IgM��Somatic hypermutation
	*/////////////////////////////////
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		//�������������M1,M2 in [1,n]
		random_shuffle(SelectedPosition.begin(), SelectedPosition.end());//�������1-N��Ԫ�أ�ѡȡǰ2��
		int M1 = SelectedPosition[0];
		int M2 = SelectedPosition[1];
		reverse(pop1.pop[i].jobid.begin() + std::min(M1, M2), pop1.pop[i].jobid.begin() + std::max(M1, M2));//inverse
	}
	/*////////////////////////////////
	Step 5 Isotype Switching
	//Recombination IgM֮��ĸ���ͨ��Isotype Switching��ֱ����ñ�֮ǰ����pop1���õ���Ⱥpop
	*/////////////////////////////////	
	//Isotype_Switching_BB(pop1, env);

	Population pop = pop1;
	/*////////////////////////////////
	Step 6 Store the best antibody and makespan
	*/////////////////////////////////
	TotalGen.Bestbody.push_back(pop.bestbody);
	TotalGen.Bestobj.push_back(pop.bestbody.obj);
}

void Isotype_Switching_BB(Population& pop1, ENV& env)
{
	//�ҳ���ʼ��Ⱥ����Ѹ���
	vector<double> objofpop1_Somatic;
	for (int i = 0; i < pop1.pop.size(); i++)
	{
		objofpop1_Somatic.push_back(pop1.pop[i].GetSumCompletofBB(pop1.pop[i].jobid, env));
	}
	while (*std::min_element(std::begin(objofpop1_Somatic), std::end(objofpop1_Somatic)) >= pop1.bestbody.obj)
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
				srand(12345);
				int random = rand() % 3 + 1;
				if (random == 1)
				{
					//IgA_BB(pop1.pop[i], env);���������⣬û��Ҫ��IgA
				}
				if (random == 2)
				{
					IgE_BB(pop1.pop[i], env);
				}
				if (random == 3)
				{
					IgG_BB(pop1.pop[i], env);
				}
			}
			objofpop1_Somatic.push_back(pop1.pop[i].GetSumCompletofBB(pop1.pop[i].jobid, env));
		}
	}
	return;
}
void IgE_BB(Antibody& body, ENV& env)
{
	int index = uniform(0, env.n - 1);
	if (uniform(1, 100) < env.G)
	{
		body.jobid[index]++;
	}
	else
	{
		body.jobid[index]--;
	}
}
void IgG_BB(Antibody& body, ENV& env)
{
	int i = rand() % env.n;
	int j = rand() % env.n;
	swap(body.jobid[i], body.jobid[j]);
}

//Ϊ��֤map��������ʹ���Զ����Batch���������¹������ط�<��
//˵������� https://blog.csdn.net/q_l_s/article/details/52575924
bool operator <(const Batch &batch1, const Batch &batch2)
{
	return true;
}
//Ϊֱ��ʹ��map���������ʣ�ֱ�Ӷ���Աȷ����ڹ���map��ͬʱ��ֱ�Ӷ�������releasetime��������
/*
��map��ʽΪ
BATCH1(RELEASETIME=5)
BATCH2(RELEASETIME=6)
BATCH3(RELEASETIME=3)
BATCH4(RELEASETIME=5)
ʹ�öԱȷ����map��ֱ�ӱ��
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
struct CmpByIntRelease {
	bool operator()(const int& k1, const int& k2) const
	{
		return k1 < k2;
	}
};


double Antibody::GetSumCompletofBB(vector<int>& job, ENV& env)
{
	//������μӹ���batch
	//Decoding process
	vector<Batch> AdjustedBeforeBatch;
	vector<Batch> AdjustedBatch;
	for (int i = 0; i <= *std::max_element(std::begin(job), std::end(job)); i++)
	{
		Batch batchtemp;
		for (int j = 0; j < job.size(); j++)
		{
			if (job[j] == i)
			{
				batchtemp.jobid.push_back(j);
				batchtemp.capacity++;
				batchtemp.sumofsecprocess += env.p2[j];
			}
		}
		AdjustedBeforeBatch.push_back(batchtemp);
	}
	//Convert the infeasible solution into feasible solution
	//According to the schedueled order, we split the solution of batch into a sequence of jobs
	vector<int> Sequence_Before_Batch;
	for (int i = 0; i < AdjustedBeforeBatch.size(); i++)
	{
		for (int j = 0; j < AdjustedBeforeBatch[i].jobid.size(); j++)
		{
			Sequence_Before_Batch.push_back(AdjustedBeforeBatch[i].jobid[j]);
		}
	}
	//vector<Batch> FormedBatch;
	while (Sequence_Before_Batch.size() > 0)
	{
		Batch CurrentBatch;//��������һ��
		CurrentBatch.maxsecprocess = 0;
		CurrentBatch.capacity = 0;
		CurrentBatch.sumofsecprocess = 0;
		CurrentBatch.timeofbatchprocess = 0;
		vector<int> record_earse;//��¼unscheduledjobs���������λ��
		for (int i = 0; i < Sequence_Before_Batch.size(); i++)//����ѭ�������е�࣬���������
		{
			if (CurrentBatch.capacity == env.B)
			{
				break;
			}
			if (CurrentBatch.capacity + 1 < env.B&&CurrentBatch.sumofsecprocess + env.p2[Sequence_Before_Batch[i]] <= env.W)//�������Լ��,�ȴ�Լ���Լ����Լ��������Ļ�
			{
				CurrentBatch.jobid.push_back(Sequence_Before_Batch[i]);//�������job����������
				CurrentBatch.sumofsecprocess += env.p2[Sequence_Before_Batch[i]];
				CurrentBatch.maxsecprocess = std::max(env.p2[Sequence_Before_Batch[i]], CurrentBatch.maxsecprocess);
				CurrentBatch.timeofbatchprocess = std::max(env.p1[Sequence_Before_Batch[i]], CurrentBatch.timeofbatchprocess);//PTB
				CurrentBatch.sumofbatchsec = CurrentBatch.sumofsecprocess + CurrentBatch.timeofbatchprocess;
				CurrentBatch.capacity++;
				record_earse.push_back(Sequence_Before_Batch[i]);//��¼jobλ��
			}
		}
		for (int i = 0; i < record_earse.size(); i++)
		{
			Sequence_Before_Batch.erase(Sequence_Before_Batch.begin() + std::distance(std::begin(Sequence_Before_Batch), find(Sequence_Before_Batch.begin(), Sequence_Before_Batch.end(), record_earse[i])));//ȥ��unscheduledjob��������job
		}
		AdjustedBatch.push_back(CurrentBatch);//������õ���ȫ������FormedBatch��
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
	CmpofBatch.push_back(0);//��0�����ʱ��
	int Obj = 0;
	vector<vector<int>> CmpofJob;
	while (1)
	{
		if (SimulatedTime >= std::max(TimeofStep1, CmpofBatch[finishedbatch - 1]) && spaceofbuffer == 0)//when Step 1 is finished and buffer is empty, namely the batch is released
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
				int goin = buffer.getSPTnumsimple(buffer, env);
				buffer.jobid.erase(buffer.jobid.begin() + std::distance(std::begin(buffer.jobid), find(buffer.jobid.begin(), buffer.jobid.end(), goin)));//ȥ��buffer���Ѽӹ���job
																																						 //����ɢ�����ӹ�
				vector<int> tmpcmp;
				tmpcmp.push_back(goin);
				SimulatedTime += env.p2[goin];
				Obj += SimulatedTime;//record the objective function
				tmpcmp.push_back(SimulatedTime);
				CmpofJob.push_back(tmpcmp);//�����
				finishedjob++;//����+1				
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


void InvertSBtoBB(vector<int>& job, ENV& env)
{
	//Encoding process

	//Initialization
	vector<Batch> FormedBatch;

	multimap<int, int, CmpByIntRelease> Sequence_job;//��multimap�����Զ���releasetime���������sequence
	for (int i = 0; i < job.size(); i++)	Sequence_job.insert(make_pair(env.r[job[i]], job[i]));//�õ�Batch���ͷ�ʱ��˳���map���ϣ���һ��sequence���������ͷŵ�

	vector<int> unsheduledjobs;
	for (multimap<int, int>::iterator iter = Sequence_job.begin(); iter != Sequence_job.end(); ++iter)
	{
		unsheduledjobs.push_back((*iter).second);
	}

	/*////////////////////////////////////////////////
	Step 1 Group the jobs into batches
	*////////////////////////////////////////////////
	while (unsheduledjobs.size() > 0)
	{
		Batch CurrentBatch;//��������һ��
		vector<int> record_earse;//��¼unscheduledjobs���������λ��
		for (int i = 0; i < unsheduledjobs.size(); i++)//����ѭ�������е�࣬���������
		{
			if (CurrentBatch.capacity == env.B)
			{
				break;
			}
			if (CurrentBatch.capacity + 1 < env.B&&CurrentBatch.sumofsecprocess + env.p2[unsheduledjobs[i]] <= env.W&&uniform(1, 100)>env.F)//�������Լ��,�ȴ�Լ���Լ����Լ��������Ļ�
			{
				CurrentBatch.jobid.push_back(unsheduledjobs[i]);//�������job����������
				CurrentBatch.sumofsecprocess += env.p2[unsheduledjobs[i]];
				CurrentBatch.capacity++;
				record_earse.push_back(unsheduledjobs[i]);//��¼jobλ��
			}
		}
		for (int i = 0; i < record_earse.size(); i++)
		{
			unsheduledjobs.erase(unsheduledjobs.begin() + std::distance(std::begin(unsheduledjobs), find(unsheduledjobs.begin(), unsheduledjobs.end(), record_earse[i])));//ȥ��unscheduledjob��������job
		}
		if (CurrentBatch.jobid.size() != 0)
		{
			FormedBatch.push_back(CurrentBatch);//������õ���ȫ������FormedBatch��
		}
	}

	/*////////////////////////////////////////////////
	Step 2 Sequence Batches Formed
	*////////////////////////////////////////////////

	//Step2.1 Caculate the release time of batch
	//Step2.2 Sequence the release time

	vector<int> ReleaseTime_T;//����ÿ��job���ͷ�ʱ�伯�ϣ�Ϊ�õ�ÿ���ͷ�ʱ���ṩ֧��
	multimap<Batch, int, CmpByRelease> Sequence;//��multimap�����Զ���releasetime���������sequence
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
		Sequence.insert(make_pair(FormedBatch[i], i));//�õ�Batch���ͷ�ʱ��˳���map���ϣ���һ��sequence���������ͷŵ�
	}
	//������μӹ���batch
	vector<Batch> AdjustedBatch;
	for (multimap<Batch, int>::iterator iter = Sequence.begin(); iter != Sequence.end(); ++iter)
	{
		AdjustedBatch.push_back((*iter).first);
	}
	for (int i = 0; i < AdjustedBatch.size(); i++)
	{
		for (int j = 0; j < AdjustedBatch[i].jobid.size(); j++)
		{
			job[AdjustedBatch[i].jobid[j]] = i;
		}
	}
}