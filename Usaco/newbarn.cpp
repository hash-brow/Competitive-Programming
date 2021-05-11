#include <bits/stdc++.h>

using namespace std;

const int MXN = 100001;
const int lg = 17;

int up[lg][MXN], depth[MXN], comp[MXN];
array<int, 2> dia[MXN];

int lca(int a, int b){
	if(depth[a] < depth[b]) 
		swap(a, b);

	for(int i = lg-1; i >= 0; --i) 
		if((depth[a] - depth[b])&(1 << i)) 
			a = up[i][a];

	if(a == b) return a;

	for(int i = lg-1; i >= 0; --i)
		if(up[i][a] != up[i][b]){
			a = up[i][a];
			b = up[i][b];
		}

	return up[0][a];
}

int dist(int a, int b){
	return depth[a] + depth[b] - 2*depth[lca(a, b)];
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);

	int Q;
	cin >> Q;

	int node = 0;

	while(Q--){
		char c; int x;
		cin >> c >> x;
		if(c == 'B'){
			node++;
			if(x == -1){
				comp[node] = node;
				dia[comp[node]] = {node, node};
				continue;
			}
			comp[node] = comp[x];
			depth[node] = depth[x] + 1;

			up[0][node] = x;
			for(int i = 1; i < lg; i++)
				up[i][node] = up[i-1][up[i-1][node]];

			auto& [e1, e2] = dia[comp[node]];

			int d = dist(e1, e2);
			if(dist(node, e1) > d) e2 = node;
			else if(dist(node, e2) > d) e1 = node;
		}
		else{
			auto& [e1, e2] = dia[comp[x]];
			cout << max(dist(x, e1), dist(x, e2)) << '\n';
		}
	}
	return 0;
}