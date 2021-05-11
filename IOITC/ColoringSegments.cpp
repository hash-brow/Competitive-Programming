#include <bits/stdc++.h>

using namespace std;

struct dsu{
	vector<int> e;
	dsu(int n){
		e.resize(n, -1);
	}
	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x]));
	}
	bool unite(int x, int y){
		x = get(x), y = get(y);
		if(x == y)
			return 0;
		if(e[x] > e[y])
			swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return 1;
	}
};

void solve(){
	int n, m;
	cin >> n >> m;

	dsu d(n+m);

	vector<int> horizontal(n+1), vertical(m+1);
	for(int i = 1; i <= n; i++){
		cin >> horizontal[i];
	}
	
	for(int i = 1; i <= m; i++){
		cin >> vertical[i];
		for(int j = 1; j <= vertical[i] && j <= n; j++)
			if(horizontal[j] >= i)
				d.unite(j-1, i-1+n);
	}

	int ans = 0;
	for(int i = 0; i < n+m; i++)
		if(d.get(i) == i) ans++;

	cout << ans << '\n';
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
		
	int t;
	cin >> t;
	while(t--){
		solve();
	}	

	return 0; 
}