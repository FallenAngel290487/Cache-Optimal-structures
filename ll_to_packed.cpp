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

void initialize_list();
void veb_initialize(int,int,int,int,int);
int binarysearch_veb(int,int);
void insert(int);
void packed_arrange(int,int);
void percolate_up(int,int);
void level_order_veb(int);
void print_packed_array();
void print_link_list();


int ht,n;										//ht = ht of veb tree = no. of nodes in one node of tree bounds = ht ans 2ht-1
int maxheight=20;
int maxnum=4;
int leaves=8;


node_veb layer1[16];									//veb with max height 20
node_array layer2[8];
node_ll* layer3=NULL;

double Tmin=0.5, Tmax=1;									//min and max for maximum densities
double Dmin=0.125, Dmax=0.25;									//min and max for minimum densities
double blocks=log2(1048576);									
int largest_index=-1;


//required for vEb initialize
int binary[16];
int ind=1;
int cnt;


void initialize_list()
{
	node_ll* head=new node_ll;
	head->arr.clear();
	head->num=0;
	head->next=NULL;
	layer3 = head;
	head->ltop=0;
	layer2[0].ptol = head;

	node_ll* tmp1=head;
	REPA(i,1,leaves)
	{
		node_ll* tmp2=new node_ll;
		tmp2->arr.clear();
		tmp2->num=0;
		tmp2->next=NULL;
		tmp1->next=tmp2;
		tmp2->ltop=i;
		layer2[i].ptol = tmp2;
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


/* Binary search in VeB to find the node which has the largest value that is smaller than value*/

int binarysearch_veb(int key, int value)
{
	if(key!=0)
	{
		if(layer1[key].leaf == true)
			return key;
		if(layer1[key].leaf == false && (layer1[layer1[key].l].val >= value || layer1[layer1[key].l].val == INT_MAX))
			return binarysearch_veb(layer1[key].l,value); 
		else if(layer1[key].leaf == false && layer1[layer1[key].r].val <= value)
			return binarysearch_veb(layer1[key].r,value);
		else
		{
			int key1 = binarysearch_veb(layer1[key].r,value);
			int key2 = binarysearch_veb(layer1[key].l,value);
			if(layer1[key1].val <= value || layer1[key].val == INT_MAX)
				return key1;
			else
				return key2;
		}
	}
	return -1;
}

/*Inserting in the data structure*/

void insert(int val)
{
	int key = binarysearch_veb(1,val);

	key = layer1[key].vtop;

	node_ll* tmp = layer2[key].ptol;
	node_ll* tmp1 = tmp;

	if(tmp->num < maxnum)
	{
		tmp->arr.pb(val);
		tmp->num++;
		sort(tmp->arr.begin(),tmp->arr.end());
	}
	else
	{
		while(tmp->num == maxnum)
		{
			tmp->arr.pb(val);
			sort(tmp->arr.begin(),tmp->arr.end());
			val = tmp->arr.back();
			tmp->arr.pop_back();
			layer2[tmp->ltop].val=tmp->arr.front();
			
			tmp=tmp->next;

		}

		tmp->arr.pb(val); 
		sort(tmp->arr.begin(),tmp->arr.end());
		layer2[tmp->ltop].val=tmp->arr.front();
		tmp->num++;
	}

	node_ll* aab = layer3;

	
	packed_arrange(tmp1->ltop,tmp->ltop);

}

void packed_arrange(int index,int endindex)
{
	double D=Tmax, diff=(Tmax-Tmin)/blocks,curD;
	int ele=0, count=1, prev, L_ind1,L_ind2;
	queue< pair< vector<int>, int > >q;
//	q.push(mp(layer2[index].ptol->arr,layer2[index].ptol->num));
//	layer2[index].ptol->arr = vector<int>();

	REPA(i,index,index+2)
	{
		if(layer2[i].ptol->num!=0)
		{
			q.push(mp(layer2[i].ptol->arr, layer2[i].ptol->num));
			layer2[i].ptol->arr=vector<int>();
			layer2[i].ptol->num=0;
		}

		curD=double(((double)(ele+1))/(double)2);

		if(curD<=D)
		{
			if(!q.empty())
			{       ele++;
				layer2[i].ptol->arr= q.front().first;
				layer2[i].ptol->num = q.front().second;
				q.pop();
			}
		}
	}

	D-=diff;

	count*=2;

	//      curD=double(((double)(ele+1))/(double)count);

	while((!q.empty()) || ((index + (count))<=endindex))     // && (index+2*count)<=size)
	{

		REPA(i,index+count,index+2*count)
		{
			if(layer2[i].ptol->num!=0)
			{
				q.push(mp(layer2[i].ptol->arr, layer2[i].ptol->num));
				layer2[i].ptol->arr=vector<int>();
				layer2[i].ptol->num=0;
			}
			curD=double(((double)(ele+1))/(double)(2*count));

			if(curD<=D)
			{
				if(!q.empty())
				{       ele++;
					layer2[i].ptol->arr = q.front().first;
					layer2[i].ptol->num = q.front().second;
					q.pop();
				}
			}

		}
		count*=2;
		D-=diff;
	}

	REPA(i,index,max(index+count,endindex))
	{
		if(layer2[i].ptol->num>0)
		{
			layer1[layer2[i].ptov].val = layer2[i].val = layer2[i].ptol->arr.front();
		}
		else
			layer1[layer2[i].ptov].val = layer2[i].val = INT_MAX;
	}

	percolate_up(index,index+count);
}

void percolate_up(int ind1,int ind2)
{
	queue<int>q;

	REPA(i,ind1,ind2)								//level order percolation so as to avoid errors which may occur if lower level is accessed after upper level
		q.push(layer2[i].ptov);
	
	int current;
	while(!q.empty())
	{
		current = q.front();
		q.pop();

		if(layer1[current].leaf == false)
			layer1[current].val = min(layer1[layer1[current].l].val,layer1[layer1[current].r].val);
	
		if(layer1[current].p>0)
			q.push(layer1[current].p);
	}
}



void level_order_veb(int key)
{
	printf("\n\n############################LEVEL ORDER TRAVERSAL OF LAYER 1 ########################################\n\n");
	queue< pair<int,int> > q;
	
	int curlevel=1;
	q.push(mp(key,1));
	while(!q.empty())
	{
		if(q.front().second > curlevel)
		{
			curlevel++;
			cout<<endl;
		}
		printf("%d ",layer1[q.front().first].val);

		if(layer1[q.front().first].leaf == false)
		{
			q.push(mp(layer1[q.front().first].l,curlevel+1));
			q.push(mp(layer1[q.front().first].r,curlevel+1));
		}
		q.pop();
	}	
	printf("\n\n\n\n");
}

void print_packed_array()
{
	printf("\n\n##############################PACKED ARRAY#######################\n\n");

	REP(i,leaves)
		printf("%d ",layer2[i].val);
	printf("\n\n\n\n");
}

void print_link_list()
{
	printf("\n\n#############################LIST#####################\n\n");

	node_ll* tmp=layer3;
	while(tmp)
	{
		if(tmp->num)
		{	printf("num: %d    ",tmp->num);
			REP(i,tmp->num)
				printf("%d ",tmp->arr[i]);
			printf("\n");
		}
		else
			printf("num: %d \n",tmp->num);
		tmp=tmp->next;
	}
}


int main()
{

	ht=4;
	cnt=0;
	leaves=8;
	REP(i,leaves)
	{
		layer2[i].ptov = -1;
		layer2[i].val = INT_MAX;
		layer2[i].ptol = NULL;
	}

	veb_initialize(1,15,4,1,4);


	initialize_list();
	insert(2);
	insert(3);
	insert(4);
	insert(6);
	insert(7);
	insert(8);
	insert(9);
	insert(5);
	insert(10);
	insert(11);
	insert(12);
	insert(13);

	insert(1);
	level_order_veb(1);

	cout<<endl;
//	REP(i,leaves)
//		printf("%d ",layer2[i].val);//p,layer1[i+1].l,layer1[i+1].r,layer1[i+1].leaf);
	return 0;
}
