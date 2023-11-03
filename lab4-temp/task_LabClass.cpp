// fibo.cpp : Defines the entry point for the console application. Written by Benjamin Mora for assignment  CS-M98.

#include <thread>
#include <mutex>
#include <iostream>
#include <string>

#include "utils.h"

#define nbThreads 10
#define ringSize (40)
const unsigned long long minimumJobSize = 28; // Minimum fib value for parallelization. Beyond this, Mutex operations are non-negligeable and reduce speed-up. Parallelization will work well for fibs values greater than 28

unsigned long long fibo(unsigned long long n)
{
	if (n <= 1ull)
		return n;
	else
		return fibo(n - 1ull) + fibo(n - 2ull);
}

void fiboRecMultithreaded(unsigned long long *inout)
{
	if (*inout > minimumJobSize)
	{
		unsigned long long res1 = *inout - 1;
		unsigned long long res2 = *inout - 2;
		std::thread t1 = std::thread(fiboRecMultithreaded, &res1);
		fiboRecMultithreaded(&res2);
		t1.join();
		*inout = res1 + res2;
	}
	else
		*inout = fibo(*inout);
}

void ThreadJob(unsigned long long *returnValue, RingBuffer *rb)
{
	*returnValue = 0ull;
	while (!rb->IsRingEmptyAndJobsCompleted())
	{
		unsigned long long job = rb->RemoveFromRing();
		if (job > 0) // A job has been retrieved from pool. There cannot exist such a job (0) in the pool by definition.
		{
			if ((job < minimumJobSize)) // Job is too small. Synchronizing may add too much overhead
				*returnValue += fibo(job);
			else // Job is too large. add more jobs
			{
				if (!rb->AddToRing(job - 1))
					*returnValue += fibo(job - 1);
				if (!rb->AddToRing(job - 2))
					*returnValue += fibo(job - 2);
			}
			rb->NotifyOfJobCompletion();
		}
	}
}

unsigned long long fiboMultithreaded(unsigned long long n)
{
	unsigned long long result = 0ull;
	std::thread *t = new std::thread[nbThreads - 1];
	unsigned long long *returnedResults = new unsigned long long[nbThreads];
	RingBuffer rb(ringSize);

	rb.AddToRing(n);
	for (int i = 0; i < nbThreads; i++)
	{
		if (i < nbThreads - 1)
			t[i] = std::thread(ThreadJob, returnedResults + i, &rb);
		else
		{
			ThreadJob(returnedResults + i, &rb); // last thread should be the current one!
			result = returnedResults[i];
		}
	}
	for (int i = 0; i < nbThreads - 1; i++)
	{
		t[i].join();
		result += returnedResults[i];
	}

	delete[] t;
	delete[] returnedResults;
	return result;
}

int main(int argc, char *argv[])
{
	unsigned long long val;
	const unsigned long long startValue = 46ull;
	unsigned long long startValueRec = startValue;

	printf("Calculating fibo(%llu)...\n", startValue);

	Timer t1;
	val = fibo(startValue);
	printf("Fibo time single-threaded (milliseconds): %.2f", t1.measure());
	printf("Final value  %llu\n", val);

	Timer t2;
	val = startValue;
	fiboRecMultithreaded(&val);
	printf("Fibo time multithreaded (milliseconds): %.2f", t2.measure());
	printf("Final value  %llu\n", val);

	Timer t3;
	val = fiboMultithreaded(startValue);
	printf("Fibo time multithreaded ring buffer (milliseconds): %.2f", t3.measure());
	printf("Final value %llu\n", val);
	return 0;
}
