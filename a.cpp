#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m;
int ne;
struct data{int to,next,v;}e[6000001];
int head[1000001];
int h[1000001],q[1000001],ans;
void insert(int u,int v,int w)
{
	ne++;
	e[ne].to=v;
	e[ne].v=w;
	e[ne].next=head[u];
	head[u]=ne;
}
bool bfs()
{
    int now,i;
    memset(h,-1,sizeof(h));
    int t=0,w=1;
    q[t]=1;h[1]=0;
    while(t<w)
    {   
        now=q[t];t++;
        i=head[now];
        while(i)
        {
            if(e[i].v&&h[e[i].to]<0)
            {
				q[w++]=e[i].to;
				h[e[i].to]=h[now]+1;                 
            }
            i=e[i].next;
        }
    }
    if(h[n*m]==-1)return 0;
    return 1;
}
int dfs(int x,int f)
{
    if(x==n*m)return f;
    int i=head[x];
    int w,used=0;
    while(i)
    {
        if(e[i].v&&h[e[i].to]==h[x]+1)
        {
            w=f-used;
            w=dfs(e[i].to,min(w,e[i].v));
            e[i].v-=w;
            e[i+1].v+=w;
            used+=w;
            if(used==f)return f;
		}
		i=e[i].next;
	}
	if(!used)h[x]=-1;
	return used;
}
void dinic()
{
	while(bfs())ans+=dfs(1,0x7fffffff);
}
int main()
{
    scanf("%d%d",&n,&m);
    int x;
    for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			insert(m*(i-1)+j,m*(i-1)+j+1,x);
			insert(m*(i-1)+j+1,m*(i-1)+j,x);
		}
    for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			insert(m*(i-1)+j,m*(i)+j,x);
			insert(m*(i)+j,m*(i-1)+j,x);
		}
    for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			insert(m*(i-1)+j,m*(i)+j+1,x);
			insert(m*(i)+j+1,m*(i-1)+j,x);
		}
    dinic();
    printf("%d",ans);
    return 0;
}
