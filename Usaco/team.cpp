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

const int MOD = 1000000009;

//***************** GLOBAL VARIABLES *****************



//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, M, K;
	cin >> N >> M >> K;

	int Z = N + M;

	int dp[Z + 1][K + 1][K + 1];

	memset(dp, 0, sizeof dp);
	dp[Z][0][0] = 1;

	array<int, 2> A[Z];

	for(int i = 0; i < N; i++){
		cin >> A[i][0];
		A[i][1] = 0;
	}

	for(int j = 0; j < M; j++){
		cin >> A[j + N][0];
		A[j + N][1] = 1;
	}

	sort(A, A + Z);

	for(int e = Z - 1; e >= 0; --e){
		for(int i = 0; i <= K; i++)
			for(int j = 0; j <= i; j++){
				if(!A[e][1]){
					dp[e][i][j] = (dp[e + 1][i][j] + (i > 0 ? dp[e + 1][i - 1][j] : 0)) % MOD;
				}
				else{
					dp[e][i][j] = (dp[e + 1][i][j] + (j > 0 ? dp[e + 1][i][j - 1] : 0)) % MOD;
				}
			}
	}

	cout << dp[0][K][K] << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	#ifndef LOCAL
		freopen("team.in", "r", stdin);
		freopen("team.out", "w", stdout);
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