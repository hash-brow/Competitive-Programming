// #define _GLIBCXX_DEBUG
// #pragma GCC optimize "trapv"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>
 
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
using namespace std;
using namespace __gnu_pbds;
using namespace chrono;
 
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
struct DSU{
    vi e;
    void init(int n){
        e = vi(n, -1);
    }
 
    int get(int x){
        return (e[x] < 0 ? x : e[x] = get(e[x]));
    }
 
    bool same_set(int x, int y){
        return get(x) == get(y);
    }
 
    void unite(int x, int y){
        x = get(x), y = get(y);
 
        if(e[x] < e[y])
            swap(x, y);
 
        e[x] += e[y];
        e[y] = x;
        return;
    }
};
vi dp;
vector<vpi> g;
void dfs(int node, int p, int w){
    dp[node] = min(dp[p], w);
 
    for(auto v : g[node]){
        if(v.f == p) continue;
        dfs(v.f, node, v.s);
    }
}
void solve(int tc){
    int n, m, q;
    cin >> n >> m >> q;
 
    vector<array<int, 3>> edges(m);
 
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges.pb({u, v, w});
    }
 
    sort(all(edges), [&](array<int, 3> a, array<int, 3> b){
        if(a[2] > b[2]) return true;
        return false;
    });
 
    DSU s;
    s.init(n);
    dp.resize(n), g.resize(n);
    for(auto a : edges){
        if(s.get(a[0]) == s.get(a[1])) continue;
        s.unite(a[0], a[1]);
        g[a[0]].pb({a[1], a[2]});
        g[a[1]].pb({a[0], a[2]});
    }
    dp[0] = INF;
    dfs(0, 0, INF); 
 
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        --x;
        cout << dp[x] << '\n';
    }
}
 
int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    #ifdef LOCAL
        auto begin = high_resolution_clock::now();
    #endif
 
    int tc = 1;
    // cin >> tc; 
    for (int t = 0; t < tc; t++) solve(t);
    
    #ifdef LOCAL 
        auto end = high_resolution_clock::now();
        cout << fixed << setprecision(4) << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
    #endif
    return 0;
}