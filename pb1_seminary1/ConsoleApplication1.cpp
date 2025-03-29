#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

unsigned int* sieve(unsigned int n, unsigned int* length) {
    bool* is_prime = static_cast<bool*>(malloc((n + 1) * sizeof(bool)));
    if (!is_prime) return NULL;
    for (unsigned int i = 0; i <= n; i++) {
        is_prime[i] = true;
    }
    if (n >= 0) is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;
    for (unsigned int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (unsigned int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    unsigned int count = 0;
    for (unsigned int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            count++;
        }
    }
    *length = count;
    unsigned int* primes = static_cast<unsigned int*>(malloc(count * sizeof(unsigned int)));
    if (!primes) {
        free(is_prime);
        return NULL;
    }
    unsigned int index = 0;
    for (unsigned int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[index++] = i;
        }
    }
    free(is_prime);
    return primes;
}

int main(void) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    unsigned int length;
    unsigned int* primes = sieve(n, &length);
    if (!primes) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (unsigned int i = 0; i < length; i++) {
        printf("%u\n", primes[i]);
    }
    free(primes);
    return 0;
}