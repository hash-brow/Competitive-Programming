/*
the euler totient function - no. of numbers less than n that it is comprime with
O(log n) per phi query
*/

int phi(int n){
	vector<int> f = factors(n);
	f.erase(unique(f.begin(), f.end()), f.end());
	int res = n;
	for(int i : f){
		res = res*(i-1) / i;
	}
	return res;
}

/*
As a tweak to the sieve itself
*/

vector<int> phi(MXN);
vector<bool> prime(MXN);

void sieve(){
	for(int i = 2; i < MXN; i++){
		phi[i] = i;
		prime[i] = 1;
	}
	for(int i = 2; i < MXN; i++){
		if(!prime[i])
			continue;
		for(int j = i; j < MXN; j += i){
			prime[j] = 0;
			phi[j] -= phi[j]/i;
		}
	}
}