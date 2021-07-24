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
	int N, L;
	cin >> N >> L;

	vector<array<int, 2>> A(N);
	for(auto& [x, y] : A)
		cin >> x >> y;

	double lo = 0, hi = sqrt(3e18);

	for(int _ = 0; _ < 70; _++){
		double mid = (lo + hi) / 2, maxl = 0;
		for(auto& [x, y] : A){
			double dx = sqrt(mid * mid - y * 1LL * y);
			if(x - dx <= maxl) maxl = max(maxl, x + dx);
		}

		(maxl < L ? lo : hi) = mid;
	}

	cout << fixed << setprecision(9) << (lo + hi) / 2 << '\n';
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