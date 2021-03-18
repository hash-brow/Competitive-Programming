#include <bits/stdc++.h>
#include "robots.h"

using namespace std;

const int MXT = 1000000;
const int MXN = 50000;

int a, b, x[MXN], y[MXN], t;
pair<int, int> toy[MXT];

bool check(int mid){
	priority_queue<pair<int, int>> pq;
	int taken = 0;

	for(int i = 0; i < a; i++){
		for(; taken < t && toy[taken].first < x[i]; taken++)
			pq.emplace(toy[taken].second, toy[taken].first);
		for(int r = 0; r < mid && !pq.empty(); r++)
			pq.pop();
	}

	for(; taken < t; taken++)
		pq.emplace(toy[taken].second, toy[taken].first);

	for(int i = 0; i < b; i++){
		for(int r = 0; r < mid && !pq.empty(); r++){
			if(pq.top().first >= y[i]) return 0;
			pq.pop();
		}
	}

	return pq.empty();
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]){
	a = A, b = B, t = T;
	for(int i = 0; i < A; i++)
		x[i] = X[i];
	for(int i = 0; i < B; i++)
		y[i] = Y[i];
	for(int i = 0; i < T; i++)
		toy[i] = {W[i], S[i]};

	sort(x, x+a);
	sort(y, y+b, greater<int>());
	sort(toy, toy+t);

	int lo = 1, hi = T, ans = -1;
	while(lo <= hi){
		int mid = (lo + hi) >> 1;
		if(check(mid)){
			ans = mid;
			hi = mid - 1;
		}
		else lo = mid + 1;
	}

	return ans;
}