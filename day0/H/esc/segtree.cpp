#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
    int F()
    {
        int n=0,F=0;
        char ch;
        while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
        ch=='-'?F=1:n=ch-'0';
        while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
        return F?-n:n;
    }
    long long G()
    {
        long long n=0,F=0;
        char ch;
        while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
        ch=='-'?F=1:n=ch-'0';
        while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
        return F?-n:n;
    }
}
const int M=1000000007;

int main()
{
    int T=io::F();
    while(T--)
    {
        long long n=io::G();
        long long len[2]={n,n};
        int l[2]={1,0},r[2]={1,0},c[2]={1,0};
        int ans=1;
        while(len[1]>1)
        {
            long long h=len[0]>>1;
            int ll[2]={},rr[2]={},cc[2]={};
            for(int i=0;i<=1;++i)
                if(len[i]>1)
                {
                    long long d[2]={len[i]>>1,len[i]+1>>1};
                    ans=(ans+d[1]%M*l[i]+d[0]%M*r[i])%M;
                    (ll[d[0]!=h]+=l[i])%=M;
                    (ll[d[1]!=h]+=(l[i]+d[0]%M*c[i])%M)%=M;
                    (rr[d[1]!=h]+=r[i])%=M;
                    (rr[d[0]!=h]+=(r[i]+d[1]%M*c[i])%M)%=M;
                    (cc[d[0]!=h]+=c[i])%=M;
                    (cc[d[1]!=h]+=c[i])%=M;
                }
            for(int i=0;i<=1;++i)
                l[i]=ll[i],r[i]=rr[i],c[i]=cc[i],len[i]=h+i;
        }
        printf("%d\n",ans);
    }
}