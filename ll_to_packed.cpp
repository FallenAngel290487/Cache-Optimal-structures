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


struct node_ll
{
	vector<int>arr;										//For indirection
	int num;
	int loc;
	node_ll* next;
	int ltop;
};


struct node_veb
{
	int p;
	int l;
	int r;
	int val;
	bool leaf;
	int vtop;
};

struct node_array
{
	int val;
	int ptov;
	node_ll* ptol;
};


void veb_initialize(int,int,int,int,int);
void insert(int);

int ht,n,len_ll;										//ht = ht of veb tree = no. of nodes in one node of tree bounds = ht ans 2ht-1
int maxheight=20;

node_veb layer1[1048576];									//veb with max height 20
node_array layer2[1048576];
node_ll* layer3=NULL;

double Tmin=0.5, Tmax=1;
double Dmin=0.125, Dmax=0.25;
double blocks=log2(size);
int largest_index=-1;

//required for vEb initialize
int* binary;
int ind=1,int cnt=0;

void initialize_list()
{
	head=new node_ll;
	head->val= (int*)malloc((2*ht-1)*sizeof(int));
	head->num=0;
	head->loc=0;
	head->next=NULL;

	node* tmp1=head;
	REP(i,len_ll-1)
	{
		node* tmp2=new node_ll;
		tmp2->val= (int*)malloc((2*ht-1)*sizeof(int));
		tmp2->num=0;
		tmp2->next=NULL;
		tmp1->next=tmp2;
		tmp->loc=i+1;
		tmp1=tmp1->next;
	}
}


/*Function to convert binary order to veb to assign children and parent to each node;

  height = height of the current subtree in picture
  curht = height of the current root node from the top of the tree
  maxht = height of the of the biggest possible subtree this node can be root of
*/

void veb_initialize(int start, int end, int height, int curht, int maxht)
{
	int mid=(start+end)/2;

	if(height == 1)
	{
		binary[mid]=ind++;
		layer1[ind-1].val=INT_MAX;
		layer1[ind-1].leaf=false;
		layer1[ind-1].vtop=-1;
		if(curht==ht)
		{	layer1[ind-1].leaf = true;
			layer1[ind-1].vtop = cnt++;
			layer2[cnt-1].ptov = ind-1;
		}
	}
	else
	{
		int half=height/2;
		int secondhalf=height-half;

		int count=0;

		int nextht=pow(2,half);
		int mx=pow(2,maxht-half)-1;

		veb_initialize(start,end,half,curht,maxht);
	
		REP(i,nextht)
		{
			veb_initialize(start,start+mx-1,secondhalf,curht+half,maxht-half);

			if(count%2)
			{	
				layer1[binary[start-1]].r = binary[((2*start)+mx-1)/2];				//right child
				layer1[binary[((2*start)+mx-1)/2]].p = binary[start-1];
			}
			else
			{	
				layer1[binary[start+mx]].l = binary[((2*start)+mx-1)/2];			//left child
				layer1[binary[((2*start)+mx-1)/2]].p = binary[start+mx];
			}
			count++;
			start=start+mx+1;

		}
	}
}


int binarysearch_veb(int key, int value)
{
	if(key!=0)
	{
		if(layer1[key].leaf == true)
			return key;
		if(layer1[key].leaf == false && (layer1[layer1[key].l].val <= value || layer1[layer1[key].l].val == INT_MAX))
			return binarysearch_veb(layer1[key].l,value); 
		else if(layer1[key].leaf == false && layer1[layer1[key].r].val >= value)
			return binarysearch_veb(layer1[key].r,value);
		else
		{
			int key1 = binarysearch_veb(layer1[key].r,value);
			int key2 = binarysearch_veb(layer1[key].l,value);
			if(layer1[key1].val <= value || layer1[key].val == INT_MAX)
				return val1;
			else
				return val2;
		}
	}
	return -1;
}


void insert(int val)
{
	int key = binarysearch_veb(1,val);

	key = layer1[key].vtop;

	node* tmp = layer2[key].ptol;

	if(tmp->num<maxnum)
	{
		temp->arr.push(val);
		temp->num++;
		sort(tmp->arr,tmp->arr+tmp->num);
	}
	else
	{

	}

}

int main()
{

	binary = (int*)malloc(1048576*sizeof(int));
	ht=20;

	REP(i,1048577)
	{
		layer2[i].vtop = -1;
		layer2[i].val = INT_MAX;
		layer2[i].ptol = NULL;
	}
	veb_initialize(1,1048576,20,1,20);


//	REP(i,15)
//		printf("%d %d %d %d\n",layer1[i+1].p,layer1[i+1].l,layer1[i+1].r,layer1[i+1].leaf);
	return 0;
}
