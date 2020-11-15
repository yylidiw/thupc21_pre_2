#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;

struct mark{int x, y;}a[1000010];
int n, K, x, y, z1, z2, map[15][15], re[4100], bin[15], b3[15], f[1000010][15], g[4100][15], G[4100][15],
g1[1000010], g2[1000010], s1, s2, S, ans;

inline int pow(int y, int x){
	int s=1, t=y;
	while(x){if(x&1)s=(ll)s*t%mod; t=(ll)t*t%mod; x>>=1;}
	return s;
}

int main(){
	scanf("%d%d", &n, &K);
	for(int i=1; i<=n*(n-1); i++){scanf("%d%d%d%d", &x, &y, &z1, &z2); map[x][y]=(ll)z1*pow(z2, mod-2)%mod;}
	bin[0]=1; for(int i=1; i<=n; i++)bin[i]=bin[i-1]<<1;
	b3[0]=1; for(int i=1; i<=n; i++)b3[i]=b3[i-1]*3;
	for(int i=0; i<=b3[n]-1; i++){
		a[i].x=a[i].y=0; x=i;
		for(int j=0; j<n; j++){y=x%3; if(y==1)a[i].x+=bin[j]; if(y==2)a[i].y+=bin[j]; x/=3;}
		a[i].x+=a[i].y;
	}
	for(int i=0; i<=bin[n]-1; i++){re[i]=0; for(int j=1; j<=n; j++)if(i&bin[j-1])re[i]+=b3[j-1];}
	for(int i=0; i<=bin[n]-1; i++)
		for(int j=1; j<=n; j++){
			g[i][j]=1; for(int k=1; k<=n; k++)if(i&bin[k-1])g[i][j]=(ll)g[i][j]*(1-map[k][j]+mod)%mod;
			G[i][j]=1-g[i][j]+mod;
		}
	for(int i=0; i<=b3[n]-1; i++){
		s1=a[i].x-a[i].y; s2=a[i].y; g1[i]=g2[i]=1;
		for(int j=1; j<=n; j++)if(s2&bin[j-1]){
			g1[i]=(ll)g1[i]*g[s1][j]%mod;
			g2[i]=(ll)g2[i]*G[s1][j]%mod;
		}
	}
	memset(f, 0, sizeof(f)); f[2][0]=1;
	for(int i=2; i<=bin[n]-1; i++)if(i&1)
		for(int s=i; s; s=(s-1)&i)if(!(s&1)){
			S=re[i]+re[s];
			for(int j=1; j<=K; j++){
				f[S][j]=0; s1=s2=i-s; if(j>=2)s1--;
				for(int ss=s1; ss; ss=(ss-1)&s1){
					if(!f[re[s2]+re[ss]][j-1])continue;
					f[S][j]+=(ll)f[re[s2]+re[ss]][j-1]*g2[re[ss]+(re[s]<<1)]%mod*g1[re[s2-ss]+(re[s]<<1)]%mod;
					if(f[S][j]>=mod)f[S][j]-=mod;
				}
			}
		}
	ans=0;
	for(int i=0; i<=K; i++)
		for(int j=1; j<=bin[n]-1; j++)ans=(ans+f[re[bin[n]-1]+re[j]][i])%mod;
	printf("%d", ans);
	return 0;
}
