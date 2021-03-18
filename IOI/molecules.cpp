#include <bits/stdc++.h>
#include "molecules.h"

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w){
	vector<pair<int, int>> W;
	int n = w.size();

	int64_t sum = 0; 
	for(int i = 0; i < n; i++){
		W.emplace_back(w[i], i);
		sum += int64_t(w[i]);
	}
	sort(W.begin(), W.end());
	vector<int> ans;
	if(sum < l || W[0].first > u)
		return ans;

	int r = 0; 
	int64_t cur = 0; 
	for(int i = 0; i < n; i++){
		while(r < n && int64_t(cur + W[r].first) <= u)
			cur += int64_t(W[r++].first);

		if(cur >= l && cur <= u){
			for(int L = i; L < r; L++)
				ans.push_back(W[L].second);
			return ans;
		}

		cur -= int64_t(W[i].first);
	}
	return ans;	
}