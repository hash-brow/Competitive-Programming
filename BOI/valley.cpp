#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/

using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
/*
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

//***************** CONSTANTS *****************

const int MXN = 100000;
const int K = 17;
const int64_t INF = 1000000000000000000;

//***************** GLOBAL VARIABLES *****************

vector<array<int, 2>> g[MXN];
int N, S, Q, root;
int up[K][MXN], tin[MXN], tout[MXN], timer;
int64_t s[MXN], D[MXN], mn[K][MXN];
array<int, 2> e[MXN];

//***************** AUXILIARY STRUCTS *****************

void dfs(int u, int p, int64_t d){
	tin[u] = timer++;
	D[u] = d;
	for(auto& [v, w] : g[u]) if(v != p){
		dfs(v, u, d + w);
		s[u] = min(s[u], s[v] + w);
	}
	tout[u] = timer++;
}
	
void calc(int u, int p){
	up[0][u] = p;
	mn[0][u] = min(s[u] - D[u], s[p] - D[p]);

	for(int i = 1; i < K; i++){
		up[i][u] = up[i-1][up[i-1][u]];
		mn[i][u] = min(mn[i-1][u], mn[i-1][up[i-1][u]]); 
	}

	for(auto& [v, w] : g[u]) if(v != p){
		calc(v, u);
	}
}

inline bool is_ancestor(int u, int k, int v){
	u = up[k][u];
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

//***************** MAIN BODY *****************

void solve(){
	cin >> N >> S >> Q >> root;
	--root;

	for(int i = 0; i < N - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
		e[i] = {u, v};
	}

	fill(s, s + N, INF);

	for(int i = 0; i < S; i++){
		int u;
		cin >> u;
		--u;
		s[u] = 0;
	}

	dfs(root, root, 0);
	calc(root, root);

	for(int _ = 0; _ < Q; _++){
		int x, u;
		cin >> x >> u;
		--x, --u;

		if(tin[e[x][0]] > tin[e[x][1]])
			swap(e[x][0], e[x][1]);

		x = e[x][1];
		if(tin[x] <= tin[u] && tout[x] >= tout[u]){
			int64_t ans = s[u] - D[u];
			int y = u;
			for(int i = K - 1; i >= 0; --i)
				if(!is_ancestor(u, i, x)){
					ans = min(ans, mn[i][u]);
					u = up[i][u];
				}

			ans = min(ans, s[x] - D[x]);

			if(ans + D[y] >= INF / 2) cout << "oo\n";
			else cout << ans + D[y] << '\n'; 
		}
		else cout << "escaped\n";
	}
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	// cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
	#endif

	return 0;
}

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/