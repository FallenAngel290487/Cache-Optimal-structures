#include<bits/stdc++.h>
#include<tr1/unordered_set>
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

tr1::unordered_set<int> hash[1010];

void insert(int);
void delete_lst(int);
void insert_hash(int,int);
void delete_hash(int,int);
int find(int);

list<int> lst[1010];
int maxlist=0;


void insert(int val)
{
	int flag=0;
	
	int size,i=0;
	size=pow(2,(pow(2,i)));
	lst[i].push_front(val);
	insert_hash(i,val);

	while(lst[i].size()>size)
	{
		val=lst[i].back();
		lst[i].pop_back();
		delete_hash(i,val);
		
		i++;
		lst[i].push_front(val);
		insert_hash(i,val);
		size=pow(2,(pow(2,i)));
	}
	maxlist=i;
}


void delete_lst(int val)
{
	int lst_ind = find(val);
	
	list<int>::iterator it1=lst[lst_ind].begin();
	
	int offset;

	offset=0;
	for(it1=lst[lst_ind].begin(); it1!=lst[lst_ind].end(); ++it1)
	{
		if((*it1) == val)
			break;
		offset++;
	}

	lst[lst_ind].erase(it1);
	delete_hash(lst_ind,val);
	int i=lst_ind;

	while(i<maxlist)
	{
		val=lst[i+1].front();
		lst[i+1].pop_front();
		delete_hash(i+1,val);

		lst[i].pb(val);
		insert_hash(i,val);
		i++;
	}

	if(lst[maxlist].size() ==0)
		maxlist--;
}

void insert_hash(int index, int val)
{
	hash[index].insert(val);
}

void delete_hash(int index, int val)
{
	hash[index].erase(val);
}

int find(int val)
{
	tr1::unordered_set<int>::const_iterator got;
	REP(i,maxlist+1)
	{
		got = hash[i].find(val);

		if(got != hash[i].end())
			return i;
	}
	return -1;
}

int main()
{
	int n,x;
	SI(n);

	REP(i,n)
	{
		SI(x);
		insert(x);

	
	REP(i,maxlist+1)
	{
		cout<<"THis is table "<<i<<endl;
		for(unsigned j = 0; j < hash[i].bucket_count(); ++j) {
		cout<<"bucket #"<<j<<"contains";
		
		for(auto local_it=hash[i].begin(j) ; local_it!=hash[i].end(j); ++local_it)
			cout<<" "<<*local_it;
			cout<<endl;
		}

		cout<<endl;

	}
	}
	REP(i,maxlist+1)
	{
		for (list<int>::iterator it=lst[i].begin() ; it != lst[i].end(); ++it)
			    cout << ' ' << *it;
		cout<<endl;
	}
	SI(n);
	REP(i,n)
	{
		SI(x);
		delete_lst(x);
/*		REP(i,maxlist+1)
		{
//			PI(i);
			printf("Tree %d inorder: ",i);
			inorder(root[i]);
			cout<<endl;
		}
*/		cout<<endl;
	}
	return 0;
}
