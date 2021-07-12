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

	BIT(int _n){
		this->n = _n + 1;
		tree.resize(n, 0);
	}

	void increment(int idx, T val){
		for(int i = idx + 1; i < n; i += (i & (-i)))
			tree[i] += val;
	}

	T query(int idx){
		T sum = 0;
		for(int i = idx + 1; i > 0; i -= (i & (-i)))
			sum += tree[i];
		return sum;
	}
};


//***************** MAIN BODY *****************

void solve(){
	int N;
	cin >> N;

	pair<int64_t, int> pre[N + 1];
	pre[0] = {0, 0};
	for(int i = 1; i <= N; i++){
		cin >> pre[i].first;
		pre[i].second = i;
		pre[i].first += pre[i-1].first;
	}

	int64_t P;
	cin >> P;

	for(int i = 1; i <= N; i++) pre[i].first -= P*1LL*i;
	sort(pre, pre + N + 1);

	int compress[N + 1], idx = 0;
	compress[pre[0].second] = idx;

	for(int i = 1; i <= N; i++){
		idx += (pre[i].first != pre[i-1].first);
		compress[pre[i].second] = idx;
	}

	BIT<int> s(idx + 1);

	int64_t ans = 0;

	for(int i = 0; i <= N; i++){
		ans += s.query(compress[i]);
		s.increment(compress[i], 1);
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