#include<bits/stdc++.h>

using namespace std;

int main()
{
	srand(time(NULL));
	int randno;
	int power=pow(2,20);
	printf("%d 1000 ",power);
	for (int t=0;t<power;t++)
	{
		randno= rand()%1000000000;
		printf("%d ",randno);
	}
/*
	for(int i=0;i<127;i++)
	{
		printf("%d ",randno[i]);
	}
	printf("\n");*/
	return 0;
}
