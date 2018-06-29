#include"GlobalHead.h"
#include"Notation.h"

void tmain()
{
	vector<int> vecTest;
	vecTest.push_back(5);
	vecTest.push_back(6);
	vecTest.push_back(3);
	vecTest.push_back(5);
	vector<Batch> FormedBatch;
	for (int i = 0; i < vecTest.size(); i++)
	{
		Batch curr;
		curr.jobid.push_back(2*i);
		curr.jobid.push_back(max(2*i,2 * i + 1));
		FormedBatch.push_back(curr);
	}
	multimap<Batch, int, CmpByRelease> Sequence;

	for (int i = 0; i < vecTest.size(); i++)
	{
		//std::vector<int>::iterator smallest = std::min_element(std::begin(vecTest), std::end(vecTest));
		FormedBatch[i].releasetime = vecTest[i];
		Sequence.insert(make_pair(FormedBatch[i],i));
		//Sequence[FormedBatch[i]] = i;
	}
}