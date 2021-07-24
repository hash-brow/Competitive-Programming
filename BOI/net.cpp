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

vector<int> g[MXN], leaves;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void dfs(int node, int p){
	if(g[node].size() == 1) leaves.push_back(node + 1);
	for(int v : g[node]) if(v != p) dfs(v, node);
}

void solve(){
	int N;
	cin >> N;

	for(int i = 0; i < N - 1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(0, 0);

	int c = leaves.size();

	cout << (c + 1) / 2 << '\n';

	for(int i = 0; i < c / 2; i++)
		cout << leaves[i] << ' ' << leaves[i + c/2] << '\n';

	if(c & 1) cout << leaves[c - 2] << ' ' << leaves[c - 1] << '\n';
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