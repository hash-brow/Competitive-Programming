#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
		
	map<int, int> x, y;
	int n;
	cin >> n;

	vector<array<int, 2>> a(n);
	for(auto& [i, j] : a){
		cin >> i >> j;
		x[i]++;
		y[j]++;
	}

	int64_t ans = 0;

	for(int i = 0; i < n; i++)
		ans += (x[a[i][0]] - 1) * 1LL * (y[a[i][1]] - 1);

	cout << ans << '\n';
	return 0;
}