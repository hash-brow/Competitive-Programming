#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << "[" << #x << ": " << x << "] "; 
struct UFDS{
	vector<int> e; 
	void init(int n){
		e = vector<int>(n, -1);
	}
	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x])); 
	}
	bool same(int x, int y){
		return get(x) == get(y); 
	}
	bool unite(int x, int y){
		x = get(x), y = get(y); 
		if(x == y) 
			return 0; 
		if(e[x] > e[y])
			swap(x, y); 
		e[x] += e[y]; 
		e[y] = x; 
		return 1; 
	}
}; 	
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, e;
	cin >> n >> e; 

	vector<array<int, 5>> event;  
	for(int i = 0; i < e; i++){
		int u, v, o, c; 
		cin >> u >> v >> o >> c;
		event.push_back({o, u, v, 0, i}); 
		event.push_back({c, u, v, 2, i}); 
	}
	int q;
	cin >> q; 
	for(int i = 0; i < q; i++){
		int time, x, y;
		cin >> x >> y >> time;
		event.push_back({time, x, y, 1, i});
	}

	sort(event.begin(), event.end(), [](array<int, 5> a, array<int, 5> b){
		if(a[0] == b[0])
			if(a[3] < b[3])
				return true; 
		if(a[0] < b[0])
			return true; 
		return false;
	}); 

	UFDS open;  
	open.init(n);  
	int sz = event.size(); 
	vector<int> ans(q);

	int i; 
	for(i = 0; i < sz; i++){
		if(event[i][3] == 2)
			break; 
		if(event[i][3] == 0) 
			open.unite(event[i][1], event[i][2]); 
		if(event[i][3] == 1){
			if(open.same(event[i][1], event[i][2]))
				ans[event[i][4]] = 1; 
			else ans[event[i][4]] = 0; 
		}
	}
	open.init(n); 
	for(int j = sz - 1; j >= i; --j){
		if(event[j][3] == 2) 
			open.unite(event[j][1], event[j][2]); 
		if(event[j][3] == 1){
			if(open.same(event[j][1], event[j][2]))
				ans[event[j][4]] = 1; 
			else ans[event[j][4]] = 0; 
		}
	}
	for(int i = 0; i < q; i++)
		cout << (ans[i] == 1 ? 'Y' : 'N') << '\n';
	return 0; 
}
