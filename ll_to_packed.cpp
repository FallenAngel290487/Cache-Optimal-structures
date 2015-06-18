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

void initialize_list(node_ll*,node_array*,int);
void veb_initialize(node_veb*,node_array*,int,int,int,int,int);
int binarysearch_veb(node_veb*,int,int);
void insert(node_veb*, node_array*, int);
void packed_arrange(node_veb*,node_array*,int,int);
void percolate_up(node_veb*,node_array*,int,int);
void level_order_veb(node_veb*,int);
void print_packed_array(node_array*,int);
void print_link_list(node_ll*);
void split(node_veb*,int);


int ht,n;										//ht = ht of veb tree = no. of nodes in one node of tree bounds = ht ans 2ht-1
int maxnum=4;
int leaves=8;


node_veb layer1[16];									//veb with max height 20
node_array layer2[8];
node_ll* layer3=NULL;


//For packed array densities
double Tmin=0.5, Tmax=1;									//min and max for maximum densities
double Dmin=0.125, Dmax=0.25;									//min and max for minimum densities
double blocks=log2(leaves);									


//required for vEb initialize
int binary[32];
int ind=1;
int cnt;


/*Initialization of list, array and veb
*/

void initialize_list(node_ll* root,node_array* arr_head, int leaf)
{
	node_ll* head=new node_ll;
	head->arr.clear();
	head->num=0;
	head->next=NULL;
	root = head;
	head->ltop=0;
	arr_head[0].ptol = head;

	node_ll* tmp1=head;
	REPA(i,1,leaf)
	{
		node_ll* tmp2=new node_ll;
		tmp2->arr.clear();
		tmp2->num=0;
		tmp2->next=NULL;
		tmp1->next=tmp2;
		tmp2->ltop=i;
		arr_head[i].ptol = tmp2;
		tmp1=tmp1->next;
	}
}


/*Function to convert binary order to veb to assign children and parent to each node;

  height = height of the current subtree in picture
  curht = height of the current root node from the top of the tree
  maxht = height of the of the biggest possible subtree this node can be root of
*/

void veb_initialize(node_veb* arr_veb,node_array* arr_pkd, int start, int end, int height, int curht, int maxht)
{
	int mid=(start+end)/2;

	if(height == 1)
	{
		binary[mid]=ind++;
		arr_veb[ind-1].val=INT_MAX;
		arr_veb[ind-1].leaf=false;
		arr_veb[ind-1].vtop=-1;
		if(curht==ht)
		{	arr_veb[ind-1].leaf = true;
			arr_veb[ind-1].vtop = cnt++;
			arr_pkd[cnt-1].ptov = ind-1;
		}
	}
	else
	{
		int half=height/2;
		int secondhalf=height-half;

		int count=0;

		int nextht=pow(2,half);
		int mx=pow(2,maxht-half)-1;

		veb_initialize(arr_veb,arr_pkd,start,end,half,curht,maxht);
	
		REP(i,nextht)
		{
			veb_initialize(arr_veb,arr_pkd,start,start+mx-1,secondhalf,curht+half,maxht-half);

			if(count%2)
			{	
				arr_veb[binary[start-1]].r = binary[((2*start)+mx-1)/2];				//right child
				arr_veb[binary[((2*start)+mx-1)/2]].p = binary[start-1];
			}
			else
			{ 
				arr_veb[binary[start+mx]].l = binary[((2*start)+mx-1)/2];			//left child
				arr_veb[binary[((2*start)+mx-1)/2]].p = binary[start+mx];
			}
			count++;
			start=start+mx+1;
		}
	}
}


/* Binary search in VeB to find the node which has the largest value that is smaller than value*/

int binarysearch_veb(node_veb* arr_veb,int key, int value)
{
	if(key!=0)
	{
		if(arr_veb[key].leaf == true)
			return key;
		if(arr_veb[key].leaf == false && (arr_veb[arr_veb[key].l].val >= value || arr_veb[arr_veb[key].l].val == INT_MAX))
			return binarysearch_veb(arr_veb,arr_veb[key].l,value); 
		else if(arr_veb[key].leaf == false && arr_veb[layer1[key].r].val <= value)
			return binarysearch_veb(arr_veb,arr_veb[key].r,value);
		else
		{
			int key1 = binarysearch_veb(arr_veb,arr_veb[key].r,value);
			int key2 = binarysearch_veb(arr_veb,arr_veb[key].l,value);
			if(arr_veb[key1].val <= value || arr_veb[key].val == INT_MAX)
				return key1;
			else
				return key2;
		}
	}
	return -1;
}

/*Functions required for Inserting in the data structure*/

void insert(node_veb* arr_veb, node_array* arr_pkd, int val)
{
	int key = binarysearch_veb(arr_veb,1,val);

	key = arr_veb[key].vtop;

	node_ll* tmp = arr_pkd[key].ptol;
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
			arr_pkd[tmp->ltop].val=tmp->arr.front();
			
			tmp=tmp->next;

		}

		tmp->arr.pb(val); 
		sort(tmp->arr.begin(),tmp->arr.end());
		arr_pkd[tmp->ltop].val=tmp->arr.front();
		tmp->num++;
	}

	packed_arrange(arr_veb,arr_pkd,tmp1->ltop,tmp->ltop);
}


/*Packed array reordering as per densities*/

