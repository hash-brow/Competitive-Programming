#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int k, n;
	cin >> k >> n; 

	vector<int> a(n); 

	for(int i = 0; i < n-1; i++)
		a[i] = i+1; 

	a[n-1] = k - (n*(n-1))/2; 

	for(int i = 0; i < n; i++)
		cout << a[i] << '\n';	
	return 0; 
}