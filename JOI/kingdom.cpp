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

const int NAX = 2000;

//***************** GLOBAL VARIABLES *****************

int grid[NAX][NAX], temp[NAX][NAX];
int H, W;
int mxv = 0, mnv = 1'000'000'000;

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	cin >> H >> W;
	for(int i = 0; i < H; i++)
		for(int j = 0; j < W; j++){
			cin >> grid[i][j];
			mxv = max(mxv, grid[i][j]);
			mnv = min(mnv, grid[i][j]);
		}

	function<void()> vert = [](){
		for(int i = 0; i < H; i++)
			for(int j = 0; j < W; j++)
				temp[H - i - 1][j] = grid[i][j];

		for(int i = 0; i < H; i++)
			for(int j = 0; j < W; j++)
				grid[i][j] = temp[i][j];
	};

	function<void()> hor = [](){
		for(int i = 0; i < H; i++)
			for(int j = 0; j < W; j++)
				temp[i][W - j - 1] = grid[i][j];

		for(int i = 0; i < H; i++)
			for(int j = 0; j < W; j++)
				grid[i][j] = temp[i][j];
	};

	function<bool(int)> check = [](int mid)->bool{
		int cur = H - 1;
		for(int j = 0; j < W; j++){
			for(int i = 0; i <= cur; i++)
				if(mxv - grid[i][j] > mid){
					cur = i - 1;
					break;
				}

			for(int i = cur + 1; i < H; i++){
				if(grid[i][j] - mnv > mid)
					return false;
			}
		}

		return true;
	};

	function<int()> find = [&]()->int{
		int lo = 0, hi = mxv - mnv + 1, ans = mxv - mnv + 1;
		while(lo <= hi){
			int mid = (lo + hi) >> 1;
			if(check(mid))
				ans = mid, hi = mid - 1;
			else lo = mid + 1;
		}
		return ans;
	};

	int ans = find();
	hor();
	ans = min(ans, find());
	vert();
	ans = min(ans, find());
	hor();
	ans = min(ans, find());

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