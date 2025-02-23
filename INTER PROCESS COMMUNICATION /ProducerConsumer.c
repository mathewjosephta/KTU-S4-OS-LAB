#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

#define max 3

int i=0,j=0,a[max],s=0,k;

void producer();
void consumer();

void main()
{
	int c;
	char y[10];
	while(1)
	{
		printf("\nMENULIST\n\n");
		printf("1.Producer\n");
		printf("2.Consumer\n");
		printf("3.Exit\n\n");
		printf("Enter The Choice\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:producer();
				break;
			case 2:consumer();
				break;
			case 3:exit(1);
		}
	}
}
void producer()
{
	if(s==max)
	{
		printf("\nBuffer Is Full\n");
		sleep(1);
	}


	else
	{
		printf("Enter The Element To Be Produced\n");
		scanf("%d",&a[i]);
		printf("\n%d Is Produced\n",a[i]);
		i=(i+1)%max;
		s++;
	}
}	
void consumer()
{
	if(s==0)
	{
		printf("\nBuffer Is Empty\n");
		sleep(1);
	}
	else
	{
		printf("\n%d Is Consumed\n",a[j]);
		j=(j+1)%max;
		s--;
	}
}	
