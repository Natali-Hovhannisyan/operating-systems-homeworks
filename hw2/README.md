# Homework 2 Report: `fork()` and `exec()`

## Assignment 0: Multiple Fork Calls

### Source Code

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    sleep(10);

    return 0;
}
```

### Analysis

The program calls `fork()` four times. Every existing process continues executing the next `fork()`, so the number of processes doubles each time:

- after 1st fork: 2 processes
- after 2nd fork: 4 processes
- after 3rd fork: 8 processes
- after 4th fork: 16 processes

`fork()` returns `0` in the child, a positive child PID in the parent, and a negative value if it fails. The program checks only for the failure case.

`getpid()` prints the current process ID and `getppid()` prints its parent process ID. The `pstree` output confirmed the parent-child hierarchy and showed the 16 `assignment0` processes. `sleep(10)` keeps them alive long enough to inspect the process tree.

---

## Assignment 1: Simple Fork and Exec

### Source Code

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int ret = fork();

    if (ret == 0) {
        execl("/usr/bin/ls", "ls", NULL);
    }
    else {
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}
```

### Analysis

`fork()` creates one child process. In the child, `ret == 0`, so `execl()` replaces the child process with `/usr/bin/ls`.

If `execl()` succeeds, it does not return to the original child program. The parent receives a positive return value from `fork()`, waits for the child using `wait(NULL)`, and then prints `Parent process done`.

This gives the order:

1. child runs `ls`
2. parent waits
3. parent prints its message

---

## Assignment 2: Multiple Forks and Execs

### Source Code

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int child1 = fork();

    if (child1 == 0) {
        execl("/usr/bin/ls", "ls", NULL);
    }

    wait(NULL);

    int child2 = fork();

    if (child2 == 0) {
        execl("/usr/bin/date", "date", NULL);
    }

    wait(NULL);

    printf("Parent process done\n");

    return 0;
}
```

### Analysis

The first `fork()` creates the first child. That child runs `ls` using `execl()`.

The parent calls `wait(NULL)` before creating the second child. This forces the `ls` process to finish first.

Then the second `fork()` creates another child, which runs `/usr/bin/date`. The parent waits again and finally prints `Parent process done`.

The process relationship is one parent with two children created one after another. The waits are important because without them, the scheduler could run `date` before `ls`.

---

## Assignment 3: Fork and Exec with Arguments

### Source Code

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int child = fork();

    if (child == 0) {
        execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);
    }

    wait(NULL);

    printf("Parent process done\n");

    return 0;
}
```

### Analysis

`fork()` creates one child. The child calls `execl()` to run `/usr/bin/echo`.

The arguments passed to `execl()` are:

```text
"echo"
"Hello from the child process"
NULL
```

The final `NULL` marks the end of the argument list. The child process is replaced by `echo`, which prints the message.

The parent waits for the child and prints its own message afterward.

---

## Assignment 4: Fork and Exec with `grep`

### Source Code

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int child = fork();

    if (child == 0) {
        execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);
    }

    wait(NULL);

    printf("Parent process done\n");
}
```

### Analysis

The program creates one child process with `fork()`.

The child uses `execl()` to replace itself with the `grep` program:

```text
grep main test.txt
```

This searches `test.txt` for lines containing the word `main`.

The parent waits until the child finishes and then prints `Parent process done`.

During testing, `test.txt` contained lines without the word `main`, so `grep` produced no matching output. This shows that `execl()` successfully runs another program, but the output depends on that program's input and arguments.

---


## Development Notes

A few mistakes during development helped clarify how the process-related system calls work:

- In Assignment 0, the first compilation produced warnings because `exit()` was used without including `<stdlib.h>`. Adding that header fixed the issue.
- Assignment 0 also showed how quickly the number of processes grows. With four sequential `fork()` calls, the program created 16 processes, which was confirmed with `pstree`.
- In Assignment 1, `execl()` initially used the wrong path for `ls`. Using `/usr/bin/ls` fixed the problem.
- In Assignment 1, one version printed `Parent process done` more than once because the parent/child control flow was not separated correctly.
- In Assignment 2, too many `fork()` calls were used at first, which created extra processes and repeated `ls`, `date`, and parent outputs.
- Assignment 2 also showed that child execution order is not guaranteed. `date` sometimes ran before `ls`, so `wait(NULL)` was added between the two forks to force the required order.
- In Assignment 3, the first `execl()` call was missing the final `NULL`, which caused a compiler warning. Adding `NULL` correctly terminated the argument list.
- In Assignment 4, `grep` produced output only when the searched word was present in `test.txt`, showing that the child process may execute correctly even when the command prints nothing.

## Conclusion

These assignments demonstrate the basic relationship between `fork()`, `exec()`, and `wait()`.

- `fork()` creates a new child process.
- `fork()` returns `0` in the child and a positive child PID in the parent.
- `execl()` replaces the current process with another program.
- `wait()` allows the parent to wait for a child process to finish.
- Multiple `fork()` calls can quickly create a hierarchy of many processes.
- The execution order of child processes is not guaranteed unless synchronization such as `wait()` is used.
