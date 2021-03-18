#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

vector<array<int, 2>> del = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

bool check(int x, int y, int r, int c){
	return x >= 0 && x < r && y >= 0 && y < c;
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int h, w;
	cin >> h >> w;

	char mat[h][w];

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			cin >> mat[i][j];

	deque<array<int, 2>> q;
	q.push_back({0, 0});
	int d[h][w];

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			d[i][j] = INF;

	d[0][0] = 1;

	while(!q.empty()){
		array<int, 2> cur = q.front();
		q.pop_front();
		int x = cur[0], y = cur[1];

		for(auto &[dx, dy] : del){
			if(!check(x+dx, y+dy, h, w))
				continue;
			if(mat[x+dx][y+dy] == '.')
				continue;
			int nxt = d[x][y] + (mat[x+dx][y+dy] == mat[x][y] ? 0 : 1);
			if(d[x+dx][y+dy] <= nxt)
				continue;
			if(mat[x+dx][y+dy] == mat[x][y])
				q.push_front({x+dx, y+dy});
			else q.push_back({x+dx, y+dy});

			d[x+dx][y+dy] = nxt;
		}
	}

	int ans = 0; 

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++){
			if(mat[i][j] == '.')
				continue;
			ans = max(ans, d[i][j]);
		}

	cout << ans << '\n';
	return 0; 
}