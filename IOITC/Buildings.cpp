#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e17;

void solve(){
	int N;
	cin >> N;

	vector<array<int64_t, 3>> B(N);

	for(int i = 0; i < N; i++){
		auto& [h, p, idx] = B[i];
		cin >> h >> p;
		idx = i;
		if(i == N-1) p = 0;
	}

	vector<int64_t> dp(N, INF);
	dp[0] = 0;
	for(int i = 1; i < N; i++){
		dp[i] = B[0][1]*1LL*max(int64_t(0), B[i][0] - B[0][0]);
	}

	sort(B.begin() + 1, B.end());

	vector<int> jump(N), st;
	for(int i = 1; i < N; i++){
		while(!st.empty() && B[st.back()][1] >= B[i][1]){
			jump[st.back()] = i;
			st.pop_back();
		}

		st.push_back(i);
	}

	for(int i = 1; i < N; i++){
		int to = B[jump[i]][2], from = B[i][2];
		dp[to] = min(dp[to], dp[from] + B[i][1]*(B[jump[i]][0] - B[i][0]));
	}

	cout << dp[N-1] << '\n';
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int t;
	cin >> t;
	while(t--)
		solve();

	return 0;
}