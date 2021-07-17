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

const int64_t INF = 1'000'000'000'000'000;

//***************** GLOBAL VARIABLES *****************



//***************** AUXILIARY STRUCTS *****************

struct SegmentTree{
	vector<int64_t> total, lazy, mint;
	int sz = 1;
	
	SegmentTree(int N, vector<int>& A){
		while(sz < N)
			sz <<= 1;

		total.resize(2*sz);
		lazy.resize(2*sz);
		mint.resize(2*sz, INF);

		build(A, 0, 0, sz);
	}

	void merge(int x){
		total[x] = total[2*x + 1] + total[2*x + 2];
		mint[x] = min(mint[2*x + 1], mint[2*x + 2]);
	}

	void apply(int x, int lx, int rx, int64_t val){
		total[x] += (rx - lx) * val;
		mint[x] += val;
	}

	void push(int x, int lx, int rx){
		int mid = (lx + rx) >> 1;
		apply(2*x + 1, lx, mid, lazy[x]);
		apply(2*x + 2, mid, rx, lazy[x]);

		lazy[2*x + 1] += lazy[x];
		lazy[2*x + 2] += lazy[x];

		lazy[x] = 0;
	}

	void build(vector<int>& A, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < A.size()){
				total[x] = mint[x] = A[lx];
				lazy[x] = 0;
			}
			return;
		}

		int mid = (lx + rx) >> 1;
		build(A, 2*x + 1, lx, mid);
		build(A, 2*x + 2, mid, rx);

		merge(x);
	}

	void update(int64_t val, int l, int r, int x, int lx, int rx){
		if(lx >= r || rx <= l)
			return;

		if(lx >= l && rx <= r){
			lazy[x] += val;
			apply(x, lx, rx, val);
			return;
		}

		push(x, lx, rx);

		int mid = (lx + rx) >> 1;
		update(val, l, r, 2*x + 1, lx, mid);
		update(val, l, r, 2*x + 2, mid, rx);

		merge(x);
	}

	array<int64_t, 2> query(int l, int r, int x, int lx, int rx){
		if(lx >= r || rx <= l)
			return {0, INF};

		if(lx >= l && rx <= r)
			return {total[x], mint[x]};

		push(x, lx, rx);
		
		int mid = (lx + rx) >> 1;

		array<int64_t, 2> lc = query(l, r, 2*x + 1, lx, mid);
		array<int64_t, 2> rc = query(l, r, 2*x + 2, mid, rx);

		return {lc[0] + rc[0], min(lc[1], rc[1])};
	}

	void update(int64_t val, int l, int r) { update(val, l, r, 0, 0, sz); }

	array<int64_t, 2> query(int l, int r) { return query(l, r, 0, 0, sz); }
};

//***************** MAIN BODY *****************

void solve(){
	int N, Q;
	cin >> N >> Q;

	vector<int> A(N);
	for(int i = 0; i < N; i++)
		cin >> A[i];

	SegmentTree S(N, A);

	while(Q--){
		char type; int l, r;
		cin >> type >> l >> r;
		if(type == 'M'){
			cout << S.query(l - 1, r)[1] << '\n';
		}
		if(type == 'P'){
			int val;
			cin >> val;
			S.update(val, l - 1, r);
		}
		if(type == 'S'){
			cout << S.query(l - 1, r)[0] << '\n'; 
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

	#ifndef LOCAL
		freopen("haybales.in", "r", stdin);
		freopen("haybales.out", "w", stdout);
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