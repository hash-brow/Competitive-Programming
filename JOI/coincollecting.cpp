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
 
const int MXN = 100000;
 
//***************** GLOBAL VARIABLES *****************
 
int c[MXN][3];
 
//***************** AUXILIARY STRUCTS *****************
 
 
 
//***************** MAIN BODY *****************
 
void solve(){
	int N;
	cin >> N;
 
	int64_t ans = 0;
 
	for(int i = 0; i < 2*N; i++){
		int x, y;
		cin >> x >> y;
		if(x < 1) ans += 1 - x, x = 1;
		else if (x > N) ans += x - N, x = N;
 
		if(y < 1) ans += 1 - y, y = 1;
		else if (y > 2) ans += y - 2, y = 2;
 
		c[x][y]++;
	}
 
	int64_t l = 0, r = 0;
 
	for(int i = 1; i <= N; i++){
		l += c[i][1] - 1;
		r += c[i][2] - 1;
 
		if(l > 0 && r < 0){
			int t = min(l, -r);
			ans += t;
			r += t;
			l -= t;
		}
		else if(l < 0 && r > 0){
			int t = min(-l, r);
			ans += t;
			r -= t;
			l += t;
		}
 
		ans += abs(l) + abs(r);
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
