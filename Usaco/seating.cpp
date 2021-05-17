#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	vector<array<int, 3>> st;
	vector<int> lazy;
	int sz = 1;

	SegmentTree(int n){
		while(sz < n)
			sz <<= 1;
		st.resize(2*sz);
		lazy.resize(2*sz, -1);

		build(n, 0, 0, sz);
	}

	void merge(int x, int l, int r, int mid){
		int lc = 2*x + 1, rc = 2*x + 2;
		st[x][0] = max({st[lc][0], st[rc][0], st[lc][2] + st[rc][1]});
		st[x][1] = (st[lc][0] == (mid - l) ? st[lc][0] + st[rc][1] : st[lc][1]);
		st[x][2] = (st[rc][0] == (r - mid) ? st[rc][0] + st[lc][2] : st[rc][2]);
	}

	void mod(int x, int v, int l, int r){
		st[x] = {v*(r - l), v*(r-l), v*(r-l)};
		lazy[x] = v;
	}

	void push(int x, int l, int r){
		if(r - l == 1)
			return;

		if(lazy[x] != -1){
			int mid = (l + r) >> 1;
			mod(2*x+1, lazy[x], l, mid);
			mod(2*x+2, lazy[x], mid, r);
		}

		lazy[x] = -1;
	}

	void build(int n, int x, int l, int r){
		if(r - l == 1){
			if(l < n) st[x][0] = st[x][1] = st[x][2] = 1;
			return;
		}

		int mid = (l + r) >> 1;
		build(n, 2*x+1, l, mid);
		build(n, 2*x+2, mid, r);

		merge(x, l, r, mid);
	}

	void update(int l, int r, int type, int x, int lx, int rx){
		if(r <= lx || l >= rx)
			return;

		if(lx >= l && rx <= r) return mod(x, type, lx, rx);

		push(x, lx, rx);

		int mid = (lx + rx) >> 1;
		update(l, r, type, 2*x+1, lx, mid);
		update(l, r, type, 2*x+2, mid, rx);

		merge(x, lx, rx, mid);
	}

	void query(int val, int x, int l, int r){
		if(r - l <= val) mod(x, 0, l, r);
		push(x, l, r);

		int mid = (l + r) >> 1;

		if(st[2*x+1][0] >= val){
			query(val, 2*x+1, l, mid);
		}
		else if(st[2*x+1][2] + st[2*x+2][1] >= val){
			update(mid - st[2*x+1][2], mid - st[2*x+1][2] + val, 0);
		}
		else if(st[2*x+2][0] >= val) query(val, 2*x+2, mid, r);

		merge(x, l, r, mid);
	}

	void update(int l, int r, int type) { update(l, r, type, 0, 0, sz); }

	void query(int val) { query(val, 0, 0, sz); }
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	#ifndef LOCAL
		freopen("seating.in", "r", stdin);
		freopen("seating.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	SegmentTree S(n);

	int ans = 0;

	for(int i = 0; i < m; i++){
		char type;
		cin >> type;
		if(type == 'A'){
			int x;
			cin >> x;
			if(S.st[0][0] < x) ans++;
			else S.query(x);
		}
		else{
			int a, b;
			cin >> a >> b;
			S.update(a-1, b, 1);
		}
	}

	cout << ans << '\n';
	return 0; 
}