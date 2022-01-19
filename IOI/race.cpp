#include <bits/stdc++.h>
#ifndef LOCAL
#include "race.h"
#endif

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
 
const int MXN = 200000;
 
//***************** GLOBAL VARIABLES *****************
 
vector<array<int, 2>> g[MXN];
map<int, int> mp[MXN];
int ans = INT_MAX, K, sz[MXN], r[MXN];
int64_t depth[MXN];

//***************** AUXILIARY STRUCTS *****************

int dfs(int p, int u){
	sz[u] = 1;

	for(auto& [v, d] : g[u]) if(v != p){
		sz[u] += dfs(u, v);
	}

	return sz[u];
}

void dfs2(int p, int u, int s, int len){
	if(depth[u] > K)
		return;

	if(mp[s].find(depth[u]) != mp[s].end()) mp[s][depth[u]] = min(mp[s][depth[u]], len);
	else mp[s][depth[u]] = len;

	for(auto& [v, d] : g[u]) if(v != p && !r[v]){
		depth[v] = depth[u] + d;
		dfs2(u, v, s, len + 1);
	}
}

void decompose(int u){
	int inv = -1, lim = sz[u] >> 1;

	for(auto& [v, d] : g[u])
		if(!r[v] && sz[v] > lim){
			inv = v;
			break;
		}

	if(inv != -1){
		sz[u] -= sz[inv];
		sz[inv] += sz[u];
		decompose(inv);

		return;
	}

	r[u] = 1;

	mp[u].clear();

	for(auto& [v, d] : g[u]) if(!r[v]){
		mp[v].clear();
	}

	depth[u] = 0;

	for(auto& [v, d] : g[u]) if(!r[v]){
		depth[v] = d;
		dfs2(u, v, v, 1);
	}

	mp[u][0] = 0;

	for(auto& [v, d] : g[u]) if(!r[v]){
		for(auto& [dep, len] : mp[v]){
			if(dep <= K && mp[u].find(K - dep) != mp[u].end()) ans = min(ans, len + mp[u][K - dep]);
		}

		for(auto& [dep, len] : mp[v]){
			if(dep > K)
				continue;

			if(mp[u].find(dep) != mp[u].end()) mp[u][dep] = min(mp[u][dep], len);
			else mp[u][dep] = len;
		}
	}

	for(auto& [v, d] : g[u]) if(!r[v]){
		decompose(v);
	}
}

//***************** MAIN BODY *****************

int best_path(int N, int k, int H[][2], int L[]){
	for(int i = 0; i < N - 1; i++){
		g[H[i][0]].push_back({H[i][1], L[i]});
		g[H[i][1]].push_back({H[i][0], L[i]});
	}
 
	K = k;

	dfs(0, 0);

	decompose(0);

	return (ans == INT_MAX ? -1 : ans);
}
 
//***************** *****************
 
#ifdef LOCAL
int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
 
	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif
 
	int tc = 1;
	// cin >> tc; 
	for (int t = 0; t < tc; t++){
		int N, k;
		cin >> N >> k;
 
		int H[N-1][2], L[N-1];
		for(int i = 0; i < N-1; i++)
			cin >> H[i][0] >> H[i][1] >> L[i];
 
		cout << best_path(N, k, H, L) << '\n';
	}
 
	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
	#endif
 
	return 0;
}
#endif
/*
If code gives a WA, check for the following : 
1. I/O format
 
2. Are you clearing all global variables in between tests if multitests are a thing
 
3. Can you definitively prove the logic
 
4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/
