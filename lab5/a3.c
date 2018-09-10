#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <stdlib.h>
int main(void)
{
	struct timeval TimeValue_Start;
	struct timezone TimeZone_Start;
	struct timeval TimeValue_Final;
	struct timezone TimeZone_Final;

	struct timeval TimeValue_Start_prl;
	struct timezone TimeZone_Start_prl;
	struct timeval TimeValue_Final_prl;
	struct timezone TimeZone_Final_prl;
	long time_start, time_end;
	double time_overhead;

	int a100[500000], a500[500], a1000[1000];
	int i,j;
	for(int i = 0; i<100; i++) 
		a100[i] = rand();
	for(int i = 0; i<500; i++) 
		a500[i] = rand();		 
	for(int i = 0; i<500; i++) 
		a1000[i] = rand();		 

	int min = 1000000;
	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	for(i=0;i<500000;i++)
		if(a100[i] < min)
			min = a100[i];

	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for sequential of 100 elements(T) : %lf\n",time_overhead);
	
	min = 1000000;
	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	for(i=0;i<500;i++)
		if(a500[i] < min)
			min = a500[i];

	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for sequential of 500 elements(T) : %lf\n",time_overhead);


	min = 1000000;
	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	for(i=0;i<1000;i++)
		if(a1000[i] < min)
			min = a1000[i];

	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for sequential of 500 elements(T) : %lf\n",time_overhead);


	int chunk = 10;
	#pragma omp parallel shared(chunk) private(min)

	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	min = 1000000;	
	#pragma omp for schedule(static)	
	for(i=0;i<500000;i++)
		if(a100[i] < min)
			min = a100[i];
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for static_parallel of 500000 elements(T) : %lf\n",time_overhead);


	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	min = 1000000;	
	#pragma omp for schedule(static,chunk)	
	for(i=0;i<500000;i++)
		if(a100[i] < min)
			min = a100[i];
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for static_chunk_parallel of 500000 elements(T) : %lf\n",time_overhead);

	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	min = 1000000;
	#pragma omp for schedule(dynamic,chunk)
	for(i=0;i<500000;i++)
		if(a100[i] < min)
			min = a500[i];
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for dynamic_chunk_parallel of 500000 elements(T) : %lf\n",time_overhead);

	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	min = 1000000;
	#pragma omp for schedule(guided,chunk)
	for(i=0;i<500000;i++)
		if(a1000[i] < min)
			min = a1000[i];
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("Time in Seconds for guided_chunk_parallel of 500000 elements(T) : %lf\n",time_overhead);
	 
	
}