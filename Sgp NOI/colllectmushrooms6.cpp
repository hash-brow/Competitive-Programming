// #define _GLIBCXX_DEBUG
// #pragma GCC optimize "trapv"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
using namespace std;
using namespace __gnu_pbds;
 
#define pb push_back 
#define f first
#define s second
#define min3(a, b, c) min(min(a, b), c)
#define max3(a, b, c) max(max(a, b), c)
#define all(v) v.begin(), v.end()
 
typedef long long ll;
typedef double ld;
typedef long double lld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
 
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
 
const int INF = 1e9;
// const ll INF = 1e18;
const ll mod = 1000000007;
// const ll mod = 998244353;
vvi pref;
void update(int c1, int c2, int r1, int r2){
    pref[r1][c1]++;
    pref[r2+1][c2+1]++;
    pref[r2+1][c1]--;
    pref[r1][c2+1]--;
}
void solve(int tc){
    int r, c, d, k;
 
    cin >> r >> c >> d >> k;
 
    pref.assign(r+2, vi(c+2, 0));
    vvi mat(r, vi(c, 0));
 
    for(int i = 0; i < r; i++){
        string s;
        cin >> s;
 
        for(int j = 0; j < c; j++){
            if(s[j] == 'M') mat[i][j] = 2;
            else if(s[j] == 'S') mat[i][j] = 1;
        }
    }
 
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            if(mat[i-1][j-1] == 1)
                update(max(1, j-d), min(c, j+d), max(1, i-d), min(r, i+d));
               
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            pref[i][j] += pref[i][j-1] + pref[i-1][j] - pref[i-1][j-1]; 
 
    int ans = 0;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++)
            if(mat[i-1][j-1] == 2 && pref[i][j] >= k) ans++;
    }
 
    cout << ans << '\n';
}
 
int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    
    int tc = 1;
    // cin >> tc;
    for (int t = 0; t < tc; t++) solve(t);
 
    return 0;
}