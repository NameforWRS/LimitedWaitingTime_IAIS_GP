#include"GBLWT.h"

//bool operator <(const Batch &batch1, const Batch &batch2)
//{
//	return true;
//}
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
struct CmpByIncr{
	bool operator()(const int k1, const int k2) const
	{
		return k1 < k2;
	}
};

struct CmpByPj {
	bool operator()(const Batch k1, const Batch k2) const
	{
		return k1.sumofsecprocess > k2.sumofsecprocess;
	}
};
struct CmpByPjtj {
	bool operator()(const Batch k1, const Batch k2) const
	{
		return k1.sumofbatchsec > k2.sumofbatchsec;
	}
};

double GBLWT(int n, vector<int> p1, vector<int> p2, vector<int> s1, vector<int> r, int W, int B)
{
	ENV env;
	env.p2 = p2;
	//Step 1.1 Sort the job
	multimap<int, int, CmpByIncr> Sequence_Job;//��multimap�����Զ���p1���������sequence_Job

	for (int i = 0; i < p1.size(); i++)
	{
		Sequence_Job.insert(make_pair(p1[i], i));//
	}
	vector<int> job;
	for (multimap<int, int>::iterator iter = Sequence_Job.begin(); iter != Sequence_Job.end(); ++iter)
	{
		job.push_back((*iter).second);
	}
	//Initialization
	vector<Batch> FormedBatch;
	vector<int> unsheduledjobs;
	unsheduledjobs = job;

	/*////////////////////////////////////////////////
	Step 1 Group the jobs into batches
	*////////////////////////////////////////////////
	while (unsheduledjobs.size() > 0)
	{
		Batch CurrentBatch;//��������һ��
		CurrentBatch.maxsecprocess = 0;
		CurrentBatch.capacity = 0;
		CurrentBatch.sumofsecprocess = 0;
		CurrentBatch.timeofbatchprocess = 0;
		vector<int> record_earse;//��¼unscheduledjobs���������λ��
		for (int i = 0; i < unsheduledjobs.size(); i++)//����ѭ�������е�࣬���������
		{
			if (CurrentBatch.capacity == B)
			{
				break;
			}
			if (CurrentBatch.capacity + 1 < B&&CurrentBatch.sumofsecprocess+ p2[unsheduledjobs[i]] - std::max(p2[unsheduledjobs[i]],CurrentBatch.maxsecprocess) <= W)//�������Լ���͵ȴ�Լ��������Ļ�
			{
				CurrentBatch.jobid.push_back(unsheduledjobs[i]);//�������job����������
				CurrentBatch.sumofsecprocess += p2[unsheduledjobs[i]];
				CurrentBatch.maxsecprocess = std::max(p2[unsheduledjobs[i]], CurrentBatch.maxsecprocess);
				CurrentBatch.timeofbatchprocess = std::max(p1[unsheduledjobs[i]], CurrentBatch.timeofbatchprocess);
				CurrentBatch.sumofbatchsec = CurrentBatch.sumofsecprocess + CurrentBatch.timeofbatchprocess;
				CurrentBatch.capacity++;
				record_earse.push_back(unsheduledjobs[i]);//��¼jobλ��
			}
		}
		for (int i = 0; i < record_earse.size(); i++)
		{
			unsheduledjobs.erase(unsheduledjobs.begin() + std::distance(std::begin(unsheduledjobs), find(unsheduledjobs.begin(), unsheduledjobs.end(), record_earse[i])));//ȥ��unscheduledjob��������job
		}
		FormedBatch.push_back(CurrentBatch);//������õ���ȫ������FormedBatch��
	}

	/*////////////////////////////////////////////////
	Step 2 Sequence Batches Formed
	*////////////////////////////////////////////////

	//Step2.1 Caculate the release time of batch
	//Step2.2 Sequence the release time

	vector<int> ReleaseTime_T;//����ÿ��job���ͷ�ʱ�伯�ϣ�Ϊ�õ�ÿ���ͷ�ʱ���ṩ֧��
	multimap<Batch, int, CmpByPj> Sequence_Batch1;//��multimap�����Զ���releasetime���������sequence
	for (int i = 0; i < FormedBatch.size(); i++)
	{
		Sequence_Batch1.insert(make_pair(FormedBatch[i], i));//�õ�Batch���ͷ�ʱ��˳���map���ϣ���һ��sequence���������ͷŵ�
	}
	//������μӹ���batch
	vector<Batch> AdjustedBatch1;
	for (multimap<Batch, int>::iterator iter = Sequence_Batch1.begin(); iter != Sequence_Batch1.end(); ++iter)
	{
		AdjustedBatch1.push_back((*iter).first);
	}
	/*////////////////////////////////////////////////
	Step 3 Calculate the sum of job completion time
	*////////////////////////////////////////////////
	int SimulatedTime = 0;//initial time is 0
	int finishedjob = 0;//the finished job number
	int finishedbatch = 1;//the finished batch number
	int currentbatch = 0;// the current batch number
	int TimeofStep1 = AdjustedBatch1[0].timeofbatchprocess;
	int spaceofbuffer = 0;
	Buffer buffer1;//the current jobs in the buffer
	vector<int> CmpofBatch1;
	CmpofBatch1.push_back(0);//��0�����ʱ��
	int Obj1 = 0;
	vector<vector<int>> CmpofJob1;
	while (1)
	{
		if (SimulatedTime >= std::max(TimeofStep1, CmpofBatch1[finishedbatch - 1]) && spaceofbuffer == 0)//when Step 1 is finished and buffer is empty, namely the batch is released
		{
			for (int i = 0; i < AdjustedBatch1[currentbatch].jobid.size(); i++)
			{
				buffer1.jobid.push_back(AdjustedBatch1[currentbatch].jobid[i]);
			}
			spaceofbuffer = buffer1.jobid.size();//the job in the batch is released
			currentbatch += 1;//we put the next batch into batch processor
			if (currentbatch < AdjustedBatch1.size())
			{
				TimeofStep1 = SimulatedTime + AdjustedBatch1[currentbatch].timeofbatchprocess;//boom! The batch is finished
			}
		}
		if (spaceofbuffer>0 && finishedjob <= n)//when the Step 2 is available and buffer has jobs and the process is continued
		{
			while (buffer1.jobid.size() > 0)
			{
				int goin = buffer1.getSPTnum(buffer1, env);
				buffer1.jobid.erase(buffer1.jobid.begin() + std::distance(std::begin(buffer1.jobid), find(buffer1.jobid.begin(), buffer1.jobid.end(), goin)));//ȥ��buffer���Ѽӹ���job																															 //����ɢ�����ӹ�
				vector<int> tmpcmp;
				tmpcmp.push_back(goin);
				SimulatedTime += p2[goin];
				Obj1 += SimulatedTime;//record the objective function
				tmpcmp.push_back(SimulatedTime);
				CmpofJob1.push_back(tmpcmp);//�����
				finishedjob++;//����+1				
			}
			spaceofbuffer = buffer1.jobid.size();//buffer is empty
			CmpofBatch1.push_back(SimulatedTime);
			finishedbatch++;
		}
		SimulatedTime++;
		if (finishedjob == n)
		{
			break;
		}
	}
	int OBJ1= Obj1;
	////////////////////////////////////////////
	///NEW STAGE!!!!!WARNIINGS!!!!
	///////////////////////////////////////////
	
	multimap<Batch, int, CmpByPjtj> Sequence_Batch2;//��multimap�����Զ���releasetime���������sequence
	for (int i = 0; i < FormedBatch.size(); i++)
	{
		Sequence_Batch2.insert(make_pair(FormedBatch[i], i));//�õ�Batch���ͷ�ʱ��˳���map���ϣ���һ��sequence���������ͷŵ�
	}
	//������μӹ���batch
	vector<Batch> AdjustedBatch2;
	for (multimap<Batch, int>::iterator iter = Sequence_Batch2.begin(); iter != Sequence_Batch2.end(); ++iter)
	{
		AdjustedBatch2.push_back((*iter).first);
	}
	/*////////////////////////////////////////////////
	Step 3 Calculate the sum of job completion time
	*////////////////////////////////////////////////
	SimulatedTime = 0;//initial time is 0
	finishedjob = 0;//the finished job number
	finishedbatch = 1;//the finished batch number
	currentbatch = 0;// the current batch number
	TimeofStep1 = AdjustedBatch2[0].timeofbatchprocess;
	spaceofbuffer = 0;
	Buffer buffer2;//the current jobs in the buffer
	vector<int> CmpofBatch2;
	CmpofBatch2.push_back(0);//��0�����ʱ��
	int Obj2 = 0;
	vector<vector<int>> CmpofJob2;
	while (1)
	{
		if (SimulatedTime >= std::max(TimeofStep1, CmpofBatch2[finishedbatch - 1]) && spaceofbuffer == 0)//when Step 1 is finished and buffer is empty, namely the batch is released
		{
			for (int i = 0; i < AdjustedBatch2[currentbatch].jobid.size(); i++)
			{
				buffer2.jobid.push_back(AdjustedBatch2[currentbatch].jobid[i]);
			}
			spaceofbuffer = buffer2.jobid.size();//the job in the batch is released
			currentbatch += 1;//we put the next batch into batch processor
			if (currentbatch < AdjustedBatch2.size())
			{
				TimeofStep1 = SimulatedTime + AdjustedBatch2[currentbatch].timeofbatchprocess;//boom! The batch is finished
			}
		}
		if (spaceofbuffer>0 && finishedjob <= n)//when the Step 2 is available and buffer has jobs and the process is continued
		{
			while (buffer2.jobid.size() > 0)
			{
				int goin = buffer2.getSPTnum(buffer2, env);
				buffer2.jobid.erase(buffer2.jobid.begin() + std::distance(std::begin(buffer2.jobid), find(buffer2.jobid.begin(), buffer2.jobid.end(), goin)));//ȥ��buffer���Ѽӹ���job
																																						 //����ɢ�����ӹ�
				vector<int> tmpcmp;
				tmpcmp.push_back(goin);
				SimulatedTime += p2[goin];
				Obj2 += SimulatedTime;//record the objective function
				tmpcmp.push_back(SimulatedTime);
				CmpofJob2.push_back(tmpcmp);//�����
				finishedjob++;//����+1				
			}
			spaceofbuffer = buffer2.jobid.size();//buffer is empty
			CmpofBatch2.push_back(SimulatedTime);
			finishedbatch++;
		}
		SimulatedTime++;
		if (finishedjob == n)
		{
			break;
		}
	}
	int OBJ2 = Obj2;
	return std::max(OBJ1, OBJ2);
}