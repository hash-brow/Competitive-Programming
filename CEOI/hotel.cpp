#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m, o;
	cin >> n >> m >> o;

	multiset<pair<int64_t, int64_t>> hotel;
	for(int i = 0; i < n; i++){
		int64_t c, p;
		cin >> c >> p;
		hotel.emplace(p, c);
	}

	vector<pair<int64_t, int64_t>> order;
	for(int i = 0; i < m; i++){
		int64_t c, p;
		cin >> c >> p;
		order.emplace_back(c, p);
	}

	sort(order.rbegin(), order.rend());
	vector<int64_t> store;
	int64_t profit = 0;
	for(int i = 0; i < m; i++){
		int64_t cur = order[i].second;
		auto it = hotel.lower_bound({cur, 0});
		if(it == hotel.end())
			continue;

		if(it->second >= order[i].first)
			continue;

		store.push_back(order[i].first - it->second);
		hotel.erase(it);
	}

	sort(store.rbegin(), store.rend());

	for(int i = 0; i < min(o, (int)store.size()); i++)
		profit += store[i];

	cout << profit << '\n';
	return 0; 
}