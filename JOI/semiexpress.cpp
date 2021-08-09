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
	int64_t N, M, K, A, B, C, T;
	cin >> N >> M >> K >> A >> B >> C >> T;

	int64_t S[M];
	for(int i = 0; i < M; i++)
		cin >> S[i];

	priority_queue<int64_t> q;

	int64_t ans = 0;

	for(int i = 0; i < M - 1 && T > 0; i++){
		int64_t mid = S[i + 1] - S[i];
		for(int64_t j = 0, x = 0; j <= K - M; j++){
			int64_t next = min(mid - x, (T - x * C + A) / A);
			if(next <= 0)
				break;
			x += next;
			if(j) q.push(next);
			if(!j) ans += next;
		}

		T -= mid * B;
		if(T < 0) ans--;
	}

	for(int i = 0; i < K - M && !q.empty(); i++)
		ans += q.top(), q.pop();

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