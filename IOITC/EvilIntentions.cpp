#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	vector<int> in(n), out(n);
	vector<array<int, 2>> edges;

	for(int i = 0; i < n; i++)
		cin >> in[i];

	for(int i = 0; i < n; i++)
		cin >> out[i];

	for(int i = 0; i < n; i++){
		int w = min(in[i], out[i]);
		in[i] -= w;
		out[i] -= w;
		for(int j = 0; j < w; j++)
			edges.push_back({i+1, i+1});
	}

	int pin = 0, pout = 0;

	while(pin < n && pout < n){
		int t = min(in[pin], out[pout]);
		in[pin] -= t;
		out[pout] -= t;

		for(int i = 0; i < t; i++)
			edges.push_back({pout+1, pin+1});

		if(in[pin] == 0) pin++;
		if(out[pout] == 0) pout++;
	}

	while(pin < n && in[pin] == 0)
		pin++;
	while(pout < n && out[pout] == 0)
		pout++;
	
	if(pin != pout){
		cout << "NO\n";
		return 0;
	}

	cout << "YES\n";
	for(auto& [u, v] : edges)
		cout << u << ' ' << v << '\n';
	return 0; 
}