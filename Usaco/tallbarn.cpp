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
	int N; int64_t K;
	cin >> N >> K;

	K -= N;

	int64_t A[N];

	for(int i = 0; i < N; i++) cin >> A[i];

	double lo = 0, hi = 1e18;
	
	function<int64_t(double)> cnt = [&](double x) -> int64_t{
		int64_t c = 0;
		for(int i = 0; i < N; i++){
			c += int64_t((sqrt(1 + 4 * 1.0 * A[i] / x) - 1) / 2);
		}
		return c;
	};

	for(int i = 0; i < 200; i++){
		double mid = (lo + hi) / 2;
		if(cnt(mid) > K)
			lo = mid;
		else hi = mid;
	}

	double ans = 0;
	int64_t tot = 0;

	for(int i = 0; i < N; i++){
		int64_t x = int64_t((sqrt(1 + 4 * 1.0 * A[i] / lo) - 1) / 2);
		tot += x;
		ans += 1.0 * A[i] / (x + 1);
	}

	cout << int64_t(round(ans - (K - tot) * lo)) << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	#ifndef LOCAL
		freopen("tallbarn.in", "r", stdin);
		freopen("tallbarn.out", "w", stdout);
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