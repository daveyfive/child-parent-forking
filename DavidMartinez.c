// David Martinez PID:3787206 This program simulates a parallel task execution scenario using process forking

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Child Function Declerations 
unsigned long long factorial(int n);
void find_primes(int start, int end);
void fibonacci();
void find_composites(int start, int end);

int main() {
    pid_t child_pid;
    int num_children = 4;
    int i;

    printf("Enter the number of child processes to create (must be less than 5): ");
    scanf("%d", &num_children);

    if (num_children >= 5) {
        printf("Number of child processes must be less than 5.\n");
        return EXIT_FAILURE;
    }

    printf("Parent process (PID: %d) is creating %d child processes.\n", getpid(), num_children);

    for (i = 0; i < num_children; i++) {
        child_pid = fork();
        if (child_pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {

            switch (i) {
                case 0:
                    printf("Child %d (PID: %d) is computing the factorial of 5.\n", i+1, getpid());
                    printf("Child %d (PID: %d) completed its task. Result: %llu\n", i+1, getpid(), factorial(5));
                    break;
                case 1:
                    printf("Child %d (PID: %d) is finding prime numbers up to 20.\n", i+1, getpid());
                    find_primes(2, 20);
                    printf("Child %d (PID: %d) completed its task.\n", i+1, getpid());
                    break;
                case 2:
                    printf("Child %d (PID: %d) is calculating the Fibonacci sequence.\n", i+1, getpid());
                    fibonacci();
                    printf("Child %d (PID: %d) completed its task.\n", i+1, getpid());
                    break;
                case 3:
                    printf("Child %d (PID: %d) is finding all composite numbers between 1 and 100.\n", i+1, getpid());
                    find_composites(1, 100);
                    printf("Child %d (PID: %d) completed its task.\n", i+1, getpid());
                    break;
                default:
                    break;
            }
            exit(EXIT_SUCCESS);
        }
    }

    //Parent process
    while (wait(NULL) > 0); 

    printf("All child processes have completed. Parent (PID: %d) is displaying the final message.\n", getpid());

    return 0;
}

//Function to calculate factorials.
unsigned long long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

//Function to find prime numbers.
void find_primes(int start, int end) {
    int i, j;
    for (i = start; i <= end; i++) {
        for (j = 2; j <= i/2; j++) {
            if (i % j == 0)
                break;
        }
        if (j > i/2)
            printf("%d ", i);
    }
    printf("\n");
}

//Function to calculate the Fibonacci.
void fibonacci() {
    int i;
    unsigned long long first = 0, second = 1, next;
    printf("%llu ", first); 
    printf("%llu ", second); 
    for (i = 2; i < 25; i++) { 
        next = first + second;
        printf("%llu ", next);
        first = second;
        second = next;
    }
    printf("\n");
}

//Function to find composite numbers.
void find_composites(int start, int end) {
    int i, j;
    for (i = start; i <= end; i++) {
        int is_prime = 1;
        for (j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (!is_prime && i > 1)
            printf("%d ", i);
    }
    printf("\n");
}
