#include <bits/stdc++.h>

using namespace std;

struct dsu{
	vector<int64_t> e;
	vector<bool> active;
	int64_t ans;
	dsu(int n){
		e.resize(n, -1);
		ans = 0;
		active.resize(n, 0);
	}

	int64_t get(int64_t x){
		return (e[x] < 0 ? x : e[x] = get(e[x]));
	}

	int64_t f(int x){
		int64_t t = -e[get(x)];
		return (t*(t+1)) / 2;
	}

	bool unite(int x, int y){
		x = get(x), y = get(y);
		if(!active[x]){
			ans += f(x);
			active[x] = 1;
		}
		if(!active[y] || x == y)
			return 0;

		if(e[x] > e[y])
			swap(x, y);
		
		ans -= f(x) + f(y);
		e[x] += e[y];
		e[y] = x;
		ans += f(x);
		return 1;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;

	vector<array<int, 2>> h(n), query(q);
	for(int i = 0; i < n; i++){
		cin >> h[i][0];
		h[i][1] = i;
	}
	for(int i = 0; i < q; i++){
		cin >> query[i][0];
		query[i][1] = i;
	}

	sort(h.begin(), h.end());
	sort(query.begin(), query.end());

	vector<int64_t> ans(q);

	dsu d(n);

	int cur = 0;
	for(int i = 0; i < q; i++){
		while(cur < n && query[i][0] >= h[cur][0]){
			int idx = h[cur][1];
			int nxt = idx + 1;
			int pre = idx - 1;
			if(nxt < n) d.unite(idx, nxt);
			if(pre >= 0) d.unite(idx, pre);
			cur++;
		}
		ans[query[i][1]] = d.ans;
	}

	for(int i = 0; i < q; i++)
		cout << ans[i] << ' ';

	return 0; 
}