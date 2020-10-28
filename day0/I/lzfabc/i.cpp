#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
using namespace std;
inline int read(){
	int x = 0,c = gc;
	while(c < '0' || c > '9') c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
int t,o,cnt;
double f[20][20][6][15][70][4][4][4];
int mp1[15] = {0,1,2,3,4,10,11,12,13,20,21,22,30,31,40},mp2[60],mp3[4010];
double work(int ya,int xa,int lft,int yp,int xp1,int xp2,int yb,int xb,int nw){
	if(ya <= 0) return 1;
	if(xa <= 0) return 0;
	double &pp = f[ya - 1][xa - 1][lft][mp2[yp]][mp3[xp2 * 100 + xp1]][yb][xb][nw];
	if(pp == pp) return pp;
	int xx10 = xp1 / 10,xx11 = xp1 % 10,xx20 = xp2 / 10,xx21 = xp2 % 10,xx0 = xx10 + xx11 + xx20 + xx21,yy1 = yp % 10,yy2 = yp / 10,yy0 = yy1 + yy2,tot = xx0 + yy0 + 2;
	double gl = 1.0 / tot;
	if(nw && nw != 3){
		bool fg = (nw == 2);
		xb -= fg;xp2 += fg;
		(++nw) %= 3;
		pp = gl * work(ya,xa - 1,lft,yp,xp1,xp2,yb,xb,nw);
		pp += gl * work(ya - 1,xa,lft,yp,xp1,xp2,yb,xb,nw);
		if(xx10) pp += gl * xx10 * work(ya,xa,lft,yp,xp1 - 10,xp2,yb,xb,nw);
		if(xx11) pp += gl * xx11 * work(ya,xa,lft,yp,xp1 - 1,xp2,yb,xb,nw);
		if(xx20) pp += gl * xx20 * work(ya,xa,lft,yp,xp1 + 10,xp2 - 10,yb,xb,nw);
		if(xx21) pp += gl * xx21 * work(ya,xa,lft,yp,xp1 + 1,xp2 - 1,yb,xb,nw);
		if(yy1) pp += gl * yy1 * work(ya,xa,lft,yp - 1,xp1,xp2,yb,xb,nw);
		if(yy2) pp += gl * yy2 * work(ya,xa,lft,yp - 9,xp1,xp2,yb,xb,nw);
		return pp;
	}
	if(ya <= 3 * (xx10 + xx20)) return pp = 1;
	if(nw != 3) pp = 1.0 - work(xa,ya,o,(xx20 + xx21) * 10 + (xx10 + xx11),yy1 * 10,yy2 * 10,xb,min(yb + 1,3),3);
	else pp = 0;
	if(lft && xa > 2 && xb != 3) pp = max(pp,work(ya,xa - 2,lft - 1,yp,xp1,xp2,yb,xb + 1,0));
	if(xx10){ 
		if(yy2) pp = max(pp,work(ya,xa,lft,yp - 10,xp1 - 10,xp2,yb,xb,0)); 
		if(yy1) pp = max(pp,work(ya,xa,lft,yp - 1,xp1 - 10,xp2,yb,xb,0)); 
		pp = max(pp,work(ya - 3,xa,lft,yp,xp1 - 9,xp2,yb,xb,0));
	}
	if(xx20){
		if(yy2) pp = max(pp,work(ya,xa,lft,yp - 10,xp1,xp2 - 10,yb,xb,0));
		if(yy1) pp = max(pp,work(ya,xa,lft,yp - 1,xp1,xp2 - 10,yb,xb,0));
		pp = max(pp,work(ya - 3,xa,lft,yp,xp1,xp2 - 9,yb,xb,0)); 
	}
	if(lft && xb && xx0 < 4){
		--lft;
		double qq = gl * work(ya,xa - 1,lft,yp,xp1,xp2,yb,xb,1);
		qq += gl * work(ya - 1,xa,lft,yp,xp1,xp2,yb,xb,1); 
		if(xx10) qq += gl * xx10 * work(ya,xa,lft,yp,xp1 - 10,xp2,yb,xb,1);
		if(xx11) qq += gl * xx11 * work(ya,xa,lft,yp,xp1 - 1,xp2,yb,xb,1);
		if(xx20) qq += gl * xx20 * work(ya,xa,lft,yp,xp1 + 10,xp2 - 10,yb,xb,1);
		if(xx21) qq += gl * xx21 * work(ya,xa,lft,yp,xp1 + 1,xp2 - 1,yb,xb,1);
		if(yy1) qq += gl * yy1 * work(ya,xa,lft,yp - 1,xp1,xp2,yb,xb,1);
		if(yy2) qq += gl * yy2 * work(ya,xa,lft,yp - 9,xp1,xp2,yb,xb,1);
		pp = max(pp,qq);
		++lft;
	}
	return pp;
}
int nwsl = 0;
void dfs(int x,int y,int sl){
	if(x == 5){
		mp3[y] = nwsl++;
		return;
	}
	for(int i = 0;i + sl <= 4;++i){
		dfs(x + 1,y * 10 + i,i + sl);
	}
}
int main(){
	int a,b,k,s,c,d,xp1,xp2,yp;
	for(int i = 1;i < 15;++i) mp2[mp1[i]] = i;
	memset(f,-1,sizeof(f));
	dfs(1,0,0);
	t = read();o = read();
	while(t--){
		a = read();b = read();
		xp1 = xp2 = yp = 0;
		s = read();
		while(s--){
			k = read();
			if(k == 1) ++yp; 
			if(k == 2) yp += 10;
		}
		s = read();
		while(s--){
			k = read();
			if(k == 1) xp1 += 10; 
			if(k == 2) xp2 += 10;
		}
		d = read();c = read();
		printf("%.9lf\n",work(b,a,o,yp,xp1,xp2,d,min(3,c + 1),3));
	}
	return 0;
}
