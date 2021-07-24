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
const int INF = 0x3f3f3f3f;

//***************** GLOBAL VARIABLES *****************

int dp[MXN][2][2], on[MXN];
vector<int> g[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void dfs(int u, int p){
	int temp[2][2][2];
	memset(temp, INF, sizeof temp);

	temp[0][0][0] = temp[0][1][0] = 0;
	for(int v : g[u]) if(v != p){
		dfs(v, u);
		memset(temp[1], INF, sizeof temp[1]);

		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				for(int k = 0; k < 2; k++)
					temp[1][i][j^k] = min(temp[1][i][j^k], temp[0][i][j] + dp[v][i][k]);

		swap(temp[0], temp[1]);
	}

	dp[u][0][0] = temp[0][0][on[u]];
	dp[u][0][1] = temp[0][1][on[u]^1] + 1;
	dp[u][1][0] = temp[0][0][on[u]^1];
	dp[u][1][1] = temp[0][1][on[u]] + 1;
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

	for(int i = 0; i < N; i++)
		cin >> on[i];

	memset(dp, INF, sizeof dp);

	dfs(0, 0);

	int ans = min(dp[0][0][0], dp[0][0][1]);

	if(ans > N) cout << "impossible\n";
	else cout << ans << '\n';
}

/*
	dp[N][2][2] -> dp[u][i][j] -> currently considering the uth node in state i and press j
	temp[c][2][2] -> tmp[v][i][j] -> vth child, is u toggled, j -> parity of selection
*/

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