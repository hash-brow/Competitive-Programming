#include <bits/stdc++.h>

using namespace std;

const int mod = 1'000'000'007;
vector<int64_t> F;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int N, M;
	cin >> N >> M;

	F.resize(N+1);
	F[0] = F[1] = 1;
	for(int i = 2; i <= N; i++)
		F[i] = (F[i-1] * 1LL * i) % mod;

	vector<int64_t> R(N+1), L(N+1), S(N+1);
	vector<array<int, 2>> mxt(N+1);

	for(int i = 1; i <= N; i++){
		int l, r;
		cin >> l >> r;
		mxt[i] = {l, r};
		L[0]++; L[l+1]--;
		R[0]++; R[r+1]--;
		S[0]++; S[min(l, r) + 1]--;
	}

	for(int i = 1; i <= N; i++){
		R[i] += R[i-1];
		L[i] += L[i-1];
		S[i] += S[i-1];
	}

	int64_t ans = 0;

	for(int i = 1; i < N; i++){
		int64_t temp = ((N - 1) * (R[i] + L[i]) - (R[i] * L[i]) + S[i]) % mod;
		temp = (temp + mod) % mod;
		temp = (temp * 1LL * (N - i)) % mod;
		ans = (ans + temp) % mod;
	}

	for(int i = 1; i <= M; i++){
		int x, y;
		cin >> x >> y;
		int64_t sx = 1LL*max(mxt[x][1], mxt[y][0]);
		int64_t sy = 1LL*max(mxt[x][0], mxt[y][1]);

		int64_t temp = (((sx * 1LL * (2*N - sx - 1)) + (sy * 1LL * (2*N - sy - 1))) / 2) % mod; 
		ans = ((ans - temp) % mod + mod) % mod;
	}

	cout << (ans * 1LL * F[N-2]) % mod << '\n';
	return 0; 
}