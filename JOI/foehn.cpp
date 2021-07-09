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
	int N, Q, S, T;
	cin >> N >> Q >> S >> T;

	int64_t A[N + 1];

	for(int i = 0; i <= N; i++)
		cin >> A[i];

	int64_t diff[N], add[N];
	int64_t ans = 0;

	memset(diff, 0, sizeof diff);
	memset(add, 0, sizeof add);

	for(int i = 0; i < N; i++){
		diff[i] = A[i] - A[i + 1];
		add[i] = (diff[i] < 0 ? S : T);
		ans += diff[i] * add[i];
	}

	for(int i = 0; i < Q; i++){
		int l, r, x;
		cin >> l >> r >> x;
		ans -= diff[l - 1] * add[l - 1];
		diff[l - 1] -= x;
		add[l - 1] = (diff[l - 1] < 0 ? S : T);
		ans += diff[l - 1] * add[l - 1];

		if(r < N){
			ans -= diff[r] * add[r];
			diff[r] += x;
			add[r] = (diff[r] < 0 ? S : T);
			ans += diff[r] * add[r];
		}

		cout << ans << '\n';
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