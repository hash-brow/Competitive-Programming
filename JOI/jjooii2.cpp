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

unordered_map<char, int> T = {{'J', 0}, {'O', 1}, {'I', 2}};

//***************** MAIN BODY *****************

void solve(){
	int N, k;
	cin >> N >> k;

	int ans = N + 5;

	vector<int> A[3];

	for(int i = 0; i < N; i++){
		char c;
		cin >> c;
		A[T[c]].push_back(i);
	}

	int start, end;

	for(int i = 0; i + k - 1 < A[0].size(); i++){
		start = A[0][i];
		end = A[0][i + k - 1];

		start = lower_bound(A[1].begin(), A[1].end(), end) - A[1].begin();
		end = start + k - 1;

		if(end >= A[1].size())
			continue;

		start = lower_bound(A[2].begin(), A[2].end(), A[1][end]) - A[2].begin();
		end = start + k - 1;

		if(end >= A[2].size())
			continue;

		ans = min(ans, A[2][end] - A[0][i] + 1 - 3*k);
	}

	cout << (ans == N + 5 ? -1 : ans) << '\n';
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

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/