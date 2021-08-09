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

const int64_t MOD = 1'000'000'007;

//***************** GLOBAL VARIABLES *****************

int64_t F[100005], iF[100005];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

int64_t power(int64_t n, int64_t x = MOD - 2){
	int64_t res = 1;
	while(x){
		if(x & 1)
			res = (res * n) % MOD;

		x >>= 1;
		n = (n * n) % MOD;
	}
	return res;
}

inline int64_t nCk(int n, int k){
	return F[n] * ((iF[n - k] * iF[k]) % MOD) % MOD;
}

void solve(){
	int N, K;
	cin >> N >> K;

	F[0] = F[1] = 1;
	for(int i = 2; i <= N + 1; i++){
		F[i] = (F[i-1] * 1LL * i) % MOD;
	}

	iF[N + 1] = power(F[N + 1]);

	for(int i = N; i >= 0; --i){
		iF[i] = (iF[i+1] * 1LL * (i + 1)) % MOD;
	}

	int64_t ans = 0, t = 1;

	for(int i = 0; i <= K; i++){
		(ans += t*nCk(N + 1, i)*1LL*power(K - i, N)) %= MOD;
		ans = (ans + MOD) % MOD;
		t = -t;
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