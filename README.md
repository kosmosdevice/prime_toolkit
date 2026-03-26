# Prime Number Toolkit

A command-line utility for exploring properties of prime numbers, including
finding primes, factorization, gap analysis, and merit calculations.

## Features

    - Find Primes: Generate all prime numbers up to a given limit using the
    Sieve of Eratosthenes
    - Test Primality: Check if a number is prime using trial division
    - Prime Factorization: Decompose a number into its prime factors
    - Gap Analysis: Calculate differences between consecutive primes
    - Merit Calculation: Compute gap merit values gn / ln(pn) for primes pn
    and subsequent gap gn up to n
    - Twin Primes: Generate all twin primes up to a given limit
    - Sieve of Atkin: Generate all prime numbers up to a given limit using the
    Sieve of Atkin
    - Palindromic Primes: Generate all paliedromic prime numbers greater than
    or equal to a given limit
    - Prime Permutations: Find the number of permutations of 1 to n so that 
    prime numbers are at prime indices

## Building

```bash
gcc prime_toolkit.c -lm
```
The -lm flag links the math library (required for log() and sqrt()).

## Usage

```bash
./a.out
```
Then select from the menu:
### Prime Number Toolkit
====================
1. Find all primes up to n with sieve of Eratosthenes
2. Test if n is prime
3. Find prime factors of n
4. Find prime gaps of primes up to n
5. Find prime gap merits of primes up to n
6. Find twin primes in primes up to n
7. Find all primes up to n with sieve of Atkin
8. Find all palindromic primes greater than or equal to n
9. Find the number of permutations of 1 to n so that prime numbers are at prime indices
10. Exit

## Memory safety

Test for memory leaks with Valgrind:

```bash
valgrind --leak-check=full ./a.out
```

## Algorithm Notes

### Time Complexity

    - Sieve of Eratosthenes: O(n log log n)
    - Sieve or Atkin: O(n)
    - Trial division: O(√n)
    - Factorization: O(√n)
