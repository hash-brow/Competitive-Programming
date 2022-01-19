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

const int MXN = 50001;
const int LOG = 16;

//***************** GLOBAL VARIABLES *****************

int dp[MXN][LOG][5][5];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int K, N, M, O;
	cin >> K >> N >> M >> O;

	int B = N / K;

	memset(dp, 0x3f, sizeof dp);

	for(int i = 0; i < M; i++){
		int u, v, t;
		cin >> u >> v >> t;
		dp[u / K][0][u % K][v % K] = t;
	}

	for(int j = 1; j < LOG; j++){
		for(int i = 0; i <= B; i++){
			for(int f = 0; f < K; f++)
				for(int t = 0; t < K; t++){
					if(i + (1 << j) > B) continue;
					for(int m = 0; m < K; m++)
						dp[i][j][f][t] = min(dp[i][j][f][t], dp[i][j-1][f][m] + dp[i + (1 << (j - 1))][j-1][m][t]);
				}
		}
	}

	for(int _ = 0; _ < O; _++){
		int u, v;
		cin >> u >> v;
		int x = u / K, y = v / K;

		int res[K];
		memset(res, 0x3f, sizeof res);
		res[u % K] = 0;

		for(int j = LOG - 1; j >= 0; --j){
			if(x + (1 << j) <= y){
				int cur[K];
				memset(cur, 0x3f, sizeof cur);

				for(int t = 0; t < K; t++)
					for(int f = 0; f < K; f++)
						cur[t] = min(cur[t], res[f] + dp[x][j][f][t]);

				for(int i = 0; i < K; i++)
					res[i] = cur[i];

				x += (1 << j);
			}
		}

		cout << (res[v % K] == 1061109567 ? -1 : res[v % K]) << '\n';
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