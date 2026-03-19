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
1. Find all primes up to n
2. Test if n is prime
3. Find prime factors of n
4. Find prime gaps of primes up to n
5. Find prime gap merits of primes up to n
6. Exit

## Memory safety

Test for memory leaks with Valgrind:

```bash
valgrind --leak-check=full ./a.out
```

## Algorithm Notes

    - Sieve of Eratosthenes: O(n log log n)
    - Trial division: O(√n)
    - Factorization: O(√n)
