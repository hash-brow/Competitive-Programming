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

template <typename T>
struct BIT{
	int n;
	vector<T> tree;

	BIT(int n){
		this->n = n;
		tree.resize(n+1, 0);
	}
	
	void increment(int idx, T val){
		for(int i = idx + 1; i <= n; i += (i & (-i)))
			tree[i] += val;
	}

	T query(int idx){
		T sum = 0;
		for(int i = idx + 1; i > 0; i -= (i & (-i)))
			sum += tree[i];
		return sum;
	}

	void increment(int l, int r, T val){
		increment(l, val);
		increment(r+1, -val);
	}
};

//***************** MAIN BODY *****************

void solve(){
	int N, M;
	cin >> N >> M;

	BIT<int> S(1000001);
	int A[N];

	for(int i = 0; i < N; i++){
		cin >> A[i];
		if(i){
			S.increment(min(A[i - 1], A[i]) + 1, max(A[i - 1], A[i]) - 1, 1);
		}
	}

	for(int i = 0; i < M; i++){
		int type;
		cin >> type;
		if(type == 1){
			int pos, val;
			cin >> pos >> val;
			--pos;
			if(pos) S.increment(min(A[pos - 1], A[pos]) + 1, max(A[pos - 1], A[pos]) - 1, -1);
			if(pos + 1 < N) S.increment(min(A[pos + 1], A[pos]) + 1, max(A[pos + 1], A[pos]) - 1, -1);

			A[pos] = val;

			if(pos) S.increment(min(A[pos - 1], A[pos]) + 1, max(A[pos - 1], A[pos]) - 1, 1);
			if(pos + 1 < N) S.increment(min(A[pos + 1], A[pos]) + 1, max(A[pos + 1], A[pos]) - 1, 1);
		}
		else{
			int val;
			cin >> val;
			cout << S.query(val) << '\n';
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