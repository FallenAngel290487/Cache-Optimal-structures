#include<bits/stdc++.h>
#define SI(n) scanf("%d",&n)
#define SII(a,b) scanf("%d%d",&a,&b)
#define SIII(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define REPA(i,a,n) for(int i=a;i<n;i++)
#define REP(i,n) for(int i=0;i<n;i++)
#define PI(n) printf("%d\n",n)
#define PII(n,m) printf("%d %d\n",n,m)
#define mp make_pair
#define M 1000000007

using namespace std;

int arr[100010];
int n,ht;

int ans[100010];
int ind;

int child[100010][2];

int power(int base, int exp)
{
	int ans=1;

	while(exp)
	{
		if(exp%2)
			ans=ans*base;
		base=base*base;
		exp/=2;
	}
	return ans;
}


void veb(int start, int end, int height, int maxht)
{
	int mid=(start+end)/2;

	if(height==1)
	{
		ans[mid]=ind++;
	}
	else
	{
		int half=height/2;
		int secondhalf=height-half;
		
		pair<int,int>p;

		int count=0,tmp=ind;
		
		int nextht=power(2,half);
		int mx=power(2,maxht-half)-1;
		
		veb(start,end,half,maxht);
		
		int st=start;
		REP(i,nextht)
		{
			veb(st,st+mx-1,secondhalf,maxht-half);
			
			if(count%2)	
				child[ans[st-1]][1]=ans[((2*st)+mx-1)/2];				//right child
			else
				child[ans[st+mx]][0]=ans[((2*st)+mx-1)/2];				//left child((2*st)+mx-1)/2
			count++;
			st=st+mx+1;
		}
	}
}



int main()
{
	SI(n);

	REPA(i,1,n+1)
		SI(arr[i]);

	ind=1;

	ht=log2(n+1);

	veb(1,n,ht,ht);
	
	REPA(i,1,n+1)
		printf("%d ",ans[i]);
	cout<<endl;
	REPA(i,1,n+1)
		PII(child[i][0],child[i][1]);
	return 0;
}
