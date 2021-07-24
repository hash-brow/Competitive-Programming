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

const int64_t INF = 1'000'000'000'000'000'000;

//***************** GLOBAL VARIABLES *****************



//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	set<pair<int64_t, int>> s;
	set<int> idx;
	int64_t val[N + 2];
	val[0] = val[N + 1] = -INF;

	s.insert({val[0], 0}), idx.insert(0);
	s.insert({val[N + 1], N + 1}), idx.insert(N + 1);

	for(int i = 1; i <= N; i++){
		cin >> val[i];
		s.insert({val[i], i});
		idx.insert(i);
	}

	int64_t ans = 0;

	for(int i = 1; i <= (N + 1) / 2; i++){
		auto [inc, j] = *s.rbegin();
		s.erase({inc, j}), idx.erase(j);
		ans += inc;
		cout << ans << '\n';

		int l = *prev(idx.lower_bound(j)), r = *idx.upper_bound(j);

		s.erase({val[l], l});
		s.erase({val[r], r});

		idx.erase(r);

		val[l] = val[l] + val[r] - inc;

		s.insert({val[l], l});
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
*/