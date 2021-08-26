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

struct FenwickTree{
	vector<int> tree;
	int n;
	FenwickTree(int N){
		tree.resize(N + 1);
		n = N;
	}
	void add(int x, int v){
		for(; x <= n; x += (x & (-x)))
			tree[x] += v;
	}
	int get(int x){
		int sum = 0;
		for(; x; x -= (x & (-x)))
			sum += tree[x];
		return sum;
	}
};

//***************** MAIN BODY *****************

int64_t count_swaps(vector<int> S){
	int N = S.size() / 2;
	vector<array<int, 2>> ord[N+1];

	for(int i = 0; i < 2*N; i++){
		ord[abs(S[i])].push_back({S[i], i});
	}

	int64_t ret = 0;

	FenwickTree X(2*N);
	for(int i = 1; i <= 2*N; i++) X.add(i, 1);

	vector<array<int, 2>> p;

	for(int i = 1; i <= N; i++){
		sort(ord[i].begin(), ord[i].end());
		int z = ord[i].size() >> 1;
		for(int j = 0; j < z; j++){
			int l = ord[i][j][1], r = ord[i][j + z][1];
			if(l > r){
				swap(l, r);
				ret++;
			}
			p.push_back({l + 1, r + 1});
		}
	}

	sort(p.begin(), p.end());
	for(auto& [l, r] : p){
		ret += X.get(r - 1) - X.get(l);
		X.add(r, -1);
		X.add(l, -1);
	}

	return ret;
}

//***************** *****************

// int32_t main(){
// 	vector<int> S = {-2, 2, 2, -2, -2, 2};
// 	// vector<int> S = {2, 1, -1, -2};
// 	cout << count_swaps(S);
// }

// int32_t main(){
// 	ios_base::sync_with_stdio(NULL);
// 	cin.tie(NULL);

// 	#ifdef LOCAL
// 		auto begin = high_resolution_clock::now();
// 	#endif

// 	int tc = 1;
// 	cin >> tc; 
// 	for (int t = 0; t < tc; t++)
// 		solve();

// 	#ifdef LOCAL 
// 		auto end = high_resolution_clock::now();
// 		cout << fixed << setprecision(4);
// 		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
// 	#endif

// 	return 0;
// }

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/