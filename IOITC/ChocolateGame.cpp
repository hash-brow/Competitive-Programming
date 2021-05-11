#include <bits/stdc++.h>

using namespace std;

const int MXN = 10000001;
const int INF = 1000000000;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int M, Q;
	cin >> M >> Q;

	vector<int> P(M), LP(MXN);
	for(auto& p : P){
		cin >> p;
		for(int i = 0; i < MXN; i += p)
			LP[i] = p;
	}

	vector<int> dp(MXN);
	int cur = 0;
	for(int i = 1; i < MXN; i++){
		while(cur + LP[cur] <= i) cur++;
		if(cur >= i) dp[i] = MXN + 10;
		else dp[i] = dp[cur] + 1;
	}

	while(Q--){
		int x;
		cin >> x;
		if(dp[x] >= MXN) cout << "oo\n";
		else cout << dp[x] << '\n';
	}
	return 0;
}