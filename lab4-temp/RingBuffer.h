#pragma once
#include <mutex>

class RingBuffer
{
private:
	int ringSize;
	int head,tail;
	unsigned long long *ringBuffer;
	int processedJobs;
	std::recursive_mutex ringLock;
private:
	int NextPosition(int pos);
	bool IsRingFull();
	bool IsRingEmpty();
public:
	RingBuffer(int size);
	~RingBuffer(void);
	unsigned long long RemoveFromRing(); 
	bool AddToRing(unsigned long long val);
	bool IsRingEmptyAndJobsCompleted();  //Return whether ring is empty and no jobs are being processed
	void NotifyOfJobCompletion(); //Reduces the count on the number of jobs being processed
};

