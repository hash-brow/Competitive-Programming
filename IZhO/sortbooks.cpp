#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	vector<int64_t> tree;
	int sz = 1;

	SegmentTree(int n){
		while(sz < n)
			sz <<= 1;
		tree.resize(2*sz);
	}

	void upd(int idx, int64_t val, int x, int lx, int rx){
		if(rx - lx == 1){
			tree[x] = max(tree[x], val);
			return;
		}

		int mid = (lx + rx) >> 1;
		if(idx < mid) upd(idx, val, 2*x+1, lx, mid);
		else upd(idx, val, 2*x+2, mid, rx);

		tree[x] = max(tree[2*x+1], tree[2*x+2]);
	}

	int64_t query(int l, int r, int x, int lx, int rx){
		if(rx <= l || lx >= r)
			return 0LL;
		if(l <= lx && r >= rx)
			return tree[x];

		int mid = (lx + rx) >> 1;
		return max(query(l, r, 2*x+1, lx, mid), query(l, r, 2*x+2, mid, rx));
	}

	void upd(int idx, int val) { upd(idx, val, 0, 0, sz); }

	int64_t query(int l, int r) { return query(l, r, 0, 0, sz); } 
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m;

	vector<int64_t> W(n);
	for(int i = 0; i < n; i++)
		cin >> W[i];

	vector<array<int64_t, 4>> query(m);
	for(int i = 0; i < m; i++){
		auto& [l, r, k, idx] = query[i];
		cin >> l >> r >> k;
		idx = i;
		--l, --r;
	}

	sort(query.begin(), query.end(), [](const array<int64_t, 4>& a, const array<int64_t, 4>& b){
		if(a[1] == b[1])
			return a[0] < b[0];

		return a[1] < b[1];
	});

	vector<int> st;
	SegmentTree S(n);
	vector<bool> ans(m);

	int i = 0;
	for(auto& [l, r, k, idx] : query){
		while(i <= r){
			while(!st.empty() && W[st.back()] <= W[i])
				st.pop_back();
			if(!st.empty())
				S.upd(st.back(), W[i] + W[st.back()]);
			st.push_back(i);
			i++;
		}

		ans[idx] = (S.query(l, r+1) <= k);
	}

	for(auto k : ans)
		cout << k << '\n';
	return 0;
}