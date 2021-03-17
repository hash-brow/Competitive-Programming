/*
Finds all divisors of all i in [1, n] in O(nlogn)
*/

vector<vector<int>> divisors(MXN);

void find(){
	for(int i = 1; i < MXN; i++)
		for(int j = i; j < MXN; j += i)
			divisors[j].push_back(i);
}