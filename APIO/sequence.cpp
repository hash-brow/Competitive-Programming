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

const int MXN = 100001;
const int MXK = 201;
const int64_t INF = 1'000'000'000'000'000'000;

//***************** GLOBAL VARIABLES *****************

int64_t dp[2][MXN];
int parent[MXK][MXN];
int64_t pref[MXN];
int N, K;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void dnc(int l, int r, int t, int optl, int optr, int row){
	if(l > r)
		return;

	int mid = (l + r) >> 1;
	pair<int64_t, int> best = {-1, -1};

	for(int i = optl; i < min(mid, optr + 1); i++){
		int64_t val = dp[t ^ 1][i] + (pref[mid] - pref[i]) * (pref[N] - pref[mid]);
		if(val > best.first)
			best = {val, i};
	}

	dp[t][mid] = best.first;
	parent[row][mid] = best.second;

	dnc(l, mid - 1, t, optl, best.second, row);
	dnc(mid + 1, r, t, best.second, optr, row);
}

void solve(){
	cin >> N >> K;

	for(int i = 1; i <= N; i++){
		cin >> pref[i];
		pref[i] += pref[i-1];
	}

	for(int i = 0; i <= N; i++)
		dp[0][i] = dp[1][i] = -INF;
	
	dp[0][0] = 0;

	for(int i = 1; i <= K; i++)
		dnc(i, N - 1, i & 1, i - 1, N - 1, i);

	pair<int64_t, int> ans = {-1, -1};

	for(int i = 1; i < N; i++)
		ans = max(ans, {dp[K & 1][i], i});

	cout << ans.first << '\n';

	for(int i = K, var = ans.second; i; var = parent[i][var], --i)
		cout << var << ' ';
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