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

using namespace std;


int arr[20000010];
int randno[20000010];
int main()
{
	int n,m;
	vector<int> newarr;
	vector<int> flag;
	SII(n,m);
	REP(i,n)
		SI(arr[i]);

	srand(time(NULL));

	for(int t=0;t<m;t++)
	{
		randno[t]= rand()%n;
	}

	sort(randno,randno+m);

	int num2=(9*(n-m))/m;

	int j=0,cur=0;


	REP(i,n)
	{
		cur=0;

		if(i==randno[j])
		{
			j++;
			cur++;
			while(randno[j]==randno[j-1])
			{
				j++;
				cur++;
			}
			REP(i,cur*num2)
			{	newarr.pb(arr[i]);
				flag.pb(1);
			}

		}
		else
		{	newarr.pb(arr[i]);
			flag.pb(0);
		}
	}
	int no,c1=0,c2=0;
	int power=pow(2,20);
	REP(i,power)
	{
		no=(rand()%(10*(n-m)));

		if(flag[no]==1)
			c1++;
		else
			c2++;
	}
	PII(c1,c2);

	return 0;
}
