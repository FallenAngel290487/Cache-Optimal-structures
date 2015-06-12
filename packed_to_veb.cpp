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

class BTreeNode
{
	public:
	int *keys;
	int t;
	BTreeNode** C;
	int n;
	bool leaf;
		
	BTreeNode(int _t,bool _leaf);
	void insertNonFull(int k);
	void splitChild(int i, BTreeNode *y);

	void traverse();

	BTreeNode* search(int k);

	int findKey(int k);

	void remove(int k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	int getPred(int idx);
	int getSucc(int idx);
	void fill(int idx);
	void borrowFromPrev(int idx);
	void borrowFromNext(int idx);
	void merge(int idx);

	friend class BTree;

};

class BTree
{
	public:
	BTreeNode* root;
	int t;
	BTree(int _t)
	{
		root=NULL;
		t=_t;
	}

	void traverse()
	{
		if(root)
			root->traverse();
	}

	BTreeNode* search(int k)
	{
		if(root == NULL)
			return NULL;
		else
			return root->search(k);
	}

	void insert(int k);
	void remove(int k);
};

BTreeNode::BTreeNode(int _t, bool _leaf)
{
	t=_t;
	leaf=_leaf;

	keys=new int[2*t-1];
	C=new BTreeNode *[2*t];
	n=0;
}

void BTreeNode::traverse()
{
	int i;

	for(i=0;i<n;i++)
	{
		if(leaf == false)
			C[i]->traverse();
		cout<<" "<<keys[i];
	}

	if(leaf == false)
		C[i]->traverse();
}

BTreeNode* BTreeNode::search(int k)
{
	int i=0;

	while(i<n && k>keys[i])
		i++;

	if(keys[i]==k)
		return this;

	if(leaf == true)
		return NULL;

	return C[i]->search(k);
}

void BTree::insert(int k)
{
	if(root == NULL)
	{
		root= new BTreeNode(t,true);
		root->keys[0]=k;
		root->n=1;
	
	else
	{
		if(root->n == 2*t-1)
		{
			BTreeNode *s = new BTreeNode(t,false);

			s->C[0]=root;

			int i=0;

			if(s->keys[0] < k)
				i++;

			s->C[i]->insertNonFull(k);

			root = s;
		}
		else
			root->insertNonFull(k);
	}
}

void BTreeNode::insertNonFull(int k)
{
	int i = n-1;

	if(leaf == true)
	{
		while(i>=0 && keys[i] >k)
		{
			keys[i+1] = keys[i];
			i--;
		}

		keys[i+1]=k;
		n++;
	}
	else
	{
		while(i>=0 && keys[i]>k)
			i--;

		if(C[i+1]->n == 2*t-1)
		{
			splitChild(i+1, C[i+1]);

			if(keys[i+1] < k)
				i++;
		}

		C[i+1]->insertNonFull(k);
	}
}

void BTreeNode::splitChild(int i, BTreeNode* y)
{
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t-1;

	for(int j=0;j<t-1;j++)
		z->keys[j]=y->keys[j+t];

	if(y->leaf == false)
	{
		for(int j=0;j<t;j++)
			z->C[j]=y->C[j+t];
	}

	y->n = t-1;

	for(int j=n;j>=i+1;j--)
		C[j+1] = C[j];

	C[i+1]=z;

	for(int j=n-1;j>=i;j--)
		keys[j+1]=keys[j];

	keys[i]=y->keys[t-1];

	n++;
}

int BTreeNode::findKey(int k)
{
	int idx=0;
	while(idx<n && keys[idx] == k)
		idx++;
	return idx;
}

void BTreeNode::remove(int k)
{
	int idx = findKey(k);

	if(idx<n && keys[idx] ==k)
	{
		if(leaf)
			removeFromLeaf(idx);
		else
			removeFromNonLeaf(idx);
	}
	else
	{
		if(leaf)
		{
			cout<<"The key "<<k<<" does not exist in the tree";
			return;
		}
		
		bool flag = ((idx==n)?true:false);

		if( C[idx]->n < t)
			fill(idx);

		if(flag && idx > n)
			C[idx-1]->remove(k);
		else
			C[idx]->remove(k);
	}
	return;
}

void BTreeNode::removeFromLeaf(int idx)
{
	for(int i=idx+1;i<n;i++)
		keys[i-1]=keys[i];
	n--;
	return;
}

void BTreeNode::removeFromNonLeaf(int idx)
{
	int k = keys[idx];

	if(C[idx]->n >= t)
	{
		int pred = getPred(idx);
		keys[idx] = pred;
		C[idx]->remove(pred);
	}
	else if(C[idx+1]->n >=t)
	{
		int succ = getSucc(idx);
		keys[idx] = succ;
		C[idx+1]->remove(succ);
	}
	else
	{
		merge(idx);
		c[idx]->remove(k);
	}
	return;
}

int BTreeNode::getPred(int idx)
{
	BTreeNode *cur=C[idx];

	while(!cur->leaf)
		cur=cur->C[cur->n];

	return cur->keys[cur->n-1];
}

int BTreeNode::getSucc(int idx)
{
	BTreeNode *cur = C[idx+1];

	while(!cur->leaf)
		cur=cur->C[0];

	return cur->keys[0];
}

void BTreeNode::fill(int idx)
{
	if(idx!=0 && C[idx-1]->n>=t)
		borrowFromPrev(idx);
	else if(idx!=n &&& C[idx+1]->n >=t)
		borrowFromNext(idx);

	else
	{
		if(idx!=n)
			merge(idx);
		else
			merge(idx-1);
	}
	return;
}


void BTreeNode::borrowFromPrev(int idx)
{
	BTreeNode *child=C[idx];
	BTreeNode *sibling=C[idx-1];

	for(int i=child->n-1;i>=0;i--)
		child->keys[i+1]=child->keys[i];

	if(!child->leaf)
	{
		for(int i=child->n;i>=0;i--)
			child->C[i+1]=child->C[i];
	}
	child->keys[0] = keys[idx-1];

	if(!leaf)
		child->C[0] = sibling->C[sibling->n];

	keys[idx-1] = sibling->keys[sibling->n-1];

	child->n +=1;
	sibling->n-=1;
	return;
}

void BTreeNode::borrowFromNext(int idx)
{
	BTreeNode *child = C[idx];
	BTreeNode *sibling = C[idx+1];

	child->keys[(child->n)] = keys[idx];

	if(!(child->leaf))
	{
		child->C[(child->n)+1] = sibling->C[0];
	}

	keys->idx = sibling->keys[0];

	for(int i=1;i<sibling->n;i++)
		sibling->keys[i-1] = sibling->keys[i];

	if(!sibling->leaf)
	{
		for(int i=1;i<=sibling->n;i++)
			sibling->C[i-1]=sibling->C[i];
	}

	child->n += 1;
	sibling->n -= 1;
	return;
}

void BTreeNode::merge(int idx)
{

}

int main()
{
	return 0;
}