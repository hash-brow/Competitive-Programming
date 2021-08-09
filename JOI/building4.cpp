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

const int MXN = 500'000;

//***************** GLOBAL VARIABLES *****************

int A[2][2*MXN + 1], l[2][2*MXN + 1], r[2][2*MXN + 1];

//***************** AUXILIARY STRUCTS *****************

inline int readInt() {
	int x = 0;
	char ch = getchar_unlocked();
	while (ch < '0' || ch > '9') ch = getchar_unlocked();
	while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
	return x;
}

//***************** MAIN BODY *****************

void solve(){
	int N = readInt();

	for(int j = 1; j >= 0; --j){
		for(int i = 1; i <= 2*N; i++) A[j][i] = readInt();	
	}

	for(int i = 1; i <= 2*N; i++){
		for(int j = 0; j < 2; j++){
			l[j][i] = 2*N + 1, r[j][i] = -1;
			for(int k = 0; k < 2; k++)
				if(A[j][i] >= A[k][i-1]){
					l[j][i] = min(l[j][i], l[k][i-1] + j);
					r[j][i] = max(r[j][i], r[k][i-1] + j);
				}
		}
	}

	int j = -1;

	for(int k = 0; k < 2; k++)
		if(l[k][2*N] <= N && r[k][2*N] >= N){
			j = k;
		}

	if(j < 0){
		cout << "-1\n";
		return;
	}

	string ans(2*N, ' ');

	int cnt = N;

	for(int i = 2*N; i >= 1; --i){
		ans[i - 1] = 'B' - j;
		cnt -= j;
		j = (A[j][i] >= A[1][i-1] && l[1][i-1] <= cnt && r[1][i-1] >= cnt);
	}

	cout << ans << '\n';
}

//***************** *****************

int32_t main(){
	// ios_base::sync_with_stdio(NULL);
	// cin.tie(NULL);

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