#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, t, p;
	cin >> n >> t >> p;

	int score[t];
	memset(score, 0, sizeof score);
	int solve[n][t];

	for(int i = 0; i < n; i++){
		for(int j = 0; j < t; j++){
			cin >> solve[i][j];
			score[j] += 1 - solve[i][j];
		}
	}

	pair<int, int> P[n];
	int task[n];

	memset(task, 0, sizeof task);

	for(int i = 0; i < n; i++){
		P[i].first = i;
		P[i].second = 0;
		for(int j = 0; j < t; j++){
			P[i].second += score[j]*solve[i][j];
			task[i] += solve[i][j];
		}
	}

	sort(P, P + n, [&](pair<int, int>& a, pair<int, int>& b){
		if(a.second == b.second) {
			if(task[a.first] == task[b.first])
				return a.first < b.first;
			return task[a.first] > task[b.first];
		}
		return a.second > b.second;
	});	

	for(int i = 0; i < n; i++)
		if(P[i].first == p-1){
			cout << P[i].second << " " << i+1 << '\n';
			return 0;
		}

	return 0; 
}