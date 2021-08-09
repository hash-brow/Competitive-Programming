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

const int MOD = 1000000007;
const int MXN = 505;

//***************** GLOBAL VARIABLES *****************

int A[MXN], B[MXN];
int64_t dp[MXN][MXN << 1], F[MXN], iF[MXN], C[MXN];

//***************** AUXILIARY STRUCTS *****************

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


//***************** MAIN BODY *****************

/*
	processing a range of values [D[i], D[i+1])

	we consider every [l, r] such that [1, l-1] lie in [..., D[i])
	and [l, r] lie in [D[i], D[i+1])

	> find the number of schools in [l, r] which can send boats in range [D[i], D[i+1])

	other schools are ignored

	>> add (D[i+1] - D[i]) C x where x is value calculated in >

	dp[i][j] -> insert i into j th interval

	dp[r][j] = sum(dp[l-1][j-1] + ways(l, r, j))

	ways(l, r, j) = >>

	C[i] -> no. of ways of picking up <= i items in increasing order from len items

	dp[i][j] = 
*/

void solve(){
	int N;
	cin >> N;

	vector<int> D;

	for(int i = 0; i < N; i++){
		cin >> A[i] >> B[i];
		D.push_back(A[i]);
		D.push_back(B[i] + 1);
	}

	F[0] = F[1] = 1;
	for(int i = 2; i < MXN; i++){
		F[i] = (F[i-1] * 1LL * i) % MOD;
	}

	iF[MXN - 1] = power(F[MXN - 1]);

	for(int i = MXN - 2; i >= 0; --i){
		iF[i] = (iF[i+1] * 1LL * (i + 1)) % MOD;
	}

	sort(D.begin(), D.end());
	D.erase(unique(D.begin(), D.end()), D.end());

	int n = D.size() - 1;

	int64_t ans = 0;

	for(int _ = 0; _ < n; _++){
		int len = D[_+1] - D[_];
		for(int i = 1; i <= N; i++){
			int64_t p = 1; C[i] = 0;
			for(int j = 1; j <= i; j++){
				p = (p * 1LL * (len - j + 1)) % MOD;
				C[i] = (C[i] + (((p * iF[j]) % MOD) * nCk(i - 1, j - 1)) % MOD) % MOD;
			}
		}

		for(int i = 0; i < N; i++) if(A[i] <= D[_] && B[i] >= D[_+1] - 1) {
			int cnt = 0;
			for(int j = i; j >= 0; j--){
				if(_) (dp[i][_] += dp[j][_-1] * C[cnt]) %= MOD;
				cnt += (A[j] <= D[_] && B[j] >= D[_+1] - 1);
			}
			(dp[i][_] += C[cnt]) %= MOD;
			ans = (ans + dp[i][_]) % MOD;
		}

		for(int i = 0; i < N; i++)
			(dp[i][_] += dp[i][_-1]) %= MOD;
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