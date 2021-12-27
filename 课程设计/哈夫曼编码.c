#include<stdio.h>
#include<stdlib.h>
#define N 100
struct node   //用于表示赫夫曼树的节点
{
	int num;//表示叶子节点的序号
	int v;//表示权值（频率）
	struct node*parent;//指向父亲节点
	int type;//1表示左儿子，2表示右儿子
	struct node*next;//用于该节点未成为赫夫曼树节点时的连接
};
struct node1   //用于表示起初的节点
{
	int number;//表示该节点在原来顺序中的位置
	int f;//表示该节点的频率
}p[N];
struct node2   //用于存放答案
{
	int code[N];
	int len;
}Ans[N];
int n;//表示单词数
struct node *start;//所有未成为赫夫曼树节点的头指针
struct node *head[N];//存放所有初始节点的地址
int cmp(const void *a,const void *b)//快排函数
{
	if ((*(struct node1*)a).f<(*(struct node1*)b).f)
		return -1;
	return 1;
}
void build()//建立包含所有初始节点的频率递增的链表
{
	int i;
	struct node *k;
	start=(struct node*)malloc(sizeof(struct node));
	start->num=p[0].number;
	start->v=p[0].f;
	start->parent=NULL;
	for(i=1,k=start;i<n;i++,k=k->next)
	{
		k->next=(struct node*)malloc(sizeof(struct node));
	    k->next->num=p[i].number;
	    k->next->v=p[i].f;
		k->next->parent=NULL;
	}
	k->next=NULL;
}
void get_head()//得到所有初始节点的地址
{
	int i;
	struct node*k;
	for(i=0,k=start;i<n;i++,k=k->next)
		head[k->num]=k;
}
void Insert(struct node*now)//把形成的新的节点插入链表，并维护链表的单调性
{
	struct node*k;
	if(start==NULL)
		return;
	if(now->v<start->v)
	{
		now->next=start;
		start=now;
		return ;
	}
	for(k=start;k->next!=NULL;k=k->next)
	{
		if(k->next->v>now->v)
		{
			now->next=k->next;
			k->next=now;
			return;
		}
	}
	if(k->v<=now->v)
	{
		k->next=now;
		now->next=NULL;
	}
}
void get_ans(struct node*k,int i)//获取所有初始节点的赫夫曼编码
{
	if(k==NULL)
		return ;
	if(k->type==1)
	{
		Ans[i].code[Ans[i].len]=0;
		Ans[i].len++;
		get_ans(k->parent,i);
	}
	else if(k->type==2)
	{
		Ans[i].code[Ans[i].len]=1;
		Ans[i].len++;
		get_ans(k->parent,i);
	}
}

int main()
{
	int i,j,sum;
	double aver;
	char data[N][N];//储存单词
	struct node *now;
	printf("输入单词数量。\n");
	scanf("%d",&n);
	getchar();
	printf("输入单词和频率，以空格隔开。\n");
	for(i=0;i<n;i++)
	{
		scanf("%s %d",data[i],&p[i].f);
		p[i].number=i;
	}
	qsort(p,n,sizeof(p[0]),cmp);//对初始节点以频率从小到大排序
	build();
	get_head();
	for(i=0;i<n-1;i++)//每次选链表前面的两个节点并形成一个新的节点，需循环n-1次
	{
		now=(struct node*)malloc(sizeof(struct node));
		start->parent=now;
		start->type=1;
		start->next->parent=now;
		start->next->type=2;
		now->num=-1;
		now->v=start->v+start->next->v;
		start=start->next->next;
		Insert(now);
	}
	for(i=0;i<n;i++)
		Ans[i].len=0;
	for(i=0;i<n;i++)
		get_ans(head[i],i);
	printf("编码为：\n");
	for(i=0,sum=0;i<n;i++)
	{
		printf("%s ",data[i]);
		sum+=Ans[i].len;
		for(j=Ans[i].len-1;j>=0;j--)//逆序输出
			printf("%d",Ans[i].code[j]);
		printf("\n");
	}
	aver=sum*1.0/n;
	printf("平均长度为%lf\n",aver);
	return 0;
}
/*
11
Data 80
Structure 90
is 100
not 43
very 5
hard 7
for 12
student 120
who 32
like 200
C 21
8
a 5
b 29
c 7
d 8
e 14
f 23
g 3
h 11
*/