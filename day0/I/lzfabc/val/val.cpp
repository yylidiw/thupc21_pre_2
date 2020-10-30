#include<bits/stdc++.h>
#define gc getchar()
using namespace std;
inline int read(int l,int r){
	int x = 0,c = gc;
	while(c < '0' || c > '9'){
		if(c == -1){
			assert(l == -1);
			return -1;
		} 
		assert(c == ' ' || c == '\r' || c == '\n');
		c = gc;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\r' || c == '\n');
	assert(x >= l && x <= r);
	return x;
}
int main(){
	int t = read(1,351493);read(3,5); 
	while(t--){
		read(1,20);read(1,20);
		int k = read(0,4);
		while(k--) read(1,2);
		k = read(0,4);
		while(k--) read(1,2);
		read(0,3);read(0,3);
	}
	read(-1,-1);
	return 0;
}

