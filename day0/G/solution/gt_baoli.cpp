#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;

struct edge{int x, y, z;}a[210];
int n, K, x, y, m1[15][15], ans, h[15], op, cl, d[15];

inline int pow(int y, int x){
	int s=1, t=y;
	while(x){if(x&1)s=(ll)s*t%mod; t=(ll)t*t%mod; x>>=1;}
	return s;
}

inline void check(int now){
	for(int i=1; i<=n; i++)h[i]=n+1; h[1]=1;
	op=0; cl=1; d[1]=1; int x;
	while(op<cl){
		op++; x=d[op];
		for(int i=1; i<=n; i++)if(m1[x][i]&&h[i]>h[x]+1){h[i]=h[x]+1; d[++cl]=i;}
	}
	for(int i=1; i<=n; i++)if(h[i]>=K+2)return;
	ans=(ans+now)%mod;
}
inline void dfs(int i, int now){
	if(i==n*(n-1)+1){check(now); return;}
	dfs(i+1, (ll)now*(1-a[i].z+mod)%mod);
	m1[a[i].x][a[i].y]=1;
	dfs(i+1, (ll)now*a[i].z%mod);
	m1[a[i].x][a[i].y]=0;
}

int main(){
	scanf("%d%d", &n, &K);
	for(int i=1; i<=n*(n-1); i++){scanf("%d%d%d%d", &a[i].x, &a[i].y, &x, &y); a[i].z=(ll)x*pow(y, mod-2)%mod;}
	memset(m1, 0, sizeof(m1));
	ans=0; dfs(1, 1); printf("%d", ans);
	return 0;
}
