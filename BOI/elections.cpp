#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 1e9; 
 
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n; 
 
	int seats = 0; 
 
	vector<pair<int, int>> a(n+1);
	for(int i = 1; i <= n; i++){
		cin >> a[i].first;
		seats += a[i].first;
		a[i].second = i;
	}
	a[0] = {INF, 0};
	sort(a.rbegin(), a.rend());
 
	vector<int> dp(seats+1, -1);
	dp[0] = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int s = seats/2; s >= 0; --s)
			if(dp[s] != -1){
				if(dp[s+a[i].first] == -1) dp[s+a[i].first] = i;
				ans = max(ans, s+a[i].first);
			}
	}
 
	vector<int> t;
	while(dp[ans] > 0){
		t.push_back(a[dp[ans]].second);
		ans -= a[dp[ans]].first;
	}
 
	cout << t.size() << '\n';
	for(int i : t)
		cout << i << ' ';
 
	return 0; 
}