#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 1000000007
#define pa(a, b, c, d) (data){a, b, c, d}
using namespace std;
struct data{ll x, ls, rs, sum;}a[3], b[3];
int T;
ll n, ans, L, R, x, ls, rs, sum;
inline void ins(ll x, ll ls, ll rs, ll sum){
	if(!a[1].x)a[1]=pa(x, ls, rs, sum);
	else if(a[1].x==x){a[1].ls=(a[1].ls+ls)%mod; a[1].rs=(a[1].rs+rs)%mod; a[1].sum=(a[1].sum+sum)%mod;}
	else if(!a[2].x)a[2]=pa(x, ls, rs, sum);
	else if(a[2].x==x){a[2].ls=(a[2].ls+ls)%mod; a[2].rs=(a[2].rs+rs)%mod; a[2].sum=(a[2].sum+sum)%mod;}
	else printf("WA\n");
}
int main(){
	scanf("%d", &T);
	for(int owo=1; owo<=T; owo++){
		scanf("%lld", &n);
		ans=1;
		a[1]=pa(n, 1, 1, 1); a[2]=pa(0, 0, 0, 0);
		while(a[1].x||a[2].x){
			b[1]=a[1]; b[2]=a[2];
			a[1]=a[2]=pa(0, 0, 0, 0);
			for(int i=1; i<=2; i++)if(b[i].x>=2){
				L=(b[i].x+1)>>1; R=b[i].x-L;
				ans=(ans+(ll)b[i].ls*(R%mod)%mod)%mod;
				ans=(ans+(ll)b[i].rs*(L%mod)%mod)%mod;
				x=L; ls=b[i].ls; rs=(b[i].rs+(ll)(R%mod)*b[i].sum%mod)%mod; sum=b[i].sum;
				ins(x, ls, rs, sum);
				x=R; ls=(b[i].ls+(ll)(L%mod)*b[i].sum%mod)%mod; rs=b[i].rs; sum=b[i].sum;
				ins(x, ls, rs, sum);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
