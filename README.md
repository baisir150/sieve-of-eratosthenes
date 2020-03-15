# Sieve of Eratosthenes
Parallel Sieve of Eratosthenes for Finding All Prime Numbers within 10^10

## Objective
Modifying the parallel Sieve of Eratosthenes to find primes numbers more efficiently and cost effectively.
1. Original Sieve of Eratosthenes
2. Avoid using memory for even numbers
3. Each process find its own sieving primes via local computations (not broadcasts)
4. More effective use of caches

## Instruction
| **Command**                        | **Description**                      |
|------------------------------------|--------------------------------------|
| `make`                             | compile                              |
| `make clean`                       | remove outputted files               |
| `make test`                        | execute cli                          |
| `make valgrind`                    | cun valgrind for memory management   |

<hr>
<p align="center">&copy; Namito Yokota</p>