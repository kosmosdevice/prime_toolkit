#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int *data;
	int size;
} int_list;

typedef struct {
	double *data;
	int size;
} double_list;

typedef struct {
	int first;
	int second;
} int_tuple;

typedef struct {
	int_tuple *data;
	int size;
} int_tuple_list;

bool test_prime(int n) {
	if (n == 1)
		return false;
	for (int i = 2; i <= floor(sqrt(n)); i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int_list primes_up_to(int n) {
	int_list result = {0};
	bool *prime = malloc(n + 1 * sizeof(bool));
	memset(prime, true, (n + 1) * sizeof(bool));

	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p) {
				prime[i] = false;
			}
		}
	}

	result.data = malloc(n * sizeof(int));
	result.size = 0;

	for (int i = 2; i <= n; i++) {
		if (prime[i]) {
			result.data[result.size++] = i;
		}
	}
	free(prime);
	return result;
}

int_list sieve_of_atkin(int n) {
	int_list result = {0};
	result.data = malloc(n * sizeof(int));
	result.size = 0;
	bool *prime = malloc(n * sizeof(bool));
	memset(prime, false, n * sizeof(bool));

	if (n > 2)
		prime[2] = true;
	if (n > 3)
		prime[3] = true;

	for (int x = 1; x * x <= n; x++) {
		for (int y = 1; y * y <= n; y++) {
			int s = (4 * x * x) + (y * y);
			if (s <= n && (s % 12 == 1 || s % 12 == 5))
				prime[s] = !prime[s];
			s = (3 * x * x) + (y * y);
			if (s <= n && s % 12 == 7)
				prime[s] = !prime[s];
			s = (3 * x * x) - (y * y);
			if (x > y && s <= n && s % 12 == 11)
				prime[s] = !prime[s];
		}
	}

	for (int i = 5; i * i <= n; i++) {
		if (prime[i] == false)
			continue;
		for (int j = i * i; j <= n; j += i * i) {
			prime[j] = false;
		}
	}

	for (int i = 2; i <= n; i++) {
		if (prime[i])
			result.data[result.size++] = i;
	}

	return result;
}

int_list prime_factor(int n) {
	int_list factors = {0};
	factors.data = malloc(n * sizeof(int));
	factors.size = 0;

	int current = n;

	for (int i = 2; i * i <= current; i++) {
		while (current % i == 0) {
			factors.data[factors.size++] = i;
			current /= i;
		}
	}

	if (current > 1) {
		factors.data[factors.size++] = current;
	}

	return factors;
}

int_list prime_gaps(int_list primes) {
	int_list gaps = {0};
	gaps.data = malloc((primes.size - 1) * sizeof(int));
	gaps.size = 0;

	for (int i = 0; i < primes.size - 1; i++) {
		gaps.data[gaps.size++] = primes.data[i + 1] - primes.data[i];
	}
	return gaps;
}

double_list prime_gap_merits(int_list primes, int_list gaps) {
	double_list merits = {0};
	merits.data = malloc((primes.size) * sizeof(double));
	merits.size = 0;

	for (int i = 0; i < gaps.size; i++) {
		int g_n = gaps.data[i];
		int p_n = primes.data[i];
		double merit = g_n / log(p_n);
		merits.data[merits.size++] = merit;
	}
	return merits;
}

int_tuple_list twin_primes(int_list primes) {
	int_tuple_list twins = {0};
	twins.data = malloc((primes.size) * sizeof(int_tuple));
	twins.size = 0;
	for (int i = 1; i < primes.size; i++) {
		if (primes.data[i] - primes.data[i - 1] == 2) {
			int_tuple pair = {.first = primes.data[i - 1],
			                  .second = primes.data[i]};
			twins.data[twins.size++] = pair;
		}
	}
	return twins;
}

bool is_palindrome(int num) {
	int reverse = 0;
	int temp = num;
	while (temp != 0) {
		reverse = (reverse * 10) + (temp % 10);
		temp /= 10;
	}
	return (reverse == num);
}

int prime_palindrome(int n) {
    if (n <= 11) {
        while (1) {
            if (is_palindrome(n) && test_prime(n))
                return n;
            n++;
        }
    }
	while (1) {
		if (is_palindrome(n) && test_prime(n))
			return n;
		else
			n++;
        int digits = (int)log10(n) + 1;
        if (digits % 2 == 0) {
            n = (int)pow(10, digits);
        }
	}
}

int main(int argc, char **argv) {
	int choice;
	int n;

	printf("Prime Number Toolkit\n");
	printf("====================\n");
	printf("1. Find all primes up to n with sieve of Eratosthenes\n");
	printf("2. Test if n is prime\n");
	printf("3. Find prime factors of n\n");
	printf("4. Find prime gaps of primes up to n\n");
	printf("5. Find prime gap merits of primes up to n\n");
	printf("6. Find twin primes in primes up to n\n");
	printf("7. Find all primes up to n with sieve of Atkin\n");
	printf("8. Find all palindromic primes greater than or equal to n\n");
	printf("9. Exit\n");

	while (1) {
		printf("\nEnter your choice (1-9): ");
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = primes_up_to(n);
			printf("The prime numbers up to %d are:\n", n);
			for (int i = 0; i < primes.size; i++) {
				printf("%d ", primes.data[i]);
			}
			printf("\n");
			printf("There are %d primes up to %d\n", primes.size, n);
			free(primes.data);
			break;
		}
		case 2: {
			printf("Enter a number: ");
			scanf("%d", &n);
			if (test_prime(n))
				printf("%d is prime\n", n);
			else
				printf("%d is not prime\n", n);
			break;
		}
		case 3: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list factors = prime_factor(n);
			printf("Prime factors of %d: ", n);
			for (int i = 0; i < factors.size; i++) {
				printf("%d ", factors.data[i]);
			}
			printf("\n");
			free(factors.data);
			break;
		}
		case 4: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = primes_up_to(n);
			int_list gaps = prime_gaps(primes);
			printf("Prime gaps up to %d are:\n", n);
			for (int i = 0; i < gaps.size; i++) {
				printf("%d ", gaps.data[i]);
			}
			printf("\n");
			free(primes.data);
			free(gaps.data);
			break;
		}
		case 5: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = primes_up_to(n);
			int_list gaps = prime_gaps(primes);
			double_list merits = prime_gap_merits(primes, gaps);
			printf("Prime gap merits up to %d are:\n", n);
			for (int i = 0; i < merits.size; i++) {
				printf("%.2f ", merits.data[i]);
			}
			printf("\n");
			free(primes.data);
			free(gaps.data);
			free(merits.data);
			break;
		}
		case 6: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = primes_up_to(n);
			int_tuple_list twins = twin_primes(primes);
			printf("Prime twins up to %d are:\n", n);
			for (int i = 0; i < twins.size; i++) {
				int_tuple pair = twins.data[i];
				printf("%d and %d\n", pair.first, pair.second);
			}
			printf("\n");
			free(primes.data);
			free(twins.data);
			break;
		}
		case 7: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = sieve_of_atkin(n);
			printf("The prime numbers up to %d are:\n", n);
			for (int i = 0; i < primes.size; i++) {
				printf("%d ", primes.data[i]);
			}
			printf("\n");
			printf("There are %d primes up to %d\n", primes.size, n);
			free(primes.data);
			break;
		}
		case 8: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int result = prime_palindrome(n);
			printf("The smallest palidromic prime greater than or equal to %d "
			       "is: %d\n",
			       n, result);
			printf("\n");
			break;
		}
		case 9:
			return 0;
		default:
			printf("Invalid choice\n");
		}
	}
}
