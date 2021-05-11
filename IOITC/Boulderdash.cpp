#include <bits/stdc++.h>

using namespace std;

const int MXN = 100005;
const int lg = 20;
const int INF = 100000000;

vector<int> g[MXN];
int depth[MXN], up[lg][MXN], pos[MXN], counter = 0;
vector<int> subtreemin(MXN, INF), order;

void gmin(int node){
	subtreemin[node] = node;
	for(int v : g[node]){
		gmin(v);
		subtreemin[node] = min(subtreemin[node], subtreemin[v]);
	}
}

void dfs(int node, int par){
	depth[node] = depth[par] + 1;

	up[0][node] = par;
	for(int i = 1; i < lg; i++)
		up[i][node] = up[i-1][up[i-1][node]];

	sort(g[node].begin(), g[node].end(), [&](int l, int r){
		return subtreemin[l] < subtreemin[r];
	});

	for(int v : g[node]){
		dfs(v, node);
	}

	order.push_back(node);
	pos[node] = counter++;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;

	int root;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		if(x == 0){
			root = i;
			continue;
		}
		--x;
		g[x].push_back(i);
	}

	gmin(root);

	dfs(root, root);

	set<int> next;
	for(int i = 0; i < n; i++)
		next.insert(i);

	for(int _ = 0; _ < q; _++){
		int t, x;
		cin >> t >> x;
		if(t == 1){
			int res;
			for(int i = 0; i < x; i++){
				res = order[*next.begin()];
				next.erase(next.begin());
			}
			cout << res + 1 << '\n';
		}
		else{
			--x;
			int v = x;
			for(int i = lg-1; i >= 0; --i){
				if(up[i][x] != x && next.find(pos[up[i][x]]) == next.end())
					x = up[i][x];
			}
			next.insert(pos[x]);
			cout << depth[v] - depth[x] << '\n';
		}
	}
	return 0; 
}