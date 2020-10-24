#include<bits/stdc++.h>
#define cmax(a,b) (a<(b)?a=(b),1:0)
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
}
int T,O;
const int P=6404,HP=20;
const int L=4,H=3;
const int S=17,V=72;
const int MO=5;
int php[P][2]; //player hp
int hnd[P][2]; //card in hand
int pno[HP+2][HP+2][H+1][H+1];
int hp[S][3]; //minion hp
int at[V][3]; //minion not attacked
int sno[L+1][L+1];
int vno[S][L+1][L+1];
int ful[S];
int add1[V]; // add an attacked minion with hp=2
int ptot,atot,htot;
int opop[P];
struct init
{
    void init0()
    {
        for(int i=0;i<=L;++i)
            for(int j=0;i+j<=L;++j)
            {
                ++ptot;
                hp[ptot][1]=i;
                hp[ptot][2]=j;
                sno[i][j]=ptot;
            }
    }
    void init1()
    {
        for(int i=1;i<=HP;++i)
            for(int j=1;j<=HP;++j)
                for(int k=0;k<=H;++k)
                    for(int l=0;l<=H;++l)
                    {
                        ++htot;
                        php[htot][0]=i;
                        php[htot][1]=j;
                        hnd[htot][0]=k;
                        hnd[htot][1]=l;
                        pno[i][j][k][l]=htot;
                    }
        for(int i=1;i<=htot;++i)
            opop[i]=pno[php[i][1]][php[i][0]][hnd[i][1]][dmin(H,hnd[i][0]+1)];
    }
    void init2()
    {
        for(int i=ptot;i;--i)
        {
            for(int j=0;j<=hp[i][1];++j)
                for(int k=0;k<=hp[i][2];++k)
                {
                    ++atot;
                    at[atot][0]=i;
                    at[atot][1]=j;
                    at[atot][2]=k;
                    vno[i][j][k]=atot;
                    if(hp[i][1]+hp[i][2]<L)
                        add1[atot]=vno[sno[hp[i][1]][hp[i][2]+1]][j][k];
                }
            ful[i]=atot;
        }
    }
    init()
    {
        init0();
        init1();
        init2();
    }
}INIT;


int R(int l,int r)
{
    return (rand()<<15|rand())%(r-l+1)+l;
}

struct state
{
    int p,s1,s2;
}ss[1888888];
int main()
{
    int T=351493,O=io::F();
    srand(time(0));
    freopen("5.in","w",stdout);
    int ps=0;
    for(int i=1;i<=htot;++i)
        for(int j=1;j<=ptot;++j)
            for(int k=1;k<=ptot;++k)
                ss[++ps]=(state){i,j,k};
    for(int i=2;i<=ps;++i)
        std::swap(ss[i],ss[R(1,i)]);
    printf("%d %d\n",T,O);
    for(int i=1;i<=T;++i)
    {
        printf("%d %d\n",php[ss[i].p][1],php[ss[i].p][0]);
        printf("%d",hp[ss[i].s1][1]+hp[ss[i].s1][2]);
        std::vector<int> v;
        for(int j=1;j<=hp[ss[i].s1][1];++j)
            v.push_back(1);
        for(int j=1;j<=hp[ss[i].s1][2];++j)
            v.push_back(2);
        std::random_shuffle(v.begin(),v.end());
        for(int j : v)
            printf(" %d",j);
        puts("");
        printf("%d",hp[ss[i].s2][1]+hp[ss[i].s2][2]);
        v.clear();
        for(int j=1;j<=hp[ss[i].s2][1];++j)
            v.push_back(1);
        for(int j=1;j<=hp[ss[i].s2][2];++j)
            v.push_back(2);
        std::random_shuffle(v.begin(),v.end());
        for(int j : v)
            printf(" %d",j);
        puts("");
        printf("%d %d\n",hnd[ss[i].p][0],hnd[ss[i].p][1]);
    }

    freopen("6.in","w",stdout);
    printf("%d %d\n",T,O);
    for(int i=T+1;i<=T+T;++i)
    {
        printf("%d %d\n",php[ss[i].p][1],php[ss[i].p][0]);
        printf("%d",hp[ss[i].s1][1]+hp[ss[i].s1][2]);
        std::vector<int> v;
        for(int j=1;j<=hp[ss[i].s1][1];++j)
            v.push_back(1);
        for(int j=1;j<=hp[ss[i].s1][2];++j)
            v.push_back(2);
        std::random_shuffle(v.begin(),v.end());
        for(int j : v)
            printf(" %d",j);
        puts("");
        printf("%d",hp[ss[i].s2][1]+hp[ss[i].s2][2]);
        v.clear();
        for(int j=1;j<=hp[ss[i].s2][1];++j)
            v.push_back(1);
        for(int j=1;j<=hp[ss[i].s2][2];++j)
            v.push_back(2);
        std::random_shuffle(v.begin(),v.end());
        for(int j : v)
            printf(" %d",j);
        puts("");
        printf("%d %d\n",hnd[ss[i].p][0],hnd[ss[i].p][1]);
    }
    return 0;
}

//laoshicaibi