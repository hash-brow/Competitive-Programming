#include <bits/stdc++.h>

using namespace std;

bool query(vector<int>& A, vector<int>& B){
	cout << "Q\n" << A.size() << '\n';
	for(int v : A)
		cout << v << ' ';
	cout << '\n' << B.size() << '\n';
	for(int v : B)
		cout << v << ' ';
	cout << endl;
	bool x;
	cin >> x;
	return x;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N;
	cin >> N;

	vector<int> found, unfound;

	for(int i = 2; i <= N; i++)
		unfound.push_back(i);

	found.push_back(1);

	vector<int> fx(N+1);
	fx[1] = 1;

	while(found.size() < N){
		int x = unfound.size();
		if(x == 1){
			if(!query(found, unfound)){
				cout << "A NO\n";
				return 0;
			}

			found.push_back(unfound[0]);
			fx[unfound[0]] = 1;
			unfound.clear();
			for(int i = 1; i <= N; i++)
				if(!fx[i])
					unfound.push_back(i);
			continue;
		}

		vector<int> A;
		for(int i = 0; i < x/2; i++)
			A.push_back(unfound[i]);

		if(query(found, A))
			unfound = A;
		else{
			vector<int> B;
			for(int i = x/2; i < x; i++)
				B.push_back(unfound[i]);
			unfound = B;
		}
	}

	found.clear();
	unfound.clear();

	fx = vector<int>(N+1, 0);
	fx[1] = 1;

	found.push_back(1);
	for(int i = 2; i <= N; i++)
		unfound.push_back(i);

	while(found.size() < N){
		int x = unfound.size();
		if(x == 1){
			if(!query(unfound, found)){
				cout << "A NO\n";
				return 0;
			}

			found.push_back(unfound[0]);
			fx[unfound[0]] = 1;
			unfound.clear();
			for(int i = 1; i <= N; i++)
				if(!fx[i])
					unfound.push_back(i);
			continue;
		}

		vector<int> A;
		for(int i = 0; i < x/2; i++)
			A.push_back(unfound[i]);

		if(query(A, found))
			unfound = A;
		else{
			vector<int> B;
			for(int i = x/2; i < x; i++)
				B.push_back(unfound[i]);
			unfound = B;
		}
	}

	cout << "A YES\n";
	return 0; 
}