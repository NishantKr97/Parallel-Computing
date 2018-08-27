#include <stdio.h>
#include <omp.h>
int a[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int r1 = 0, r2 = 0, r3 = 0, c1 = 0, c2 = 0, c3 = 0;
int i,j;
void rowSum()
{
	#pragma omp task 
	{
		for(i=0;i<3;i++)
		{
			r1 += a[0][i];
		}
	}
	
	#pragma omp task 
	{
		for(i=0;i<3;i++)
		{
			r2 += a[1][i];
		}
	}
			
	#pragma omp task
	{
		for(i=0;i<3;i++)
		{
			r3 += a[2][i];
		}
	}
}

void colSum()
{
	#pragma omp task 
	{
		for(i=0;i<3;i++)
		{
			c1 += a[i][0];
		}
	}

	#pragma omp task 
	{
		for(i=0;i<3;i++)
		{
			c2 += a[i][1];
		}
	}
	
	#pragma omp task 	
	{
		for(i=0;i<3;i++)
		{
			c3 += a[i][2];
		}
	}
}

int main()
{
	

	#pragma omp parallel num_threads(6)
	{
		#pragma omp single
		{
			rowSum();
			colSum();
			printf("row1 = %d\nrow2 = %d\nrow3 = %d\ncol1 = %d\ncol2 = %d\ncol3 = %d\n",r1, r2, r3, c1, c2, c3);			
		}
		
	}

}