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

const int MOD = 1'000'000'007;

//***************** GLOBAL VARIABLES *****************

int64_t dp[2001][2001];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, s, e;
	cin >> N >> s >> e;

	dp[1][1] = 1;

	for(int i = 2; i <= N; i++)
		for(int j = 1; j <= N; j++){
			if(i == s || i == e){
				dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % MOD;
				continue;
			}
			dp[i][j] = ((dp[i-1][j+1] * 1LL * j) % MOD + (dp[i-1][j-1] * 1LL *(j - (i > s) - (i > e))) % MOD) % MOD;
		}

	cout << dp[N][1] << '\n';
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