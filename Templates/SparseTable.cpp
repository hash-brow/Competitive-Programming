const int MXN = 100000;
const int MXK = 20;

struct SparseTable{
	int st[MXK][MXK];
	int log[MXN];

	function<T(const T&,const T&)> merge;

	SparseTable(int N, const vector<int>& a, const function<T(const T&, const T&)>& _merge){
		merge = _merge;

		log[0] = log[1] = 0;
		for(int i = 2; i <= N; i++)
			log[i] = log[i>>1] + 1;

		for(int i = 0; i < N; i++)
			st[0][i] = a[i];

		for(int j = 1; j < MXK; j++){
			for(int i = 0; i + (1 << j) <= N; i++)
				st[j][i] = merge(st[j-1][i], st[j-1][i + (1 << (j-1))]);
		}
	}

	int query(int L, int R){
		int j = log[R - L + 1];
		return merge(st[j][L], st[j][R - (1 << j) + 1]);
	}
};