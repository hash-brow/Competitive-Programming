#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;


//***************** CONSTANTS *****************

const int MXN = 100'000;
const int INF = 100'000'000;

//***************** GLOBAL VARIABLES *****************

ordered_set<pair<int, int>> mp[MXN];
vector<int> g[MXN];
int a[MXN], ans[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void dfs(int u, int p){
	for(int v : g[u]) if(v != p){
		dfs(v, u);
		if(mp[v].size() > mp[u].size())
			mp[u].swap(mp[v]);
		
		for(auto &px : mp[v])
			mp[u].insert(px);
	}

	ans[u] += mp[u].size() - mp[u].order_of_key({a[u], INF});
	mp[u].insert({a[u], u});
}

void solve(){
	int N;
	cin >> N;

	for(int i = 0; i < N; i++)
		cin >> a[i];

	for(int i = 1; i < N; i++){
		int u;
		cin >> u;
		--u;
		g[u].push_back(i);
	}

	dfs(0, 0);

	for(int i = 0; i < N; i++)
		cout << ans[i] << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	#ifndef LOCAL
		freopen("promote.in", "r", stdin);
		freopen("promote.out", "w", stdout);
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