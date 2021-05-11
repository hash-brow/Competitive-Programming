#include <bits/stdc++.h>

using namespace std;


int Ask(int64_t num){
	cout << "? " << num << endl;
	int x;
	cin >> x;
	return x; 
}

void solve(){
	int64_t n;
	cin >> n;

	int64_t l = 1, r = n-1, start = n, cur = 0, dir = 1;

	while(l <= r){
		int64_t mid = (l + r) / 2;
		cur += dir*mid;
		dir *= -1;
		start = min(start, n - cur);
		l = mid + 1;
	}

	l = 1, r = n-1, dir = 1;

	int64_t answer = n;	

	Ask(start);

	while(l <= r){
		int64_t mid = (l + r) / 2;
		start += dir*mid;
		dir *= -1;
		if(Ask(start)){
			answer = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	
	cout << "= " << answer << endl;	
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