void packed_arrange(node_veb* arr_veb, node_array* arr_pkd,int index,int endindex)
{
	double D=Tmax, diff=(Tmax-Tmin)/blocks,curD;
	int ele=0, count=1, prev, L_ind1,L_ind2;
	queue< pair< vector<int>, int > >q;
//	q.push(mp(layer2[index].ptol->arr,layer2[index].ptol->num));
//	layer2[index].ptol->arr = vector<int>();

	REPA(i,index,index+2)
	{
		if(arr_pkd[i].ptol->num!=0)
		{
			q.push(mp(arr_pkd[i].ptol->arr, arr_pkd[i].ptol->num));
			arr_pkd[i].ptol->arr=vector<int>();
			arr_pkd[i].ptol->num=0;
		}

		curD=double(((double)(ele+1))/(double)2);

		if(curD<=D)
		{
			if(!q.empty())
			{       ele++;
				arr_pkd[i].ptol->arr= q.front().first;
				arr_pkd[i].ptol->num = q.front().second;
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
			if(arr_pkd[i].ptol->num!=0)
			{
				q.push(mp(arr_pkd[i].ptol->arr, arr_pkd[i].ptol->num));
				arr_pkd[i].ptol->arr=vector<int>();
				arr_pkd[i].ptol->num=0;
			}
			curD=double(((double)(ele+1))/(double)(2*count));

			if(curD<=D)
			{
 				if(!q.empty())
				{	ele++;
					arr_pkd[i].ptol->arr = q.front().first;
					arr_pkd[i].ptol->num = q.front().second;
					q.pop();
				}
			}

		}
		count*=2;
		D-=diff;
	}

	REPA(i,index,max(index+count,endindex))
	{
		if(arr_pkd[i].ptol->num>0)
		{
			arr_veb[layer2[i].ptov].val = arr_pkd[i].val = arr_pkd[i].ptol->arr.front();
		}
		else
			arr_veb[layer2[i].ptov].val = arr_pkd[i].val = INT_MAX;
	}

	percolate_up(arr_veb,arr_pkd,index,index+count);
}


/*Changing VeB as per the new packed array by percolating upwards*/
void percolate_up(node_veb* tmp_v, node_array* tmp_p,int ind1,int ind2)
{
	queue<int>q;

	REPA(i,ind1,ind2)								//level order percolation so as to avoid errors which may occur if lower level is accessed after upper level
		q.push(tmp_p[i].ptov);
	
	int current;
	while(!q.empty())
	{
		current = q.front();
		q.pop();

		if(tmp_v[current].leaf == false)
			tmp_v[current].val = min(tmp_v[tmp_v[current].l].val,tmp_v[tmp_v[current].r].val);
	
		if(tmp_v[current].p>0)
			q.push(tmp_v[current].p);
	}
}
/*Insertion ends*/

/*Traversal of different layers of  the structure*/

void level_order_veb(node_veb* tmp,int key)
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
		printf("%d ",tmp[q.front().first].val);

		if(tmp[q.front().first].leaf == false)
		{
			q.push(mp(layer1[q.front().first].l,curlevel+1));
			q.push(mp(layer1[q.front().first].r,curlevel+1));
		}
		q.pop();
	}	
	printf("\n\n\n\n");
}

void print_packed_array(node_array* tmp,int leaf)
{
	printf("\n\n##############################PACKED ARRAY#######################\n\n");

	REP(i,leaf)
		printf("%d ",tmp[i].val);
	printf("\n\n\n\n");
}

void print_link_list(node_ll* tmp)
{
	printf("\n\n#############################LIST#####################\n\n");

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


void split(node_veb* arr_veb, node_array* arr_pkd, int value)
{
	int key=binarysearch_veb(arr_veb,1,value);
	int pos=-1;

	node_ll* tmp = arr_pkd[arr_veb[key].vtop].ptol;

	REP(i,tmp->num)
	{	if(tmp->arr[i]==value)
		{
			pos=i;
			break;
		}
	}

	if(pos<0)
	{
		printf("The key doesn't exist\n");
		return;
	}

	int tmppos=key;
	stack<int> st;

	while(tmppos!=0)
	{
		st.push(tmppos);
		tmppos=arr_veb[tmppos].p;
	}
	
	int path1[100],path2[100];

        ht=5;
        cnt=0;
        leaves=16;
	ind=1;
				
	vector<int> sm,la;
	REP(i,tmp->num)
	{
		if(tmp->arr[i]>value)
			la.pb(tmp->arr[i]);
		else if(tmp->arr[i]<value)
			sm.pb(tmp->arr[i]);
	}

	node_veb tmp_veb[2*16-1];
	node_array tmp_pkd[16];
	memset(tmp_pkd,INT_MAX,sizeof(tmp_pkd));
	veb_initialize(tmp_veb,tmp_pkd,1,2*16-1,5,1,5);

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

	veb_initialize(layer1,layer2,1,15,4,1,4);


	initialize_list(layer3,layer2,8);
	insert(layer1,layer2,7);
	insert(layer1,layer2,6);
	insert(layer1,layer2,5);
	insert(layer1,layer2,4);
	insert(layer1,layer2,3);
	insert(layer1,layer2,2);
	insert(layer1,layer2,9);
	insert(layer1,layer2,5);
	insert(layer1,layer2,10);
	insert(layer1,layer2,11);
	insert(layer1,layer2,12);
	insert(layer1,layer2,13);
	insert(layer1,layer2,1);

	level_order_veb(layer1,1);

	cout<<endl;
//	REP(i,14)
//		PI(binarysearch_veb(1,i+1));
//		printf("%d ",layer2[i].val);//p,layer1[i+1].l,layer1[i+1].r,layer1[i+1].leaf);

	split(layer1,layer2,13);
//	split(14);
	return 0;
}
