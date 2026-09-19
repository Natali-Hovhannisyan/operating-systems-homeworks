# Homework 3 Report

## Assignment 1: Basic Process Creation with `fork()`

This program uses `fork()` to create one child process.

The child process prints its own PID using `getpid()`, while the parent also prints its own PID. Since the parent does not use `wait()`, the order of the two outputs is not guaranteed.

**Observation:** After `fork()`, both parent and child continue execution separately. The return value of `fork()` is `0` in the child and positive in the parent.

---

## Assignment 2: Using `wait()` and `waitpid()`

This program creates two child processes.

The first child prints its PID and exits with status `0`. The parent uses `wait()` to wait for it and then prints its exit status.

The second child is created afterward. The parent uses `waitpid()` with the second child's PID to wait specifically for that process.

**Observation:** `wait()` waits for a child process, while `waitpid()` can wait for a specific child. Both also allow the parent to collect the child's exit status.

---

## Assignment 3: Understanding `atexit()`

Two functions are registered using `atexit()`.

When `exit(0)` is called, the registered functions execute automatically before the program terminates. They run in reverse order of registration.

The line after `exit()` is never executed.

**Observation:** `atexit()` is useful for cleanup work that should happen before normal program termination, such as closing files or releasing resources.

---

## Assignment 4: Fork and Exit Status

The program creates two child processes.

The first child exits with status `1`, and the second exits with status `2`. The parent uses `waitpid()` to wait for each child separately.

`WIFEXITED()` checks whether the child exited normally, and `WEXITSTATUS()` retrieves its exit code.

**Observation:** Exit statuses allow the parent to determine how each child process finished.

---

## Assignment 5: Handling Zombie Processes

The program creates a child process that exits immediately, while the parent sleeps for 20 seconds without calling `wait()`.

During this time, the child was observed using `ps` and `htop` as a zombie process.

The child appeared with state `Z` and as `<defunct>` because it had finished but the parent had not collected its exit status yet.

**Observation:** Using `wait()` or `waitpid()` allows the parent to collect the child's termination information and prevents the child from remaining as a zombie process.

