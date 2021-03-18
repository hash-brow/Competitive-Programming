#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << "[" << #x << ": " << x << "] ";

const int MXN = 10000;
const int MXQ = 50000;
const int MXW = 2001;
const int64_t INF = 1e18;

int N, W[MXN], Q, L[MXQ], R[MXQ], K[MXQ];
int64_t V[MXN], ans[MXQ], dpL[MXN][MXW], dpR[MXN][MXW];

void dnc(int l, int r, vector<int> queries, int lev){

	int mid = (l + r) >> 1;

	if(queries.size() == 0)
		return;

	if(l == r){
		for(int& idx : queries)
			if(K[idx] >= W[l])
				ans[idx] = V[l];
		return;
	}

	for(int i = mid; i >= l; --i){
		for(int j = 1; j < MXW; j++){
			dpL[i][j] = max(dpL[i+1][j], dpL[i][j-1]);
			if(j - W[i] >= 0)
				dpL[i][j] = max(dpL[i][j], dpL[i+1][j-W[i]] + V[i]);
		}
	}

	for(int i = mid + 1; i <= r; i++){
		for(int j = 1; j < MXW; j++){
			dpR[i][j] = max(dpR[i-1][j], dpR[i][j-1]);
			if(j - W[i] >= 0)
				dpR[i][j] = max(dpR[i][j], dpR[i-1][j-W[i]] + V[i]);
		}
	}

	vector<int> nq[2];

	for(int& idx : queries){
		if(L[idx] <= mid && R[idx] > mid){
			for(int x = 0; x <= K[idx]; x++){
				ans[idx] = max(ans[idx], dpL[L[idx]][x] + dpR[R[idx]][K[idx]-x]);
			}
			
			continue;
		}
		nq[L[idx] > mid].push_back(idx);
	}

	for(int i = l; i <= r; i++)
		for(int j = 1; j < MXW; j++)
			dpL[i][j] = dpR[i][j] = 0;

	dnc(l, mid, nq[0], lev+1);
	dnc(mid + 1, r, nq[1], lev + 1);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	cin >> N;
	for(int i = 0; i < N; i++)
		cin >> W[i] >> V[i];
	cin >> Q;
	vector<int> queries(Q);
	for(int i = 0; i < Q; i++){
		cin >> L[i] >> R[i] >> K[i]; 
		--L[i], --R[i];
		queries[i] = i;
	}

	dnc(0, N-1, queries, 0);

	for(int i = 0; i < Q; i++)
		cout << ans[i] << '\n';
	return 0; 
}