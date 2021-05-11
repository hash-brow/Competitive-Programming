#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MXN = 200001;
const int lg = 20;

int e[2*MXN], val[2*MXN], up[lg][2*MXN];
vector<int> g[2*MXN];

int nxt;

int get(int x){
	return (e[x] < 0 ? x : e[x] = get(e[x]));
}

bool unite(int u, int v, int wt){
	u = get(u), v = get(v);
	if(u == v)
		return false;

	val[nxt] = wt;
	
	g[nxt].push_back(u);
	g[nxt].push_back(v);

	e[nxt] += e[u] + e[v];

	e[u] = nxt;
	e[v] = nxt;

	nxt++;
	return true;
}

int timer, tin[2*MXN], tout[2*MXN];

void dfs(int node, int par){
	tin[node] = timer++;

	up[0][node] = par;
	for(int i = 1; i < lg; i++)
		up[i][node] = up[i-1][up[i-1][node]];

	for(int v : g[node])
		if(v != par) dfs(v, node);

	tout[node] = timer;
}

bool isAncestor(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){
	if(isAncestor(u, v))
		return u;
	if(isAncestor(v, u))
		return v;

	for(int i = lg-1; i >= 0; --i)
		if(!isAncestor(up[i][u], v))
			u = up[i][u];

	return up[0][u];
}

inline bool valid(int x, int y, int X, int Y){
	return x > 0 && x <= X && y > 0 && y <= Y;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int H, W, P, Q;
	cin >> H >> W >> P >> Q;

	int grid[H+1][W+1];
	memset(grid, -1, sizeof grid);

	for(int i = 1; i <= H; i++){
		for(int j = 1; j <= W; j++){
			char x;
			cin >> x;
			if(x == '.') grid[i][j] = 0;
		}
	}

	deque<pair<int, int>> dq;

	vector<vector<int>> dist(H+1, vector<int>(W+1, INF)), bfs(H+1, vector<int>(W+1));

	for(int i = 1; i <= P; i++){
		int x, y;
		cin >> x >> y;

		grid[x][y] = i;
		dist[x][y] = 0;
		bfs[x][y] = i;

		dq.emplace_back(x, y);
	}

	vector<array<int, 3>> edges;

	int delta[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

	while(!dq.empty()){
		auto [x, y] = dq.front();
		dq.pop_front();

		for(auto& [dx, dy] : delta){
			int nx = dx + x, ny = dy + y;
			if(!valid(nx, ny, H, W) || grid[nx][ny] < 0)
				continue;

			if(dist[nx][ny] < INF){
				if(bfs[x][y] == bfs[nx][ny])
					continue;
				edges.push_back({(dist[nx][ny] + dist[x][y]), bfs[x][y], bfs[nx][ny]});
				continue;
			}
			int wt = (grid[nx][ny] == 0);

			bfs[nx][ny] = bfs[x][y];
			
			if(wt == 0) dq.emplace_front(nx, ny);
			else dq.emplace_back(nx, ny);
			
			dist[nx][ny] = dist[x][y] + wt;
		}
	}

	sort(edges.begin(), edges.end());

	memset(e, -1, sizeof e);
	nxt = P+1;

	for(int i = 0; i <= 2*P; i++)
		val[i] = INF;

	for(auto& [wt, u, v] : edges){
		unite(u, v, wt);
	}

	for(int i = 1; i < nxt; i++)
		if(get(i) == i)
			g[0].push_back(i);

	dfs(0, 0);

	while(Q--){
		int u, v;
		cin >> u >> v;
		int l = lca(u, v);
		cout << (val[l] == INF ? -1 : val[l]) << '\n';
	}

	return 0; 
}