#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	vector<int> weight(n);
	int rt = INF;
	for(int i = 0; i < n; i++){
		cin >> weight[i];
		rt = min(rt, weight[i]);
	}

	vector<int> start(n), to(n);
	vector<int> g(n);

	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		--x;
		start[x] = i;
	}

	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		--x;
		to[i] = x;
		g[start[x]] = i;
	}

	vector<int> vis(n, 0);
	vector<vector<int>> cycle;
	for(int i = 0; i < n; i++){
		if(vis[i]) continue;
		vector<int> temp;
		int s = i;
		while(vis[s] == 0){
			vis[s] = 1;
			temp.push_back(s);
			s = g[s];
		}

		cycle.push_back(temp);
	}
	
	int64_t ans = 0;

	for(vector<int> v : cycle){
		int mn = INF;
		int64_t temp = 0;
		for(int x : v){
			temp += weight[to[x]];
			mn = min(mn, weight[to[x]]);
		}
		int r = v.size() - 2;
		ans += min(temp + r*1LL*mn, rt + mn + temp + rt + (r+1)*1LL*rt);
	}

	cout << ans << '\n';
	return 0; 
}