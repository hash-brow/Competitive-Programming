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

	T query(int l, int r){ return query(r) - query(l - 1); }
};

//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	vector<int> A(2*N);
	for(int i = 0; i < 2*N; i++){
		cin >> A[i];
		--A[i];
	}

	int64_t ans = 0;

	BIT<int> D(2*N);

	vector<int> active(N), pos(N);

	for(int i = 0; i < 2*N; i++){
		if(active[A[i]]){
			D.increment(pos[A[i]], -1);
			active[A[i]] = 0;
			ans += D.query(pos[A[i]], i);
		}
		else{
			active[A[i]] = 1;
			D.increment(i, 1);
			pos[A[i]] = i;
		}
	}

	cout << ans + N << '\n';
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