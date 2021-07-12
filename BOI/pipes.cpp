#include <bits/stdc++.h>

using namespace std;

const int MXN = 100000;

set<array<int, 2>> g[MXN];
int change[MXN], suf[MXN];
bitset<MXN> vis;
int a[MXN], b[MXN], ans[MXN + 1];

void solve(){
	int N, M;
	cin >> N >> M;

	for(int i = 0; i < N; i++)
		cin >> change[i];

	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].insert({v, i});
		g[v].insert({u, i});
	}

	if(M > N){
		cout << 0 << '\n';
		return;
	}

	queue<array<int, 3>> q;
	for(int i = 0; i < N; i++)
		if(g[i].size() < 2){
			q.push({i, (*g[i].begin())[0], (*g[i].begin())[1]});
			vis[i] = 1;
		}

	int cnt = 0;

	while(!q.empty()){
		auto [u, par, idx] = q.front();
		q.pop();

		++cnt;

		int t = change[u];
		ans[idx] += 2*t;
		change[u] -= t;
		change[par] -= t;

		g[par].erase({u, idx});

		if(g[par].size() < 2 && !vis[par]){
			q.push({par, (*g[par].begin())[0], (*g[par].begin())[1]});
			vis[par] = 1;
		}
	}

	if(cnt < N){
		if(!((N - cnt) & 1)){
			cout << 0 << '\n';
			return;
		}

		int x;
		for(int i = 0; i < N; i++) 
			if(!vis[i]) 
				x = i;

		int u = x;
		N = 0;

		while(u != x || N == 0){
			auto [v, idx] = (N == 0 || (*g[u].begin())[0] != a[N-1] ? *g[u].begin() : *g[u].rbegin());
			a[N] = u;
			b[N++] = idx;
			u = v;
		}

		suf[N-1] = change[a[N-1]];
		for(int i = N - 2; i >= 0; --i)
			suf[i] = change[a[i]] - suf[i+1];
		int pre = 0;

		for(int i = 0; i < N; i++){
			pre = change[a[i]] - pre;
			ans[b[i]] = (pre + (i + 1 < N ? suf[i+1] : 0));
		}
	}

	for(int i = 0; i < M; i++)
		cout << ans[i] << '\n';
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	solve();

	return 0; 
}