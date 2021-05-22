struct SegmentTree{
	vector<int> st;
	int sz;
 	
 	function<T&(const T&, const T&)> merge;

	SegmentTree(int n, const function<T&(const T&, const T&)> _merge){
		merge = _merge;

		sz = 1;
		while(sz < n)
			sz <<= 1;
		st.resize(2*sz);
	}
 
	void build(const vector<int>& a, int x, int l, int r){
		if(r - l == 1){
			if(l < a.size())
				st[x] = a[l];
			return;
		}
 
		int mid = (l + r) >> 1;
 
		build(a, 2*x+1, l, mid);
		build(a, 2*x+2, mid, r);
		st[x] = merge(st[2*x+1], st[2*x+2]);
	}
 
	void update(int val, int idx, int x, int l, int r){
		if(r - l == 1){

			return;
		}
 
		int mid = (l + r) >> 1;
		if(idx < mid) update(val, idx, 2*x+1, l, mid);
		else update(val, idx, 2*x+2, mid, r);
 
		st[x] = merge(st[2*x+1], st[2*x+2]);
	}
 
	int query(int val, int x, int lx, int rx){
		if(rx - lx == 1)
			return;
 
		int mid = (lx + rx) >> 1;
	

	}
 
	void build(const vector<int>& a){ build(a, 0, 0, sz); }
 
	void update(int val, int idx) { update(val, idx, 0, 0, sz); }
 
	int query(int val){
		if(st[0] < val) return -1;
		int t = query(val, 0, 0, sz);
		update(val, t);
		return t;
	}
};