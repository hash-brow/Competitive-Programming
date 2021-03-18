#include <combo.h>
#include <bits/stdc++.h>

using namespace std;

string guess_sequence(int N){
	string ans;
	vector<string> s = {"A", "B", "X", "Y"};
	if(press("AB")){
		if(press("A")){
			ans += "A";
			s.erase(s.begin());
		}
		else{
			ans += "B";
			s.erase(s.begin() + 1);
		}
	}
	else{
		if(press("X")){
			ans += "X";
			s.erase(s.begin() + 2);
		}
		else{
			ans += "Y";
			s.erase(s.begin() + 3);
		}
	}
	if(N == 1)
		return ans;
	for(int i = 1; i < N-1; i++){
		string query = ans + s[0] + ans + s[1] + s[0] + ans + s[1] + s[1] + ans + s[1] + s[2];
		int r = press(query);
		if(r == ans.size() + 1){
			ans += s[0];
			continue;
		}
		if(r == ans.size() + 2){
			ans += s[1];
			continue;
		}
		if(r == ans.size()){
			ans += s[2];
			continue;
		}
	}
	string query = ans + s[0] + ans + s[1];
	if(press(query) == N){
		query = ans + s[0];
		if(press(query) == N) return query;
		query = ans + s[1];
		return query;
	}
	return (ans + s[2]);
}