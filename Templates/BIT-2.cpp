template <typename T>
struct BIT{
	int n;
	vector<T> tree;

	BIT(int n){
		this->n = n;
		tree.resize(n+1, 0);
	}
	
	void increment(int idx, T val){
		for(int i = idx + 1; i <= n; i += (i & (-i)))
			tree[i] += val;
	}

	T query(int idx){
		T sum = 0;
		for(int i = idx + 1; i > 0; i -= (i & (-i)))
			sum += tree[i];
		return sum;
	}

	void increment(int l, int r, T val){
		increment(l, val);
		increment(r+1, -val);
	}
};