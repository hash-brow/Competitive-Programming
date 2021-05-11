#include <bits/stdc++.h>

using namespace std;

struct BIT{
	vector<int> tree;
	int N;
	void init(int _n){
		N = _n;
		tree.resize(N+1);
	}
	void upd(int pos, int val){
		for(++pos; pos <= N; pos += (pos & (-pos)))
			tree[pos] += val;
	}
	int que(int idx){
		int sum = 0;
		for(idx++; idx > 0; idx -= (idx & (-idx)))
			sum += tree[idx];
		return sum;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;

	vector<array<int, 4>> marks(n), query(q);
	vector<int> ds(n+q), dt(n+q);
	vector<BIT> ft(2);

	for(int i = 0; i < n; i++){
		auto& [tot, s, t, idx] = marks[i];
		cin >> s >> t;
		tot = s + t;
		idx = i;
		ds[i] = s;
		dt[i] = t;
	}
	for(int i = 0; i < q; i++){
		auto& [tot, s, t, idx] = query[i];
		cin >> s >> t >> tot;
		tot = max(tot, s + t);
		idx = i;
		ds[i+n] = s;
		dt[i+n] = t;
	}

	sort(ds.begin(), ds.end());
	ds.erase(unique(ds.begin(), ds.end()), ds.end());
	sort(dt.begin(), dt.end());
	dt.erase(unique(dt.begin(), dt.end()), dt.end());

	ft[0].init(ds.size());
	ft[1].init(dt.size());

	for(auto& [tot, s, t, idx] : marks){
		s = lower_bound(ds.begin(), ds.end(), s) - ds.begin();
		t = lower_bound(dt.begin(), dt.end(), t) - dt.begin();
		assert(s < (n+q) && t < (n+q));
	}

	for(auto& [tot, s, t, idx] : query){
		s = lower_bound(ds.begin(), ds.end(), s) - ds.begin();
		t = lower_bound(dt.begin(), dt.end(), t) - dt.begin();
		assert(s < (n+q) && t < (n+q));
	}

	sort(marks.rbegin(), marks.rend());
	sort(query.rbegin(), query.rend());

	vector<int> ans(q);

	int idx = 0;
	for(int i = 0; i < q; i++){
		while(idx < n && marks[idx][0] >= query[i][0]){
			ft[0].upd(marks[idx][1], 1);
			ft[1].upd(marks[idx][2], 1);
			idx++;
		}
		ans[query[i][3]] = idx - ft[0].que(query[i][1]-1) - ft[1].que(query[i][2]-1);
	}

	for(int i = 0; i < q; i++)
		cout << ans[i] << '\n';
	return 0; 
}