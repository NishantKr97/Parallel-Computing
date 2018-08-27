#include<stdio.h>
#include<omp.h>
int main()
{
	int x=0, i, n;
	printf("Enter n : ");
	scanf("%d", &n);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		#pragma omp for lastprivate(i)
		for(i=0;i<n;i++)
		{
			printf("Thread %d: Value of i: %d\n",id, i);
			x = x + i;
			printf("Thread %d: x is %d\n", id,x);
		}
	}

	printf("x is %d\n", x);
	printf("i is %d\n", i);

	return 1;
}