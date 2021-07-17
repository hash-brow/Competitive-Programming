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



//***************** GLOBAL VARIABLES *****************

char grid[3002][3002];
int dp[3002][3002][3];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, M;
	cin >> N >> M;

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> grid[i][j];

	function<bool(int, int)> vert = [&](int i, int j)->bool{
		return grid[i][j] == 'G' && grid[i-1][j] == 'R' && grid[i+1][j] == 'W';
	};

	function<bool(int, int)> hor = [&](int i, int j)->bool{
		return grid[i][j] == 'G' && grid[i][j-1] == 'R' && grid[i][j+1] == 'W';
	};

	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= M; j++){
			for(int k = 0; k < 3; k++)
				dp[i][j][0] = max(dp[i][j][0], dp[i-1][j+1][k]);

			if(vert(i, j)) dp[i][j][1] = max(dp[i-1][j+1][0], dp[i-1][j+1][1]) + 1;
			if(hor(i, j)) dp[i][j][2] = max(dp[i-1][j+1][0], dp[i-1][j+1][2]) + 1;
		}
	}

	int ans = 0;
	
	for(int i = 1; i <= N; i++)
		ans += max({dp[i][1][0], dp[i][1][1], dp[i][1][2]});

	for(int i = 2; i <= M; i++)
		ans += max({dp[N][i][0], dp[N][i][1], dp[N][i][2]});

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