#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	vector<int64_t> left, right, both, none;
	int sz = 1;
	SegmentTree(int n){
		while(sz < n)
			sz <<= 1;
		left.resize(2*sz);
		right.resize(2*sz);
		both.resize(2*sz);
		none.resize(2*sz);
	}

	void merge(int node){
		int lc = 2*node+1, rc = 2*node+2;
		left[node] = max(both[lc] + none[rc], left[lc] + left[rc]);
		right[node] = max(none[lc] + both[rc], right[lc] + right[rc]);
		both[node] = max(left[lc] + both[rc], both[lc] + right[rc]);
		none[node] = max(none[lc] + left[rc], right[lc] + none[rc]);
	}

	void update(int idx, int val, int x, int l, int r){
		if(r - l == 1){
			both[x] = val;
			return;
		}
		int mid = (l + r) >> 1;
		if(idx < mid) update(idx, val, 2*x+1, l, mid);
		else update(idx, val, 2*x+2, mid, r);
		merge(x);
	}

	void update(int idx, int val){
		update(idx, val, 0, 0, sz);
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	#ifndef LOCAL
	freopen("optmilk.in", "r", stdin);
	freopen("optmilk.out", "w", stdout);
	#endif

	int N, D;
	cin >> N >> D;

	SegmentTree S(N);


	for(int i = 0; i < N; i++){
		int val;
		cin >> val;
		S.update(i, val);
	}

	int64_t ans = 0;
	for(int i = 0; i < D; i++){
		int idx, val;
		cin >> idx >> val;
		--idx;
		S.update(idx, val);
		ans += S.both[0];
	}

	cout << ans << '\n';
	return 0; 
}