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

bool test_prime(int n) {
	for (int i = 2; i <= floor(sqrt(n)); i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int_list primes_up_to(int n) {
	int_list result = {0};

	bool prime[n];
	memset(prime, true, sizeof(prime));

	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p) {
				prime[i] = false;
			}
		}
	}

	int count = 0;
	printf("The prime numbers up to %d are:\n", n);
	for (int p = 2; p <= n; p++) {
		if (prime[p]) {
			++count;
			printf("%d ", p);
		}
	}
	printf("\n");
	printf("There are %d primes up to %d\n", count, n);

	result.data = malloc(count * sizeof(int));
	result.size = 0;

	for (int i = 2; i <= n; i++) {
		if (prime[i]) {
			result.data[result.size++] = i;
		}
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

void twin_primes(int n) { ; }

int main(int argc, char **argv) {
	int choice;
	int n;

	printf("Prime Number Toolkit\n");
	printf("====================\n");
	printf("1. Find all primes up to n\n");
	printf("2. Test if n is prime\n");
	printf("3. Find prime factors of n\n");
	printf("4. Find prime gaps of primes up to n\n");
	printf("5. Find prime gap merits of primes up to n\n");
	printf("6. Exit\n");

	while (1) {
		printf("\nEnter your choice (1-6): ");
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			printf("Enter a number: ");
			scanf("%d", &n);
			int_list primes = primes_up_to(n);
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

		case 6:
			return 0;

		default:
			printf("Invalid choice\n");
		}
	}
}
