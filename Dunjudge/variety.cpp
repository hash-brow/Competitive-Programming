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

// const int INF = 1e9;
const ll INF = LLONG_MAX;
const ll mod = 1000000007;
// const ll mod = 998244353;
bool Compare(pair<ll, int> a, pair<ll, int> b){
	if(a.f > b.f) return true;
	return false;
}
void solve(int tc){
	int n, m; 
	ll w;
	cin >> n >> m >> w;

	vector<vector<pair<int, ll>>> adj(n+1);

	for(int i = 0; i < m; i++){
		int u, v; 
		ll c;
		cin >> u >> v >> c;
		adj[u].pb({v+1, c}); 
	}
	for(int i = n; i > 0; --i){
		adj[i].pb({i-1, w}); 
	}

	vl dis(n + 1, INF); 
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, function<bool(pair<ll, int>, pair<ll, int>)>> q(Compare); 
	vector<bool> vis(n + 1, 0); 
	dis[0] = 0;
	q.push({0, 0}); 

	while(!q.empty()){
		int node = q.top().s; 
		ll cur_dis = q.top().f;
		q.pop();
		if(cur_dis > dis[node]) continue;		

		for(auto e : adj[node]){
			if(dis[e.f] <= cur_dis + e.s) continue; 
			dis[e.f] = cur_dis + e.s; 
			q.push({dis[e.f], e.f}); 
		}
	}

	cout << (dis[n] == INF ? -1 : dis[n]) << '\n';
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