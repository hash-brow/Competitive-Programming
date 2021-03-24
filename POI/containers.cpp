#include <bits/stdc++.h>

using namespace std;

const int k = 320; 
const int N = 100000;

int dp[N+k+1][k];
int cont[N+1];

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;

	while(q--){
		int a, l, d;
		cin >> a >> l >> d;
		--a;
		if(d >= k){
			for(int i = 0; i < l; i++) cont[a+i*d]++;
		}
		else{
			dp[a][d]++;
			dp[a+l*d][d]--;
		}
	}

	for(int j = 1; j < k; j++){
		for(int i = j; i < n; i++)
			dp[i][j] += dp[i-j][j];
	}

	for(int i = 0; i < n; i++){
		for(int j = 1; j < k; j++) cont[i] += dp[i][j];
		cout << cont[i] << ' ';
	}
	return 0; 
}