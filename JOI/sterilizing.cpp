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

struct SegmentTree{
	vector<int64_t> tree;
	int sz = 1;

	SegmentTree(int N, vector<int>& A){
		while(sz < N)
			sz <<= 1;
		tree.resize(2*sz);
		build(A, 0, 0, sz);
	}

	void build(vector<int>& A, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < A.size())
				tree[x] = A[lx];
			return;
		}

		int mid = (lx + rx) >> 1;
		build(A, 2*x + 1, lx, mid);
		build(A, 2*x + 2, mid, rx);

		tree[x] = tree[2*x + 1] + tree[2*x + 2]; 
	}

	void update(int val, int idx, int x, int lx, int rx){
		if(rx - lx == 1){
			tree[x] = val;
			return;
		}

		int mid = (lx + rx) >> 1;
		if(idx < mid) update(val, idx, 2*x + 1, lx, mid);
		else update(val, idx, 2*x + 2, mid, rx);

		tree[x] = tree[2*x + 1] + tree[2*x + 2];
	}

	void update(int val, int idx) { update(val, idx, 0, 0, sz); }

	void spray(int K, int l, int r, int x, int lx, int rx){
		if(rx <= l || lx >= r || tree[x] == 0)
			return;
		if(rx - lx == 1){
			tree[x] /= K;
			return;
		}

		int mid = (lx + rx) >> 1;
		spray(K, l, r, 2*x + 1, lx, mid);
		spray(K, l, r, 2*x + 2, mid, rx);

		tree[x] = tree[2*x + 1] + tree[2*x + 2];
	}

	void spray(int K, int l, int r) { spray(K, l, r, 0, 0, sz); }

	int64_t query(int l, int r, int x, int lx, int rx){
		if(rx <= l || lx >= r || tree[x] == 0)
			return 0;
		if(lx >= l && rx <= r)
			return tree[x];

		int mid = (lx + rx) >> 1;
		return query(l, r, 2*x + 1, lx, mid) + query(l, r, 2*x + 2, mid, rx);
	}

	int64_t query(int l, int r) { return query(l, r, 0, 0, sz); }
};

//***************** MAIN BODY *****************

void solve(){
	int N, Q, K;
	cin >> N >> Q >> K;

	vector<int> A(N);

	for(int i = 0; i < N; i++)
		cin >> A[i];

	SegmentTree S(N, A);

	while(Q--){
		int type, l, r;
		cin >> type >> l >> r;
		if(type == 1){
			S.update(r, l - 1);
		}
		if(type == 2){
			if(K > 1) S.spray(K, l - 1, r);
		}
		if(type == 3){
			cout << S.query(l - 1, r) << '\n';
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