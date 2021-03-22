#include <bits/stdc++.h>

using namespace std;

void wssert(bool x){
	if(!x){
		cout << "rte\n";
	}
}

struct SegmentTree{
	struct Node{
		int mx, mn;
	};

	vector<Node> tree;
	vector<bool> lazy;
	int sz = 1, N;

	SegmentTree(int n){
		N = n;
		while(sz < n)
			sz <<= 1;
		tree.resize(2*sz, {1000000, 0});
		lazy.resize(2*sz, false);
	}

	Node merge(Node x, Node c){
		if(x.mn >= c.mx) return {x.mn, x.mn};
		if(x.mx <= c.mn) return {x.mx, x.mx};
		return {min(x.mx, c.mx), max(x.mn, c.mn)};
	}

	inline int lc(int x) { return 2*x+1; }
	inline int rc(int x) { return 2*x+2; }

	void push(int x){
		lazy[x] = false;
		wssert(lc(x) < 2*sz);
		wssert(rc(x) < 2*sz);
		lazy[lc(x)] = lazy[rc(x)] = true;
		tree[lc(x)] = merge(tree[x], tree[lc(x)]);
		tree[rc(x)] = merge(tree[x], tree[rc(x)]);
		tree[x] = {1000000, 0};
	}

	void update(int l, int r, int t, int val, int x, int lx, int rx){
		if(rx <= l || lx >= r)
			return;

		if(lx >= l && rx <= r){
			lazy[x] = true;
			if(t == 0) tree[x] = {max(tree[x].mx, val), max(tree[x].mn, val)};
			else tree[x] = {min(tree[x].mx, val), min(tree[x].mn, val)};
			return;
		}

		if(lazy[x]) 
			push(x);

		int mid = (lx + rx) >> 1;
		
		update(l, r, t, val, lc(x), lx, mid);
		update(l, r, t, val, rc(x), mid, rx);
	}

	void construct(int x, int lx, int rx, int ans[]){
		if(rx - lx == 1){
			if(lx < N) ans[lx] = tree[x].mn;
			return;
		}

		int mid = (lx + rx) >> 1;
		
		if(lazy[x])
			push(x);

		wssert(lc(x) < 2*sz);
		wssert(rc(x) < 2*sz);
		
		construct(lc(x), lx, mid, ans);
		construct(rc(x), mid, rx, ans);
	}

	void update(int l, int r, int t, int val) { update(l, r, t, val, 0, 0, sz); }
	void construct(int ans[]){ construct(0, 0, sz, ans); }
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	SegmentTree S(n);
	for(int i = 0; i < k; i++)
		S.update(left[i], right[i] + 1, op[i] - 1, height[i]);
	S.construct(finalHeight);
}

/*int main(){
	int n, k;
	cin >> n >> k;
	int op[k], left[k], right[k], height[k], finalHeight[n];

	for(int i = 0; i < k; i++)
		cin >> op[i] >> left[i] >> right[i] >> height[i];

	buildWall(n, k, op, left, right, height, finalHeight);
	for(int i = 0; i < n; i++)
		cout << finalHeight[i] << ' ';
}*/