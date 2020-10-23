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
        while((ch=getchar())>='0'&&ch<'9')n=n*10+ch-'0';
        return F?-n:n;
    }
}
int T,O;
const int P=3604,HP=15;
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
double f[P][S][V][MO+2];
bool vis[P][S][V][MO+2];
double g[3][P][S][V][MO+1];
bool vg[3][P][S][V][MO+1];
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
        T=io::F(),O=io::F();
        init0();
        init1();
        init2();
    }
}INIT;

double dp(int p,int s,int v,int o);

double rnddamage(int k,int p,int s,int v,int o)
{
    if(k==-1)return dp(p,s,add1[v],o);
    if(vg[k][p][s][v][o])return g[k][p][s][v][o];
    vg[k][p][s][v][o]=1;
    double &ans=g[k][p][s][v][o];
    int ohp=php[p][0],shp=php[p][1];
    int oh=hnd[p][0],sh=hnd[p][1];
    int vs=at[v][0];
    int sm1=hp[vs][1],sm2=hp[vs][2];
    int om1=hp[s][1],om2=hp[s][2];
    int at1=at[v][1],at2=at[v][2];
    double uni=1.0/(2+sm1+sm2+om1+om2);
    ans+=ohp==1?1:rnddamage(k-1,pno[ohp-1][shp][oh][sh],s,v,o); //hit opponent's face
    if(shp!=1)ans+=rnddamage(k-1,pno[ohp][shp-1][oh][sh],s,v,o); //hit my face
    if(om1)ans+=om1*rnddamage(k-1,p,sno[om1-1][om2],v,o); //hit opponent's minion with hp=1
    if(om2)ans+=om2*rnddamage(k-1,p,sno[om1+1][om2-1],v,o); //hit opponent's minion with hp=2
    if(at1)ans+=at1*rnddamage(k-1,p,s,vno[sno[sm1-1][sm2]][at1-1][at2],o); //hit my not attacked minion with hp=1
    if(at2)ans+=at2*rnddamage(k-1,p,s,vno[sno[sm1+1][sm2-1]][at1+1][at2-1],o); //hit my not attacked minion with hp=2
    if(sm1-at1)ans+=(sm1-at1)*rnddamage(k-1,p,s,vno[sno[sm1-1][sm2]][at1][at2],o); //hit my attacked minion with hp=1
    if(sm2-at2)ans+=(sm2-at2)*rnddamage(k-1,p,s,vno[sno[sm1+1][sm2-1]][at1][at2],o); //hit my attacked minion with hp=2
    ans*=uni;
    return ans;
}

double dp(int p,int s,int v,int o)
{
    if(vis[p][s][v][o])return f[p][s][v][o];
    vis[p][s][v][o]=1;
    int ohp=php[p][0],shp=php[p][1];
    int oh=hnd[p][0],sh=hnd[p][1];
    int vs=at[v][0];
    double &max=f[p][s][v][o];
    double tmp;
    int sm1=hp[vs][1],sm2=hp[vs][2];
    int om1=hp[s][1],om2=hp[s][2];

    //attack
    {    
        for(int i=1;i<=2;++i)
            if(at[v][i])
            {
                if(ohp<=3)return max=1,1;
                int vv=vno[vs][at[v][1]-(i==1)][at[v][2]-(i==2)];
                tmp=dp(pno[ohp-3][shp][oh][sh],s,vv,dmin(o,O)); //go face
                cmax(max,tmp);

                if(om1)
                {
                    tmp=dp(p,sno[om1-1][om2],vno[sno[sm1-(i==1)][sm2-(i==2)]][at[v][1]-(i==1)][at[v][2]-(i==2)],dmin(o,O)); // hit minion with hp=1
                    cmax(max,tmp);
                }
                if(om2)
                {
                    tmp=dp(p,sno[om1][om2-1],vno[sno[sm1-(i==1)][sm2-(i==2)]][at[v][1]-(i==1)][at[v][2]-(i==2)],dmin(o,O)); // hit minion with hp=2
                    cmax(max,tmp);
                }
            }
    }

    if(o)
    {
        if(shp>2)
        {
            tmp=dp(pno[ohp][shp-2][oh][dmin(H,sh+1)],s,v,dmin(o,O)-1); //hero skill
            cmax(max,tmp);
        }
        
        if(sh&&sm1+sm2<L)
        {
            tmp=rnddamage(2,pno[ohp][shp][oh][sh-1],s,v,dmin(o,O)-1); //play a card
            cmax(max,tmp);
        }
    }   

    if(o<=O)
    {
        tmp=1-dp(opop[p],at[v][0],ful[s],O+1); //end turn
        cmax(max,tmp);
    }
    return max;
}
int main()
{
    while(T--)
    {
        int E,S,c,a[3]={},p,e[3]={}; //itsme
        E=io::F();
        S=io::F();
        c=io::F();
        for(int i=1;i<=c;++i)
            a[io::F()]++;
        p=io::F();
        for(int i=1;i<=p;++i)
            e[io::F()]++;
        int oh=io::F(),sh=io::F();
        if(sh<H)++sh;
        printf("%.9lf\n",dp(pno[S][E][oh][sh],sno[a[1]][a[2]],ful[sno[e[1]][e[2]]],O+1));
    }
    return 0;
}

//laoshicaibi