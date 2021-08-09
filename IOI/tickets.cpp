#include <bits/stdc++.h>
#include "tickets.h"

using namespace std;

long long find_maximum(int k, vector<vector<int>> x){
	int N = x.size(), M = x[0].size();

	vector<vector<int>> ans(N, vector<int>(M, -1));

	long long sum = 0;

	priority_queue<array<int64_t, 3>> pq;

	for(int i = 0; i < N; i++){
		for(int j = 0; j < k; j++){
			pq.push({x[i][j] +  x[i][M-k+j], i, j});
			ans[i][j] = 0;
			sum -= x[i][j];
		}
	}

	for(int _ = 0; _ < (N * 1LL * k) / 2; _++){
		auto [v, i, j] = pq.top();
		pq.pop();
		sum += v;
		ans[i][j] = -1;
		ans[i][M - k + j] = 1;
	}

	int l[N], r[N]; array<int, 2> arr[N];

	for(int i = 0; i < N; i++){
		arr[i][0] = 0;
		for(int j = 0; j < M; j++){
			if(ans[i][j] == 1){
				arr[i][0]++;
				r[i] = M - 1;
			}
			else if(ans[i][j] == 0) l[i] = 0;
		}
		arr[i][1] = i;
	}

	for(int i = 0; i < k; i++){
		sort(arr, arr + N);
		for(int j = 0; j < N; j++){
			int col = arr[j][1];

			if(j < N / 2) {
				ans[col][l[col]++] = i;
			}
			else{
				ans[col][r[col]--] = i;
				arr[j][0]--;
			}
		}
	}

	allocate_tickets(ans);
	return sum;	
}