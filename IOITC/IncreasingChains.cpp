#include <bits/stdc++.h>

using namespace std;

const int MXN = 5001;

int A[MXN];
int lis[MXN][MXN];
int dp[MXN];

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, K;
	cin >> N >> K;

	for(int i = 1; i <= N; i++)
		cin >> A[i];

	for(int i = 1; i <= N; i++){
		multiset<int> s;
		for(int j = i; j <= N; j++){
			s.insert(A[j]);
			auto it = s.upper_bound(A[j]);
			if(it != s.end())
				s.erase(it);
			lis[i][j] = s.size();
		}
	}

	for(int i = 1; i <= N; i++){
		for(int j = 0; j < i; j++)
			dp[i] = max(dp[i], dp[j] + (lis[j+1][i] >= K ? lis[j+1][i] : 0));
	}

	cout << *max_element(dp + 1, dp + N + 1) << '\n';
	return 0; 
}