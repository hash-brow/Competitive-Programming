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
	int H, W;
	cin >> H >> W;

	int grid[H][W];

	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++){
			char x;
			cin >> x;
			if(x == 'J') grid[i][j] = 1;
			if(x == 'I') grid[i][j] = 2;
			if(x == 'O') grid[i][j] = 3;
		}
	}

	int orb[H][W], ingot[H][W];
	memset(orb, 0, sizeof orb);
	memset(ingot, 0, sizeof ingot);

	int64_t ans = 0;
	
	for(int i = H - 1; i >= 0; --i){
		for(int j = W - 1; j >= 0; --j){
			orb[i][j] = (grid[i][j] == 3);
			ingot[i][j] = (grid[i][j] == 2);
			if(j < W - 1) orb[i][j] += orb[i][j+1];
			if(i < H - 1) ingot[i][j] += ingot[i+1][j];

			if(grid[i][j] == 1)
				ans += orb[i][j] * 1LL * ingot[i][j];
		}
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
*/