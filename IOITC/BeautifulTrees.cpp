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

#define int long long

//***************** CONSTANTS *****************

const int MXN = 1001;
const int MXK = 11;
const int mod = 1'000'000'007;

//***************** GLOBAL VARIABLES *****************

int N, K;
vector<int> g[MXN];

//***************** AUXILIARY STRUCTS *****************

	//***************** LCA *****************

		int up[MXK][MXN];
		int tin[MXN], tout[MXN], dist[MXN];
		int timer = 0;

		void dfs(int node, int par){
			dist[node] = dist[par] + 1;

			tin[node] = timer++;

			up[0][node] = par;
			for(int i = 1; i < MXK; i++)
				up[i][node] = up[i-1][up[i-1][node]];

			for(int v : g[node]){
				if(v != par)
					dfs(v, node);
			}

			tout[node] = timer;
		}

		bool isAncestor(int u, int v){
			return tin[u] <= tin[v] && tout[u] >= tout[v];
		}

		int lca(int u, int v){
			if(isAncestor(u, v))
				return u;
			if(isAncestor(v, u))
				return v;

			for(int i = MXK-1; i >= 0; --i)
				if(!isAncestor(up[i][u], v))
					u = up[i][u];

			return up[0][u];
		}

		int d(int u, int v){
			return dist[u] + dist[v] - 2*dist[lca(u, v)];
		}

	// ***************** Exp *****************

		int eexp(int a, int b){
			int res = 1;

			while(b){
				if(b & 1)
					res = (res * a) % mod;

				b >>= 1;
				a = (a * a) % mod;
			}
			
			return res;
		}

//***************** MAIN BODY *****************

void reset(){
	for(int i = 0; i < N; i++){
		g[i].clear();
		tin[i] = tout[i] = 0;
		dist[i] = 0;
		timer = 1;
	}
}

void solve(){
	cin >> N >> K;
	reset();

	for(int i = 0; i < N - 1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<int> v;
	int root = 0;
	for(int i = 0; i < N; i++){
		if(g[i].size() == 1)
			v.push_back(i);
		else root = i;
	}

	if(v.size() == 2 && K == 1){
		cout << N - 1 << ' ' << eexp(2, N - 2) << '\n';
		return;
	}

	dfs(root, root);

	int64_t ans = 0;

	for(int i = 0; i < v.size(); i++)
		for(int j = i + 1; j < v.size(); j++)
			ans = (ans + 1LL*eexp(d(v[i], v[j]), K)) % mod;

	cout << ans << ' ' << 1 << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
    #endif

	return 0;
}