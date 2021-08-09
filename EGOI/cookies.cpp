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

const int K = 21;

//***************** GLOBAL VARIABLES *****************

vector<int> A(K);

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

int query(int s, int e){
	cout << "? ";
	for(int i = s; i <= e; i++)
		cout << i << ' ';
	cout << endl;

	int x;
	cin >> x;
	return x;
}

void answer(int x, int y){
	int t = x&y;
	x ^= t, y ^= t;

	cout << "! " << __builtin_popcount(x) << ' ' << __builtin_popcount(y) << '\n';
	for(int i = 0; i < K; i++)
		if((x >> i) & 1)
			cout << A[i] << ' ';
	cout << '\n';
	for(int i = 0; i < K; i++)
		if((y >> i) & 1)
			cout << A[i] << ' ';
	cout << '\n';
}

void solve(){
	int N;
	cin >> N;

	for(int i = 0; i < K; i++){
		A[i] = query(i*N + 1, (i + 1)*N);
	}

	vector<array<int, 2>> T(1 << K);
	for(int mask = 0; mask < (1 << K); mask++){
		T[mask][1] = mask;
		for(int i = 0; i < K; i++)
			if((mask >> i) & 1)
				T[mask][0] += A[i];
	}

	sort(T.begin(), T.end());

	for(int i = 1; i < (1 << K); i++){
		if(T[i][0] == T[i-1][0]){
			answer(T[i][1], T[i-1][1]);
			break;
		}
	}
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