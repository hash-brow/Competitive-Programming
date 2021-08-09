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

const int MXN = 500'000;

//***************** GLOBAL VARIABLES *****************

vector<int> g[MXN];
map<int, int> mp[MXN];
int deg[MXN], st[MXN], cnt[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void dfs(int u, int p){
	if(cnt[st[u]] != 1) mp[u][st[u]] = 1;

	for(int v : g[u]) if(v != p){
		dfs(v, u);
		if(!mp[v].size()){
			deg[u]++;
			deg[v]++;
		}
		else{
			deg[u] += deg[v];
			deg[v] = 0;
		}

		if(mp[v].size() > mp[u].size()) swap(mp[u], mp[v]);

		for(auto& [state, count] : mp[v]){
			mp[u][state] += count;
			if(mp[u][state] == cnt[state]) mp[u].erase(state);
		}
	}
}

void solve(){
	int N, K;
	cin >> N >> K;
	for(int i = 0; i < N - 1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for(int i = 0; i < N; i++){
		cin >> st[i];
		--st[i];
		cnt[st[i]]++;
	}

	dfs(0, 0);

	int ans = 0;

	for(int i = 0; i < N; i++) ans += (deg[i] == 1);

	cout << (ans + 1) / 2 << '\n';
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
*/