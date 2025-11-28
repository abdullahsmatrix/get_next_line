# 📚 get_next_line

A project from the 42 curriculum that teaches how to read a file line-by-line, manage persistent state across function calls, and handle memory safely in C.

This project seems simple at first—"just return the next line"—but it introduces some of the most fundamental concepts in systems programming: buffers, static variables, heap allocation, pointer-to-pointer management, and handling multiple file descriptors and so on.

# 🚀 Goal

Goal is to implement a function with the following prototype:
char *get_next_line(int fd);
Each call returns one line terminated by \n (or EOF), reading from a file descriptor using a pre-defined or user-defined buffer of size "BUFFER_SIZE".

# 🧠 What This Project Teaches
### 1. Managing Dynamic Memory

-> Handling repeated malloc, free, and allocations of varying sizes
-> Preventing memory leaks
-> Avoiding double-free and dangling pointers

### 2. Using Static Variables

-> static char *stash; keeps leftover data between calls.

The tricky part was understanding why a pointer-to-pointer (char **) is needed inside functions that modify stash.
This project forces you to confront how C actually handles pass-by-value.

### 3. Reading in Chunks

read() does not guarantee:

   -> reading full lines
   -> reading until a newline
   -> returning the entire file
   -> or even reading the same number of bytes each call

This project teaches you how to build a predictable interface over an unpredictable system call.

### 4. Handling Edge Cases

Some of the most challenging cases:

files with no newline

files that end with a newline

empty files

extremely small BUFFER_SIZE (e.g., 1)

extremely large BUFFER_SIZE

files containing multiple \n next to each other

leftover becoming an empty string ("")

These cases reveal subtle bugs such as:

infinite loops

premature EOF

returning NULL too early

segmentation faults due to pointer misuse

### 5. Bonus: Multiple File Descriptors

The bonus requires supporting multiple files open in multiple file descriptors without mixing data between them.
This introduces deeper ideas:

arrays of static pointers (static char *stash[OPEN_MAX])

isolating state for each FD

careful cleanup logic

# 🏗️ How It Works
### 1. Get_next_line is called & fd as an arguement is passed into teh function.
   The function checks for edge cases and correct validate arguement that is been passed.

### 2. read_join()
Keeps reading into a buffer
Joins new data to the stash
Stops only when a newline is found or EOF is reached

### 3. extract_new_line()
Splits stash into: i) the next full line to return
                  ii)leftover that stays for next call. 
This part is where pointer-to-pointer logic becomes crucial.

# 🧯 Challenges I Faced

Understanding when to free stash and when to keep it

Realizing buffer must be freed once, at the right time

The classic bug: returning NULL too early at EOF

Handling an empty leftover string ("") properly

Making extract_new_line modify the original stash using char **

Bonus: making sure stash is separate for each file descriptor

This project teaches you not just how to code, but how to think like someone writing a library function in C. Solving problem, keeping track all the variable, loop, conditions in line. 



# Compile using:

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c


Or bonus:

cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils.c

# Grade: 125% ✅

# Gen AI usage: 
Mostly for edge case checks. Vibecode: </> 5%






