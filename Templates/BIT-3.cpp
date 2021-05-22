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
};

template<typename T>
struct Range{
	BIT<T> B[2];
	int n;

	Range(int n){
		this->n = n;
		for(int i = 0; i < 2; i++)
			B[i].init(n);
	}

	void increment(int l, int r, T val){
		B[0].increment(r + 1, -val);
		B[0].increment(l, val);
		B[1].increment(l, val*(l-1));
		B[1].increment(r, -val*r);
	}

	T query(int l){
		return B[0].query(l)*l - B[1].query(l);
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};