#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	vector<int> a(n);

	for(int i = 0; i < n; i++)
		cin >> a[i];

	int64_t ans = 0;
	for(int i = 0; i < n - 1; i++)
		ans += int64_t(max(a[i], a[i+1]));

	cout << ans << '\n';
	
	return 0; 
}