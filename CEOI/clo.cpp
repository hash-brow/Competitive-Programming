#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n; 

	vector<array<int, 4>> o; 

	for(int i = 0; i < n; i++){
		int c, f, v;
		cin >> c >> f >> v;
		o.push_back({f, c, v, 0}); 
	}
	
	int m;
	cin >> m; 

	for(int i = 0; i < m; i++){
		int c, f, v;
		cin >> c >> f >> v;
		o.push_back({f, c, v, 1}); 
	}

	sort(o.begin(), o.end(), [](array<int, 4> a, array<int, 4> b){
		if(a[0] == b[0]){
			if(a[3] < b[3])
				return true; 
		}
		if(a[0] > b[0])
			return true; 
		return false;
	}); 

	vector<int64_t> dp(100001, -1e18);
	dp[0] = 0; 
	for(auto& [f, c, v, w] : o){
		if(w == 0){
			for(int i = 100000 - c; i >= 0; --i)
				dp[i+c] = max(dp[i+c], dp[i] - int64_t(v));
		}	
		else{
			for(int i = c; i < 100001; i++)
				dp[i-c] = max(dp[i-c], dp[i] + int64_t(v));
		}
	}

	int64_t ans = 0; 

	for(int i = 0; i < 100001; i++)
		ans = max(ans, dp[i]);

	cout << ans << '\n';
	return 0; 
}