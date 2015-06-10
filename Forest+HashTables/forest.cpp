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

struct node
{
	int val;
	node* l;
	node* r;
}*root[1010];

void insert(int);
void delete_lst(int);
node* insert_bst(node*,int);
node* delete_bst(node*,int);
int search(int);
void inorder(int);

list<int> lst[1010];
int maxlist=0;


void insert(int val)
{
	int flag=0;
	
	int size,i=0;
	size=pow(2,(pow(2,i)));
	lst[i].push_front(val);
	root[i]=insert_bst(root[i],val);

	while(lst[i].size()>size)
	{
		val=lst[i].back();
		lst[i].pop_back();
		root[i]=delete_bst(root[i],val);
		
		i++;
		lst[i].push_front(val);
		root[i]=insert_bst(root[i],val);
		size=pow(2,(pow(2,i)));
	}
	maxlist=i;
}


void delete_lst(int val)
{
	int lst_ind = search(val);
	
//	PI(lst_ind);
	list<int>::iterator it1=lst[lst_ind].begin();
	
	int offset;

	offset=0;
	for(it1=lst[lst_ind].begin(); it1!=lst[lst_ind].end(); ++it1)
	{
//		cout<<*it1;
		if((*it1) == val)
			break;
		offset++;
	}
//	cout<<"offset:"<<offset<<endl;
//	advance(it1,offset);
		

	lst[lst_ind].erase(it1);
	root[lst_ind]=delete_bst(root[lst_ind],val);
	int i=lst_ind;

	while(i<maxlist)
	{
		val=lst[i+1].front();
		lst[i+1].pop_front();

		root[i+1]=delete_bst(root[i+1],val);
		lst[i].pb(val);
		root[i]=insert_bst(root[i],val);
		i++;
	}

	if(lst[maxlist].size() ==0)
		maxlist--;
}

node* insert_bst(node* head, int val)
{
	node* newNode = new node;

	newNode->val=val;
	newNode->l=NULL;
	newNode->r=NULL;

	if(head == NULL)
	{
		head=newNode;
	}
	else
	{
		node *ptr,*ptr_parent;
		ptr=head;

		while(ptr)
		{
			if(val< ptr->val)
			{
				ptr_parent=ptr;
				ptr=ptr->l;
			}
			else
			{
				ptr_parent=ptr;
				ptr=ptr->r;
			}
		}

		if(val<ptr_parent->val)
			ptr_parent->l=newNode;
		else
			ptr_parent->r=newNode;

	}
	return head;
}

node* delete_bst(node* head, int val)
{
	node *ptr=head,*ptr_parent=NULL;

	while(ptr->val!=val)
	{
		if(val<ptr->val)
		{
			ptr_parent=ptr;
			ptr=ptr->l;
		}
		else
		{
			ptr_parent=ptr;
			ptr=ptr->r;
		}
	}


	if(ptr_parent == NULL)
	{

		if( ptr->l && ptr->r )
		{
			node* cur=ptr;
			cur = cur->r;

			while(cur->l)
				cur = cur->l;

			val=cur->val;
			head = delete_bst(head,cur->val);
			ptr->val=val;

			return head;

		}
		else if(ptr->l)
		{
			head=ptr->l;
			delete ptr;
			return head;
		}
		else
		{
			head=ptr->r;
			delete ptr;
			return head;
		}
		
	}

	else
	{

		if( ptr->l && ptr->r )
		{
			node* cur=ptr;
			cur = cur->r;

			while(cur->l)
				cur = cur->l;

			val=cur->val;
			head=delete_bst(head,cur->val);
			ptr->val=val;
			return head;

		}
		else if(ptr->l)
		{
			if(ptr_parent->l == ptr)
				ptr_parent->l=ptr->l;
			else
				ptr_parent->r=ptr->l;
			delete ptr;
			return head;
		}
		else
		{
			if(ptr_parent->l == ptr)
				ptr_parent->l=ptr->r;
			else
				ptr_parent->r=ptr->r;
			delete ptr;
			return head;
		}
	}
}

int search(int val)
{
	node* head;
	REP(i,maxlist+1)
	{
		head=root[i];
		while(head!=NULL)
		{
			if(val<head->val)
				head=head->l;
			else if(val>head->val)
				head=head->r;
			else
				return i;
		}
	}
	return -1;
}	

void inorder(node* head)
{
	if(head!=NULL)
	{
		printf("%d ",head->val);
		inorder(head->l);
		inorder(head->r);
	}
}

int main()
{
	int n,x;
	SI(n);

	REP(i,n)
	{
		SI(x);
		insert(x);

		/*REP(i,maxlist+1)
		{
//			PI(i);
		}*/
	}

	REP(i,maxlist+1)
	{	
			printf("Tree %d inorder: ",i);
		inorder(root[i]);
		cout<<endl;
	
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
		REP(i,maxlist+1)
		{
//			PI(i);
			printf("Tree %d inorder: ",i);
			inorder(root[i]);
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}
