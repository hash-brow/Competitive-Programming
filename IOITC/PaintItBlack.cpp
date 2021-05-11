#include <bits/stdc++.h>

using namespace std;

int K;
int ll, rr, uu, dd;
inline int get(int l, int r, int u, int d){
	return l*rr*uu*dd + r*uu*dd + u*dd + d;
}

struct Rect{
	int x1, x2, y1, y2;
	Rect(int _x1, int _x2, int _y1, int _y2) : x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
};

vector<Rect> V;

struct SegmentTree{
	vector<int> tree, lazy;
	int sz;

	SegmentTree(int n){
		sz = 1;
		while(sz < n)
			sz <<= 1;
		tree.resize(2*sz);
		lazy.resize(2*sz);
	}

	void pull(int x, int l, int r){
		if(lazy[x]) tree[x] = r - l;
		else tree[x] = (l + 1 == r ? 0 : tree[2*x+1] + tree[2*x+2]);
	}

	void update(int ql, int qr, int val, int x, int l, int r){
		if(ql >= l && qr <= r){
			lazy[x] += v;
			return;
		}

		int mid = (l + r) >> 1;
		if(qr <= mid) update(ql, qr, val, 2*x+1, l, mid);
		else if(mid <= ql) update(ql, qr, val, 2*x+2, mid, r);
		else{
			update(ql, qr, val, 2*x+1, l, mid);
			update(ql, qr, val, 2*x+2, mid, r);
		}
	}

	void update(int ql, int qr, int val) { update(ql, qr, val, 0, 0, sz); }

	void query(){
		return tree[0];
	}
};

struct Seg{
	int l, r, y, v;

	bool operator<(const Seg& rhs) const {
		return y < rhs.y;
	}
};

inline bool check(array<int, 4> idx){
	// for every rectangle, everything must be 1
	// every 1 must be covered in the union of the rectangles...
	
	vector<Seg> s;
	SegmentTree T(4);
	for(int i = 0; i < 4; i++){
		s.push_back(V[idx[i]].l+1, V[idx[i]].r, V[idx[i]].u+1, -1);
		s.push_back(V[idx[i]].l+1, V[idx[i]].r, V[idx[i]].d, 1);
	}

	sort(s.begin(), s.end());

	int ans = 0, preY = 0;
	for(auto [ql, qr, y, val] : s){
		ans += T.query() * (y - preY);
		T.update(ql, qr, val);
		preY = y;
	}

	return (ans == num);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, M;
	cin >> N >> M >> K;

	int grid[N+2][M+2];

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> grid[i][j];

	vector<int> L, R, U, D;

	// L -> j such that grid[i][j] = 0, grid[i][j+1] = 1
	// R -> j such that grid[i][j] = 1, grid[i][j+1] = 0
	// U -> i such that grid[i][j] = 0, grid[i+1][j] = 1
	// D -> i such that grid[i][j] = 1, grid[i+1][j] = 0

	for(int i = 1; i <= N; i++)
		for(int j = 0; j < M; j++){
			if(grid[i][j] == 0 && grid[i][j+1] == 1)
				L.push_back(j);
			if(grid[i][j] == 1 && grid[i][j+1] == 0)
				R.push_back(j);
		}

	for(int i = 0; i < N; i++)
		for(int j = 1; j <= M; j++){
			if(grid[i][j] == 0 && grid[i+1][j] == 1)
				U.push_back(i);
			if(grid[i][j] == 1 && grid[i+1][j] == 0)
				D.push_back(i);
		}

	sort(L.begin(), L.end()); L.erase(unique(L.begin(), L.end()), L.end());
	sort(R.begin(), R.end()); R.erase(unique(R.begin(), R.end()), R.end());
	sort(D.begin(), D.end()); D.erase(unique(D.begin(), D.end()), D.end());
	sort(U.begin(), U.end()); U.erase(unique(U.begin(), U.end()), U.end());
	
	ll = L.size();
	rr = R.size();
	uu = U.size();
	dd = D.size();
	
	if(ll > K || rr > K || uu > K || dd > K){
		cout << "No\n";
		return 0;
	}

	// assign lines to all K rectangles... check if they cover all.
	// if the rectangle has lines i, j : it covers (i, j]

	int sz = ll*rr*uu*dd;
	V.resize(sz);

	for(int l = 0; l < ll; l++)
	for(int r = 0; r < rr; r++)
	for(int u = 0; u < rr; u++)
	for(int d = 0; d < dd; d++)
		V[get(l, r, u, d)] = {L[l], R[r], U[u], D[d]};

	for(int i = 0; i < sz; i++)
	for(int j = i+1; j < sz; j++)
	for(int k = j+1; k < sz; k++)
	for(int l = k+1; l < sz; l++)
		if(check({i, j, k, l})){
			cout << "Yes\n";
			return 0;
		}

	cout << "No\n";
	return 0; 
}