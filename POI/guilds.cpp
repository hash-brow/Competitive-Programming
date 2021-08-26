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

const int MXN = 200'000;

//***************** GLOBAL VARIABLES *****************

vector<int> g[MXN];
int ans[MXN];

//***************** AUXILIARY STRUCTS *****************

struct UFDS{
	int e[MXN];
	UFDS() { memset(e, -1, sizeof e); }
	int get(int x){return (e[x] < 0 ? x : e[x] = get(e[x])); }
	int sz(int x){return -e[get(x)]; }
	bool unite(int x, int y){
		x = get(x), y = get(y);
		if(x == y)
			return 0;

		if(e[x] > e[y])
			swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return 1;
	}
};


//***************** MAIN BODY *****************

void dfs(int u, int p, int d){
	ans[u] = d;
	for(int v : g[u]) if(v != p){
		dfs(v, u, 1 - d);
	}
}

void solve(){
	int N, M;
	cin >> N >> M;

	UFDS S;

	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(S.unite(u, v)){
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}

	for(int i = 0; i < N; i++)
		if(S.sz(i) == 1){
			cout << "NIE\n";
			return;
		}

	memset(ans, -1, sizeof ans);

	for(int i = 0; i < N; i++){
		if(ans[i] == -1)
			dfs(i, i, 0);
	}

	cout << "TAK\n";
	for(int i = 0; i < N; i++)
		cout << (ans[i] == 0 ? 'K' : 'S') << '\n';
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