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

const int MXN = 200001;
const int K = 20;

//***************** GLOBAL VARIABLES *****************

vector<int> g[MXN], leaf[MXN];
int up[K][MXN], sub[MXN], tin[MXN], tout[MXN], timer, depth[MXN], ans[MXN], counter[MXN];
bool added[MXN];

//***************** AUXILIARY STRUCTS *****************

void dfs(int p, int u){
	depth[u] = depth[p] + 1;
	tin[u] = timer++;

	up[0][u] = p;

	for(int i = 1; i < K; i++)
		up[i][u] = up[i-1][up[i-1][u]];

	for(int v : g[u]) if(v != p){
		dfs(u, v);
	}

	tout[u] = timer++;
}

bool check(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){
	if(check(u, v)) return u;
	if(check(v, u)) return v;

	for(int i = K - 1; i >= 0; --i){
		if(!check(up[i][u], v))
			u = up[i][u];
	}

	return up[0][u];
}

int dist(int u, int v){
	return depth[u] + depth[v] - 2*depth[lca(u, v)];
}

//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	for(int i = 0; i < N - 1; i++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(1, 1);

	for(int i = 1; i <= N; i++)
		if(g[i].size() == 1){
			leaf[1].push_back(i);
			added[i] = 1;
		}

	fill(sub + 1, sub + N + 1, 1);

	for(int s = 1; s <= N; s++) for(int u : leaf[s]) for(int v : g[u]){
		if(added[v]) continue;
		counter[v]++;

		sub[v] += sub[u];

		if(counter[v] == (int)g[v].size() - 1){
			added[v] = 1;
			leaf[sub[v]].push_back(v);
		}
	}

	array<int, 2> e = {-1, -1};
	int j = N >> 1;

	fill(ans + 1, ans + N + 1, 1);

	for(int s = N; s >= 1; --s) for(int x : leaf[s]){
		if(e[0] == -1)
			e[0] = x;
		else if(e[1] == -1)
			e[1] = x;
		else{
			if(dist(e[0], x) > dist(e[0], e[1])) e[1] = x;
			else if(dist(e[1], x) > dist(e[0], e[1])) e[0] = x;
		}

		if(e[1] == -1) continue;

		while(j > min(sub[e[0]], sub[e[1]]))
			--j;

		ans[2*j] = dist(e[0], e[1]) + 1;
	}


	for(int i = N - (N & 1) - 2; i >= 2; i -= 2)
		ans[i] = max(ans[i], ans[i + 2]);

	for(int i = 1; i <= N; i++)
		cout << ans[i] << '\n';
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