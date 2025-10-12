int prime[N];
void sieveFactorize() {
    for(int i = 2; i < N; i++) if(!prime[i]) {
        prime[i] = i;
        for(int j = i * i; j < N; j += i) if(!prime[j])
            prime[j] = i;
    }
}