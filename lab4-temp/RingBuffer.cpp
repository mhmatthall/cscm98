#include "RingBuffer.h"


RingBuffer::RingBuffer(int size)
{
	ringSize=size;
	ringBuffer=new unsigned long long[size];
	processedJobs=0;
	head=tail=0;
}


RingBuffer::~RingBuffer(void)
{
	delete[] ringBuffer;
}


int RingBuffer::NextPosition(int pos) //returns the position after pos in the ring.
{
	return (pos+1)%ringSize; 
}

bool RingBuffer::IsRingEmpty()
{
	return head==tail; //returns whether the ring is empty
}

bool RingBuffer::IsRingFull() //returns whether the ring is full.
{
	return tail==NextPosition(head);
}

bool RingBuffer::AddToRing(unsigned long long val)
{
	return 0;
}

unsigned long long  RingBuffer::RemoveFromRing() 
{
	return 0;
}

bool RingBuffer::IsRingEmptyAndJobsCompleted()   //Return whether ring is empty and no jobs are being processed. 
{
	return 0;
}

void RingBuffer::NotifyOfJobCompletion() //Reduces the count on the number of jobs being processed
{
}