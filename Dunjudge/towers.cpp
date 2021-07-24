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

const int64_t MOD = 1000000007;

//***************** GLOBAL VARIABLES *****************



//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

int f(int x){
	return (x * (x + 1)) >> 1;
}

void solve(){
	int R, G;

	cin >> R >> G;

	int64_t dp[2][R + 1];
	bool touch[2][R + 1];

	memset(dp, 0, sizeof dp);
	memset(touch, 0, sizeof touch);

	dp[0][0] = 1, touch[0][0] = 1;

	int h;

	for(int i = 1; i < 1500; i++){
		int cur = (i & 1), prev = (i & 1) ^ 1;

		memset(dp[cur], 0, sizeof dp[cur]);
		memset(touch[cur], false, sizeof touch[cur]);

		int bound = f(i - 1);

		for(int j = 0; j <= min(R, bound); j++){
			int red = R - j;
			int green = G - f(i - 1) + j;

			if(red >= i){
				dp[cur][j + i] = (dp[cur][j + i] + dp[prev][j]) % MOD;
				touch[cur][j + i] |= touch[prev][j];
			}

			if(green >= i){
				dp[cur][j] = (dp[cur][j] + dp[prev][j]) % MOD;
				touch[cur][j] |= touch[prev][j];
			}
		}

		bool cont = false;
		for(int j = 0; j <= R; j++)
			cont |= touch[cur][j];

		if(!cont){
			h = prev;
			break;
		}
	}

	int ans = 0;
	for(int i = 0; i <= R; i++)
		ans = (ans + dp[h][i]) % MOD;

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
*/