#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

#define dbg(x) cout << "[" << #x << ' ' << x << "] ";

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;


//***************** CONSTANTS *****************

const int MXN = 1'000'001;

//***************** GLOBAL VARIABLES *****************

int A[MXN], N;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	cin >> N;

	for(int i = 1; i <= N; i++){
		cin >> A[i];
	}

	int ans = 0;

	set<int> s;
	s.insert(MXN);

	for(int i = 1, j; i <= N; i = j){
		j = i + 1;
		int x = *s.upper_bound(A[i]);
		s.insert(A[i]);

		while(j <= N && A[j] >= A[j - 1] && A[j] <= x)
			s.insert(A[j++]);

		++ans;
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

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/

/*
dp[i] -> minimum no. of subarrays to break into to finish this job

if a subsegment is purely increasing in nature, the number of 

3 6  -> 3 3 7

use an ordered set

*/