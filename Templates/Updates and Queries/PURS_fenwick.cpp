/*
Point update range sum fenwick tree
1 indexed BIT
1 indexed array

Works in O(logn) time

Can only be used for reversible functions

Alternatively, can be used to find prefix values of certain non reversible functions
*/

struct BIT{
	vector<int> tree;
	BIT(int n){
		tree.resize(n+1);
	}
	void upd(int pos, int val){
		for(; pos <= n; pos += (pos&(-pos)))
			tree[pos] += val;
	}
	int query(int pos){
		int sum = 0;
		for(; pos > 0; pos -= (pos&(-pos)))
			sum += tree[pos];
		return sum;
	}
	// returns the sum from [l, r]
	int query(int l, int r){
		return query(r+1) - query(l);
	}
};