#include<cstdio>
#include<iostream>
#define rep(i,j,k) for(int i = j; i <= k; i++)
#define ll long long
using namespace std;

inline int read() {
    int s = 0, t = 1; char c = getchar();
    while( !isdigit(c) ) { if( c == '-' ) t = -1; c = getchar(); }
    while( isdigit(c) ) s = s * 10 + c - 48, c = getchar();
    return s * t;
}

const int N = 12;
const int N_mask = (1 << N) + 5;
const int mod = 998244353;
ll Pow(ll x,int t) {
    ll ret = 1;
    while( t ) {
        if( t & 1 ) ret = ret * x % mod;
        x = x * x % mod, t >>= 1;
    }
    return ret;
}

ll f[N][N_mask][N_mask];
ll g[N_mask][N_mask], h[N_mask][N], gh[N_mask][N_mask];

void _(ll &x) {
    while( x < 0 ) x += mod;
    while( x >= mod ) x -= mod;
}

int lower(int x) {
    return x & -x;
}

int main() {
    int n = read(), k = read();
    for(int i = 1; i <= n * (n-1); i++) {
        int x = read() - 1, y = read() - 1, p = read(), q = read();
        h[1<<x][y] = p * Pow(q,mod-2) % mod;
        _(gh[1<<x][1<<y] = 1 - h[1<<x][y]);
    }

    int mask = (1 << n) - 1;

    for(int j = 1; j <= mask; j++) gh[0][j] = 1;
    for(int i = 1; i <= mask; i++) {
        for(int j = 0; j < n; j++) {
            int x = lower(i);
            gh[i][1<<j] = gh[i^x][1<<j] * gh[x][1<<j] % mod;
        }
    }

    for(int i = 1; i <= mask; i++) {
        int x = mask ^ i, y = x;
        while( y ) {
            ll sum = 1;
            for(int j = 0; j < n; j++) {
                if( (y & (1<<j)) ) {
                    sum = sum * gh[i][1<<j] % mod;
                }
            }
            gh[i][y] = sum;
            y = (y-1) & x;
        }
    }

    for(int i = 1; i <= mask; i++) {
        for(int j = 0; j < n; j++) {
            int x = lower(i);
            h[i][j] = (h[i^x][j] * (gh[x][1<<j] + h[x][j]) + gh[i^x][1<<j] * h[x][j]) % mod;
        }
    }

    for(int i = 1; i <= mask; i++) {
        int x = mask ^ i, y = x;
        while( y ) {
            ll sum = 1;
            for(int j = 0; j < n; j++) {
                if( (y & (1<<j)) ) {
                    sum = sum * h[i][j] % mod;
                }
            }
            g[i][y] = sum;
            y = (y-1) & x;
        }
    }

    f[0][1][1] = 1;
    for(int j = 0; j < k; j++) {
        for(int i = 1; i <= mask; i++) {
            int xi = i, yi = xi;
            while( yi ) {
                if( !f[j][i][yi] ) {
                    yi = (yi - 1) & xi;
                    continue;
                }
                int x = mask ^ i, y = x;
                while( y ) {
                    _(f[j+1][i | y][y] += f[j][i][yi] * g[yi][y] % mod * gh[i^yi][y] % mod);
                    y = (y-1) & x;
                }
                yi = (yi - 1) & xi;
            }
        }
    }

    ll ans = 0;
    for(int i = 0; i <= k; i++) {
        for(int j = 1; j <= mask; j++)
            _(ans += f[i][mask][j]); 
    }

    cout<<ans<<endl;
}