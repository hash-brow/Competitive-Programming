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



//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N;
	int64_t M;
	cin >> N >> M;

	vector<int64_t> A(N);
	for(int i = 0; i < N; i++)
		cin >> A[i];

	vector<int64_t> X(1 << (N / 2));
	for(int mask = 0; mask < (1 << (N / 2)); mask++){
		for(int i = 0; i < 20; i++)
			if((mask >> i) & 1)
				X[mask] += A[i];
	}

	sort(X.begin(), X.end());

	int64_t ans = 0;

	for(int mask = 0; mask < (1 << (N - N / 2)); mask++){
		int64_t temp = 0;
		for(int i = 0; i < 20; i++)
			if((mask >> i) & 1)
				temp += A[N/2 + i];
		ans += upper_bound(X.begin(), X.end(), M - temp) - X.begin();
	}

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