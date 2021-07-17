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

const int INF = 1'000'000'001;

//***************** MAIN BODY *****************

void solve(){
	int N, M;
	cin >> N >> M;

	int pref[N + 1];
	pref[0] = INF;
	for(int i = 1; i <= N; i++){
		cin >> pref[i];
		pref[i] = min(pref[i], pref[i - 1]);
	}

	int last = N;

	for(int i = 0; i < M; i++){
		int x;
		cin >> x;
		int lo = 0, hi = last, ans = 0;
		while(lo <= hi){
			int mid = (lo + hi) >> 1;
			if(pref[mid] >= x){
				ans = mid;
				lo = mid + 1;
			}
			else hi = mid - 1;
		}
		last = ans - 1;
	}

	cout << last + 1 << '\n';
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