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

const int MXN = 1000000;

//***************** AUXILIARY STRUCTS *****************

struct UFDS{
	int e[MXN], cnt;
	UFDS(int N){
		memset(e, -1, sizeof e);
		cnt = N;
	}

	int get(int x) { return (e[x] < 0 ? x : e[x] = get(e[x])); }

	void unite(int x, int y){
		x = get(x), y = get(y);
		if(x == y)
			return;

		cnt--;
		if(e[x] < e[y])
			swap(x, y);

		e[x] += e[y];
		e[y] = x;
	}
};

//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	UFDS D(N);

	for(int i = 0; i < N; i++){
		int x;
		cin >> x;
		D.unite(i, x - 1);
	}

	cout << D.cnt << '\n';
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