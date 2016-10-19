//created in 2016-5-21 by wz
//interval tree (for poj 3468) 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define MAX 100100
#define LL long long
#define lson root<<1,l,mid
#define rson root<<1|1,mid+1,r
using namespace std;

int n,q;
LL tree[MAX<<2],add[MAX<<2];

void pushdown(int root,int l){//两个功能：１、将root结点的add加到tree。２、将root结点add下放并清空add
	if(l>1){
		add[root<<1]+=add[root];
		add[root<<1|1]+=add[root];
	}
	tree[root]+=add[root]*l;
	add[root]=0;
}

void pushup(int root,int l){//两个功能：１、将两个子节点的add作用到tree上并下放add。２、将两个子节点的tree赋给root
	pushdown(root<<1,l-l/2);
	pushdown(root<<1|1,l/2);
	tree[root]=tree[root<<1]+tree[root<<1|1];
}

void build(int root,int l,int r){
	if(l==r){
		scanf("%lld",&tree[root]);
		add[root]=0LL;
		return;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	pushup(root,r-l+1);
}

void update(int root,int l,int r,int front,int rear,int v){
	if(l>=front&&r<=rear){
		add[root]+=v;
		//tree[root]+=add[root]*(r-l+1);
		pushdown(root,r-l+1);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(root,r-l+1);
	if(mid>=front)
		update(lson,front,rear,v);
	if(mid+1<=rear)
		update(rson,front,rear,v);
	pushup(root,r-l+1);
}

LL query(int root,int l,int r,int front,int rear){
	if(l>=front&&r<=rear){
		pushdown(root,r-l+1);
		return tree[root];
	}
	int mid=(l+r)>>1;
	pushdown(root,r-l+1);
	LL ret=0LL;
	if(mid>=front)
		ret+=query(lson,front,rear);
	if(mid+1<=rear)
		ret+=query(rson,front,rear);
	return ret;
}

int main(){
	char com;
	int a,b,c;
	while(cin>>n>>q){
		build(1,1,n);
		for(int i=0;i<q;i++){
			getchar();
			scanf("%c %d %d",&com,&a,&b);
			if(com=='C'){
				scanf("%d",&c);
				update(1,1,n,a,b,c);
			}
			else
				printf("%lld\n",query(1,1,n,a,b));
		}
	}
	return 0;
}
