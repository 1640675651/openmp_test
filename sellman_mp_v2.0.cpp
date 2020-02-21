#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<omp.h>
using namespace std;
int n;
unsigned int ans[100001];
struct home
{
	int a;
	int s;
}h[100001];
bool cmp(const home &a,const home &b)
{
	if(a.a>b.a)return 1;
	else return 0;
}
unsigned int dp[4][100001];
bool vis[4][100001];

int main()
{
	clock_t start=clock();
	freopen("sellman.in","r",stdin);
	cin>>n;
	int k;
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i].s);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i].a);
	
	sort(h+1,h+n+1,cmp);
	#pragma omp parallel for num_threads(4)
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",i);
		int threadnum=omp_get_thread_num();
		memset(dp[threadnum],0,sizeof(dp)/4);
		memset(vis[threadnum],0,sizeof(vis)/4);
		dp[threadnum][1]=h[i].s*2+h[i].a;
		vis[threadnum][i]=1;
		int j=1;
		for(int x=2;x<=n;x++)
		{
			/*for(int j=1;j<=i;j++)
			{
				if(h[j].a>maxa && vis[j]==0)
				{
					maxa=h[j].a;
					k=j;
				}
			}*/
			while((vis[threadnum][j]==1 || h[j].s>=h[i].s) && j<=n+1)
				j++;
			if(j==n+1)break;
			dp[threadnum][x]=dp[threadnum][x-1]+h[j].a;
			vis[threadnum][j]=1;
			
		}
		for(int j=1;j<=n;j++)
		{
			if(ans[j]<dp[threadnum][j])
				ans[j]=dp[threadnum][j];
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		printf("%u\n",ans[i]);
	}
	clock_t end=clock();
	cout<<(end-start)/CLOCKS_PER_SEC<<"sec"<<endl;
	return 0;
	
}
