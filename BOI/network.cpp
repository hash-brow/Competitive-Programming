#include <bits/stdc++.h>
#include "network.h"

using namespace std;

int _ping(int u, int v){
	return (u == v ? -1 : ping(u, v));
}

void findRoute(int N, int u, int v){
	int dist[N + 1];
	for(int i = 1; i <= N; i++)
		dist[i] = _ping(v, i);

	int cur = u;
	for(int i = dist[u] - 1; i >= 0; --i)
		for(int j = 1; j <= N; j++){
			if(dist[j] == i && ping(cur, j) == 0){
				travelTo(j);
				cur = j;
				break;
			}
		}

	travelTo(v);
}