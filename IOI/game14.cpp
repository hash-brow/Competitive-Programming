#include <bits/stdc++.h>

using namespace std;

vector<int> cnt;

void initialize(int n){
	cnt.resize(n);
}
int hasEdge(int u, int v){
	u = max(u, v);
	cnt[u]++;
	if(cnt[u] == u) return 1;
	return 0;
}