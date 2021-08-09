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

const int MXN = 1001;
const int INF = 2'000'000'000;

//***************** GLOBAL VARIABLES *****************

int A[MXN];
int dp[MXN][MXN][2]; // dp[i][j][0] -> left endpoint is i, right is j and you are at (0 : 1 :: left : right)

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	for(int i = 0; i < N; i++)
		cin >> A[i];

	A[N++] = 0;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			dp[i][j][0] = dp[i][j][1] = INF;

	sort(A, A + N);

	int mid;

	for(int i = 0; i < N; i++)
		if(A[i] == 0){
			mid = i;
			dp[mid][mid][0] = dp[mid][mid][1] = 0;
		}

	for(int i = mid - 1; i >= 0; i--){
		dp[i][mid][0] = dp[i + 1][mid][0] + (N - mid + i) * (A[i + 1] - A[i]);
	}

	for(int i = mid + 1; i < N; i++){
		dp[mid][i][1] = dp[mid][i - 1][1] + (N - i + mid) * (A[i] - A[i - 1]);
	}

	for(int i = mid - 1; i >= 0; i--){
		for(int j = mid + 1; j < N; j++){
			int len = N - j + i;
			dp[i][j][0] = min(dp[i + 1][j][0] + len * (A[i + 1] - A[i]), dp[i + 1][j][1] + len * (A[j] - A[i]));
			dp[i][j][1] = min(dp[i][j - 1][0] + len * (A[j] - A[i]), dp[i][j - 1][1] + len * (A[j] - A[j - 1]));
		}
	}

	cout << min(dp[0][N-1][0], dp[0][N-1][1]) << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifndef LOCAL
		freopen("cowrun.in", "r", stdin);
		freopen("cowrun.out", "w", stdout);
	#endif
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