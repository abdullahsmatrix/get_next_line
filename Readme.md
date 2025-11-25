📚 get_next_line

A project from the 42 curriculum that teaches how to read a file line-by-line, manage persistent state across function calls, and handle memory safely in C.

This project seems simple at first—"just return the next line"—but it introduces some of the most fundamental concepts in systems programming: buffers, static variables, heap allocation, pointer-to-pointer management, and handling multiple file descriptors.

🚀 Goal

Implement a function with the following prototype:

char *get_next_line(int fd);


Each call returns one line terminated by \n (or EOF), reading from a file descriptor using a buffer of size BUFFER_SIZE.

🧠 What This Project Teaches
### 1. Managing Dynamic Memory

Handling repeated malloc, free, and allocations of varying sizes

Preventing memory leaks

Avoiding double-free and dangling pointers

2. Using Static Variables

static char *stash; keeps leftover data between calls.

The tricky part was understanding why a pointer-to-pointer (char **) is needed inside functions that modify stash.
This project forces you to confront how C actually handles pass-by-value.

3. Reading in Chunks

read() does not guarantee:

reading full lines

reading until a newline

returning the entire file

or even reading the same number of bytes each call

This project teaches you how to build a predictable interface over an unpredictable system call.

4. Handling Edge Cases

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

5. Bonus: Multiple File Descriptors

The bonus requires supporting:

get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);


without mixing data between them.
This introduces deeper ideas:

arrays of static pointers (static char *stash[OPEN_MAX])

isolating state for each FD

careful cleanup logic

🏗️ How It Works
1. read_join()

Keeps reading into a buffer

Joins new data to the stash

Stops only when a newline is found or EOF is reached

2. extract_new_line()

Splits stash into:

the next full line to return

leftover that stays for next call

This part is where pointer-to-pointer logic becomes crucial.

📁 Files

get_next_line.c – main logic

get_next_line_utils.c – helper functions (strjoin, strdup, etc.)

get_next_line.h – prototypes and macros

get_next_line_bonus.c – multi-file-descriptor support

get_next_line_bonus.h – bonus header

🧪 Testing

I tested the implementation with:

Tripouille’s official test suite

custom edge-case files (empty, no newline, only newline, huge lines)

random input generators

valgrind (to ensure no leaks remain)

🧯 Challenges I Faced

Understanding when to free stash and when to keep it

Realizing buffer must be freed once, at the right time

The classic bug: returning NULL too early at EOF

Handling an empty leftover string ("") properly

Making extract_new_line modify the original stash using char **

Bonus: making sure stash is separate for each file descriptor

This project teaches you not just how to code, but how to think like someone writing a library function in C.

📜 Usage
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd))) {
    printf("%s", line);
    free(line);
}
close(fd);


Compile using:

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c


Or bonus:

cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils.c

Grade: 125% ✅
