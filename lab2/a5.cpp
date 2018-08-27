#include<stdio.h>
#include<omp.h>

int main()
{
	int i, n, sum = 0, x = 0;
	printf("Enter n : ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array elements : \n");
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for reduction(+:x)
		for(i = 0; i < n; i++)
		{
			sum += a[i];
		}
	}
	printf("Sum = %d\n", sum);
}