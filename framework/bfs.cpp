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

int visit[5000010];
vector<int> edges[5000010];
vector<int> pattern;
int cur;
int n,no;

void bfs()
{
	while(cur<pattern.size())
	{
		if(visit[pattern[cur]]==0)
		{
			visit[pattern[cur]]=1;
			REP(i,edges[pattern[cur]].size())
				pattern.pb(edges[pattern[cur]][i]);
		}
		cur++;
	}
	
}

int main()
{
	SI(n);

	int x,y;
	cur=0;
	SI(no);
	REP(i,no)
	{
		SII(x,y);

		edges[x].pb(y);
		edges[y].pb(x);
	}

	REP(i,n)
		visit[i]=0;
	REP(i,n)
	{
		if(visit[i]==0)
		{	
			pattern.pb(i);
			bfs();
		}
	}

	REP(i,pattern.size())
		printf("%d ",pattern[i]);

	printf("\n");

	return 0;
}
