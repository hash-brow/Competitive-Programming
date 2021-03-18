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
vvi adj;
vi tin, tout;
int timer;
struct segtree{
	vl st;

	int sz = 1;
	void init(int n){
		while(sz < n)
			sz *= 2;

		st.resize(2*sz);
	}
	void set(int l, int r, ll v, int x, int lx, int rx){
		if(lx >= r || rx <= l)
			return;
		if(lx >= l && rx <= r){
			st[x] += v;
			return;
		}
		int m = (lx+rx)/2;
		set(l, r, v, 2*x+1, lx, m);
		set(l, r, v, 2*x+2, m, rx);
	}
	void set(int l, int r, ll v){
		set(l, r, v, 0, 0, sz);
	}
	ll query(int i){	
		int r = sz+i-1;
		ll ans = 0;
		while(r){
			ans += st[r];
			r -= 1;
			r >>= 1;
		}
		ans += st[0];
		return ans;
	}
};	
void dfs(int node){
	tin[node] = timer++;

	for(int v : adj[node])
		dfs(v);

	tout[node] = timer++;
}	
void solve(int tc){
	int n, m;
	cin >> n >> m;
	tin.resize(n), tout.resize(n), adj.resize(n);

	segtree s;
	s.init(2*n);
	vi wage(n);
	cin >> wage[0];
	for(int i = 1; i < n; i++){
		int p;
		cin >> wage[i] >> p;
		--p;
		adj[p].pb(i);
	}
	timer = 0;
	dfs(0);

	for(int i = 0; i < m; i++){
		char q;
		cin >> q;
		if(q == 'p'){
			int a;
			ll x;
			cin >> a >> x;
			s.set(tin[a-1]+1, tout[a-1], x);
		}
		else{
			int u;
			cin >> u;
			cout << wage[u-1] + s.query(tin[u-1])<< '\n';
		}
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