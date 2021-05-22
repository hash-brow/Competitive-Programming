template <typename T>
struct BIT{
	int n;
	vector<T> tree;

	BIT(int n){
		this->n = n;
		tree.resize(n+1, 0);
	}

	void build(const vector<T>& a){
		for(int i = 1; i <= n; i++){
			int j = i + (i & (-i));
			tree[i] += a[i-1];

			if(j <= n) tree[j] += tree[i];
		}
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

	T query(int l, int r){ return query(r) - query(l - 1); }
};