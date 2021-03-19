/*
Finds all prime numbers in [1, n] in O(nloglogn)
spf[i] is the smallest prime factor of i
*/

vector<bool> prime(MXN, 1);
vector<int> primes;
vector<int> spf(MXN);

void sieve(){
	prime[0] = prime[1] = 0;
	for(int i = 2; i < MXN; i++){
		if(!prime[i]) continue;
		primes.push_back(i);
		spf[i] = i;
		for(int j = i*i; j < MXN; j += i){
			prime[j] = 0;
			spf[j] = i;
		}
	}
}
