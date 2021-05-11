#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e16;

/*struct SparseTable{
	vector<vector<int64_t>> table;
	vector<int> log;

	SparseTable(vector<int64_t>& a, int n){
		log.resize(n+1);
		log[0] = 0;
		log[1] = 0;
		int lg = 18;
		table.resize(lg, vector<int64_t>(n+1));

		for(int i = 2; i <= n; i++)
			log[i] = log[i>>1] + 1;

		for(int i = 1; i <= n; i++)
			table[0][i] = a[i];

		for(int i = 2; i < lg; i++)
			for(int j = 1; j + (1 << i) <= n+1; j++)
				table[i][j] = min(table[i-1][j], table[i-1][j + (1 << (i-1))]);
	}

	int64_t query(int L, int R){
		int j = log[R-L+1];
		return min(table[j][L], table[j][R - (1 << j) + 1]);
	}
};*/

struct SegmentTree{
	vector<int64_t> tree;
	int sz = 1; 
	SegmentTree(vector<int64_t>& a, int n){
		while(sz < n)
			sz <<= 1;
		tree.resize(2*sz, INF);
		build(a, 0, 0, sz);
	}

	void build(vector<int64_t>& a, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < a.size())
				tree[x] = a[lx];
			return;
		}

		int mid = (lx + rx) >> 1;
		build(a, 2*x+1, lx, mid);
		build(a, 2*x+2, mid, rx);

		tree[x] = min(tree[2*x+1], tree[2*x+2]);
	}

	int64_t query(int l, int r, int x, int lx, int rx){
		if(rx <= l || lx >= r)
			return INF;
		if(l <= lx && rx <= r)
			return tree[x];

		int mid = (lx + rx) >> 1;
		return min(query(l, r, 2*x+1, lx, mid), query(l, r, 2*x+2, mid, rx));
	}

	int64_t query(int l, int r){
		return query(l, r, 0, 0, sz);
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m;

	vector<int> a(n+1);
	for(int i = 1; i <= n; i++)
		cin >> a[i];

	vector<int64_t> pref(n+1);

	for(int i = 1; i <= n; i++)
		pref[i] = pref[i-1] + int64_t(a[i]);

	//binary search with log^2??
	//lo = i, hi = 
	//check that in [mid, n], the min prefix sum is <= pref[i] + M
	// if satisfies, then the endpoint must lie in [mid, n] -> otherwise the endpoint lies in [i, mid-1]
	// 101 42 -132 17 404 -13 55 222 89 11 -66 91 -9 21 4
	// 101 143 11 28 432 419 474 696 785 796 730 821 812 833 837
	// 1, 15
	// 8
	// since the array starts from i, pref[i-1] + M

	SegmentTree S(pref, n+1);

	pair<int, int> ans = {INT_MIN, INT_MIN};

	for(int i = 1; i <= n; i++){
		// the subarray taken into consideration is [i, j]
		// find the maximal index j such that pref[j] <= pref[i-1] + m
		
		int lo = i, hi = n, xx = 0;
		while(lo <= hi){
			int mid = (lo + hi) >> 1;
			if(S.query(mid, n+1) <= pref[i-1] + m){
				xx = mid;
				lo = mid + 1;
			}
			else hi = mid-1;
		}
		ans = max(ans, {xx - i + 1, -i});
	}

	cout << ans.first << ' ' << -ans.second << '\n';
	return 0; 
}