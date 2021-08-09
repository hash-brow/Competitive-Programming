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

const int MXN = 3001;
const int C = 100001;

//***************** GLOBAL VARIABLES *****************

int N, M, K, g[MXN][MXN], cnt[C], cur, mx;
int64_t sum;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void shift(int x, int y, int i, int j){
	if(!cnt[g[x][y]]) cur++;
	cnt[g[x][y]]++;
	cnt[g[i][j]]--;
	if(!cnt[g[i][j]]) cur--;
}

void solve(){
	cin >> N >> M >> K;

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> g[i][j];

	for(int i = 1; i < K; i++)
		for(int j = 1; j <= K; j++){
			if(!cnt[g[i][j]]) cur++;
			cnt[g[i][j]]++;
		}

	cnt[0] = K; cur++;

	for(int i = K; i <= N; i++){
		int l, r, z = i - K;
		if(z & 1) l = M - K + 1, r = M;
		else l = 1, r = K;

		for(int j = l; j <= r; j++)
			shift(i, j, z, j);

		sum += cur;
		mx = max(mx, cur);

		if(z & 1){
			for(int j = M - K; j >= 1; --j){
				z = j + K;
				for(int x = i - K + 1; x <= i; x++)
					shift(x, j, x, z);
				sum += cur;
				mx = max(mx, cur);
			}
		}
		else{
			for(int j = K + 1; j <= M; j++){
				z = j - K;
				for(int x = i - K + 1; x <= i; x++)
					shift(x, j, x, z);
				sum += cur;
				mx = max(mx, cur);
			}
		}
	}

	cout << mx << ' ' << sum << '\n';
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