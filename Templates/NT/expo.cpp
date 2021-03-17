/*
(a^b) % mod in log(b) time
*/

int64_t expo(int64_t a, int64_t b){
	int64_t res = 1;
	while(b){
		if(b & 1)
			res = (res * a) % mod;
		b >>= 1;
		(a *= a) %= mod;
	}
	return res;
}

int64_t inv(int64_t a){
	return expo(a, mod-2);
}