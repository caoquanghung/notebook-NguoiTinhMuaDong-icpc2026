bool isPrime[N];
void sieve() {
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    for(int i = 2; 1LL * i * i < N; i++) if(isPrime[i]) {
        for(int j = i * i; j < N; j += i) 
            isPrime[j] = 0;
    }
}