// Cao Quang Hung
#include<bits/stdc++.h>

using namespace std;
#define REP(i,a,b) for(int (i)=(a);(i)<=(b);++i)
#define REPD(i,a,b) for(int (i)=(a); (i)>=(b);--i)
#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define pii pair<int,int>
#define pll pair<long long , long long>
#define vi vector<int>
#define SZ(x) ((int)(x.size()))
#define ALL(t) t.begin(),t.end()
#define dem(x) __builtin_popcount(x)
#define Mask(x) (1LL << (x))
#define BIT(x, i) ((x) >> (i) & 1)
#define ln '\n'

///mt19937 rnd(time(0));

const int INF = 1e9 , mod = 1e9 + 7;

template <class T1, class T2>
inline T1 mul(T1& x, const T2 &k){ return x = (1LL * x * k) % mod; }

template <class T1 , class T2>
inline T1 pw(T1 x, T2 k){T1 res = 1; for (; k ; k >>= 1){ if (k & 1) mul(res, x); mul(x, x); } return res;}

template <class T>
inline bool minimize(T &x, const T &y){ if (x > y){x = y; return 1;} return 0; }

template <class T>
inline bool maximize(T &x, const T &y){ if (x < y){x = y; return 1;} return 0; }

template <class T>
inline void add(T &x , const T &y){ if ((x += y) >= mod) x -= mod; }

template <class T>
inline T product (const T &x , const T &y) { return 1LL * x * y % mod; }

typedef long long ll;
typedef double db;
const int N = 2e5 + 5;

void readip(){
    
}

void solve(){   
   
}


#define PROB "a"
void file(){
    if(fopen(PROB".inp", "r")){
        freopen(PROB".inp","r",stdin);
        freopen(PROB".out","w",stdout);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    file();
    int t = 1;
//    cin >> t;
    while (t--){
        readip();
        solve();
    }
}