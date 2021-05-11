#include <bits/stdc++.h>

using namespace std;
const int MXN = 20; 
const int MX = 1000; 
vector<int> pos[MXN*MX+1];
vector<vector<int>> dp(MXN, vector<int>(1 << MXN, -1));
int n, m;
vector<int> a;
bool solve(int idx, int mask){
	if(idx == n) return 1; 
	if(dp[idx][mask] != -1){
		return dp[idx][mask];
	} 
	bool ans = 0; 
	for(int nmask : pos[a[idx]]){
		if((nmask & mask) == 0)
			ans = ans | solve(idx+1, mask|nmask);
	}

	return dp[idx][mask] = ans;
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	//dp[i][mask] -> is it possible to cover all employees till i using mask notes

	cin >> n >> m; 
	a.resize(n);

	for(int i = 0; i < n; i++)
		cin >> a[i];

	vector<int> b(m); 
	for(int i = 0; i < m; i++)
		cin >> b[i];

	for(int mask = 0; mask < (1 << m); mask++){
		int sum = 0; 
		for(int i = 0; i < m; i++)
			if(mask & (1 << i))
				sum += b[i];

		pos[sum].push_back(mask);
	}

	cout << (solve(0, 0) ? "YES" : "NO") << '\n';
	return 0; 
}