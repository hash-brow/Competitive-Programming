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

const int MXN = 200000;

//***************** GLOBAL VARIABLES *****************

vector<int> g[MXN];
int ans = 0;
int N, D, d[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

int dfs(int u, int p){
	vector<int> t = {0};
	ans++;

	for(int v : g[u]) if(v != p){
		t.push_back(dfs(v, u) + 1);
	}

	sort(t.begin(), t.end());

	for(int i = t.size() - 1; i >= 1; --i){
		if(t[i] + t[i - 1] < D){
			ans -= i;
			return t[i];
		}
	}

	return t[0];
}

void solve(){
	cin >> N >> D;

	for(int i = 1; i < N; i++){
		int x;
		cin >> x;
		g[x].push_back(i);
	}

	dfs(0, 0);

	cout << ans << '\n';
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