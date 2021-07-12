#include <bits/stdc++.h>

using namespace std;

vector<int> req;
vector<vector<int>> land;
vector<array<int, 3>> D;
vector<int> ans;

int n, m;

struct BIT{
	vector<int64_t> tree;
	int n;

	void init(int _n){
		n = _n;
		tree.resize(n+1);
	}

	void upd(int idx, int64_t val){
		for(; idx <= n; idx += (idx&(-idx)))
			tree[idx] += val;
	}

	void upd(int l, int r, int64_t val){
		upd(l, val);
		upd(r+1, -val);
	}

	int64_t query(int idx){
		int64_t sum = 0;
		for(; idx > 0; idx -= (idx&(-idx)))
			sum += tree[idx];
		return sum;
	}

}bit;

void PBS(int l, int r, vector<int> active){
	if(active.size() == 0)
		return;

	if(r - l == 1){
		for(int i : active)
			ans[i] = l;
		return;
	}

	int mid = (l+r) >> 1;
	
	for(int i = l; i < mid; i++){
		if(D[i][0] <= D[i][1]) bit.upd(D[i][0], D[i][1], (int64_t)D[i][2]);
		else{
			bit.upd(D[i][0], m, int64_t(D[i][2]));
			bit.upd(1, D[i][1], int64_t(D[i][2]));
		}
	}
	
	vector<int> nq[2];
	
	for(int i : active){
		uint64_t sum = 0;
		for(int v : land[i]) sum += uint64_t(bit.query(v));
		if(sum >= req[i]) nq[0].push_back(i);
		else{
			req[i] -= sum;
			nq[1].push_back(i);
		}
	}

	for(int i = l; i < mid; i++){
		if(D[i][0] <= D[i][1]) bit.upd(D[i][0], D[i][1], int64_t(-D[i][2]));
		else{
			bit.upd(D[i][0], m, int64_t(-D[i][2]));
			bit.upd(1, D[i][1], int64_t(-D[i][2]));
		}
	}

	PBS(l, mid, nq[0]);
	PBS(mid, r, nq[1]);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	cin >> n >> m;
	land.resize(n+1), req.resize(n+1);
	ans.resize(n+1);

	bit.init(m);

	for(int i = 1; i <= m; i++){
		int x;
		cin >> x;
		land[x].push_back(i);
	}

	for(int i = 1; i <= n; i++)
		cin >> req[i];

	int k;
	cin >> k;

	D.resize(k+1);
	for(int i = 1; i <= k; i++){
		auto& [l, r, upd] = D[i];
		cin >> l >> r >> upd;
	}

	vector<int> cur(n);
	iota(cur.begin(), cur.end(), 1);
	PBS(1, k+2, cur);

	for(int i = 1; i <= n; i++)
		if(ans[i] == k+1) cout << "NIE\n";
		else cout << ans[i] << '\n';

	return 0; 
}
