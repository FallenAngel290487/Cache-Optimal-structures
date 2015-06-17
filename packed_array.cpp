#include<bits/stdc++.h>
#define SI(n) scanf("%d",&n)
#define SII(a,b) scanf("%d%d",&a,&b)
#define SIII(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define SLL(n) scanf("%lld",&n)
#define SC(r) scanf("%c",&r)
#define SS(r) scanf("%s",r)
#define SD(r) scanf("%lf",&r)
#define REPA(i,a,n) for(int i=a;i<n;i++)
#define REP(i,n) for(int i=0;i<n;i++)
#define PI(n) printf("%d\n",n)
#define PII(a,b) printf("%d %d\n",a,b)
#define PLL(n) printf("%lld\n",n)
#define PC(n) printf("%c\n",n)
#define PS(n) printf("%s\n",n)
#define PD(n) printf("%lf\n",n)
#define ll long long
#define pb push_back
#define mp make_pair
#define M 1000000007
#define size 16

using namespace std;

int arr[size];
double Tmin=0.5, Tmax=1;
double Dmin=0.125, Dmax=0.25;
double blocks=log2(size);
int largest_index=-1;

void insert(int);
void insert_move(int,int);
void rearrange(queue<int> q);
void delete_packedarray(int);
void delete_move(int);

void insert(int val)
{
	int prev=-1,prev_index=-1;

	if(largest_index==-1)
	{	arr[0]=val;
		largest_index=0;
	}
	else
	{
		REP(i,size)
		{
			if(prev<val && arr[i]>val)
			{
				insert_move(prev_index+1,val);
				return;
			}
			else if(arr[i]!=-1)
			{
				prev=arr[i];
				prev_index=i;
			}
		}
		insert_move(prev_index+1,val);
	}
}

void insert_move(int index, int val)
{
	double D=Tmax, diff=(Tmax-Tmin)/blocks,curD;
	int ele=0, count=1, prev, L_ind1,L_ind2;
	queue<int> q;
	q.push(val);
	
	REPA(i,index,index+2)
	{
		if(arr[i]!=-1)
		{	q.push(arr[i]);
			arr[i]=-1;
		}
		
		curD=double(((double)(ele+1))/(double)2);
		
		if(curD<=D)
		{
			if(!q.empty())
			{	ele++;
				arr[i]=q.front();
				q.pop();
			}
		}
		//PD(curD);
	}
	D-=diff;
	
	count*=2;

//	curD=double(((double)(ele+1))/(double)count);
	
	while((!q.empty()))	// && (index+2*count)<=size)
	{

		if(index+2*count>size)
		{	rearrange(q);
		}
		else
		{
			REPA(i,index+count,index+2*count)
			{
				if(arr[i]!=-1)
				{	q.push(arr[i]);
			//	arr[i]=-1;
				}
				curD=double(((double)(ele+1))/(double)(2*count));
			
				if(curD<=D)
				{
					if(!q.empty())
					{	ele++;
						arr[i]=q.front();
						q.pop();
					}
				}
			
			}
			count*=2;
			D-=diff;
		}
	}
}

void rearrange(queue<int> q)
{
	queue<int> q1;

	REP(i,size)
	{
		if(arr[i]!=-1)
		{	
			q1.push(arr[i]);
			arr[i]=-1;
		}
	}

	while(!q.empty())
	{
		q1.push(q.front());
		q.pop();
	}
	double D=Tmax, diff=(Tmax-Tmin)/blocks,curD;
	int ele=0, count=1, prev, L_ind1,L_ind2,index=0;
	
	REPA(i,index,index+2)
	{
		curD=double(((double)(ele+1))/(double)2);
		
		if(curD<=D)
		{
			if(!q1.empty())
			{	ele++;
				arr[i]=q1.front();
				q1.pop();
			}
		}
		//PD(curD);
	}
	D-=diff;
	
	count*=2;

//	curD=double(((double)(ele+1))/(double)count);
	
	while((!q1.empty()))	// && (index+2*count)<=size)
	{
		REPA(i,index+count,index+2*count)
		{
			curD=double(((double)(ele+1))/(double)(2*count));

			if(curD<=D)
			{
				if(!q1.empty())
				{	ele++;
					arr[i]=q1.front();
					q1.pop();
				}
			}

		}
		count*=2;
		D-=diff;

	}

}

void delete_packedarray(int val)
{
	REP(i,size)
	{
		if(arr[i]==val)
		{
			delete_move(i);
		}
	}
}

void delete_move(int index)
{
	arr[index]=-1;
	
	int count=1,ind,ele=0;
	double curD,D=Dmin,diff=(Dmax-Dmin)/blocks;

	queue<int> q;

	REPA(i,index,size)
	{
		if(arr[i]!=-1)
		{	ind=i;
			break;
		}
		else if(index==size-1)
		{	return;
		}
	
	}
	
	while(curD<D)
	{
		count*=2;
		for(int i=ind+1;i<=ind+count;i++)
		{
			if(arr[i]!=-1)
			{
				q.push(arr[i]);
				arr[i]=-1;
				ele++;
			}
		}
		curD=double(((double)(ele))/(double)(count));
		D+=diff;
		
	}

	int i=ind;

	curD=(float)0;
	D=Tmax;
	ele=0;
	count=1;
	while(!q.empty())
	{
		REPA(i,ind+count,ind+2*count)
		{
			curD=double(((double)(ele+1))/(double)(2*count));

			if(curD<D)
			{
				if(!q.empty())
				{	ele++;
					arr[i]=q.front();
					q.pop();
				}
			}

		}
		count*=2;
	}


}

int main()
{

	int n,x;

	SI(n);

	REP(i,size)
		arr[i]=-1;

	REP(i,n)
	{
		SI(x);
		insert(x);
	


		REP(i,15)
		{
			if(arr[i]>0)
				printf("%d ",arr[i]);
			else
				printf("0 ");
		}   
		printf("\n");
	}

	return 0;
}
