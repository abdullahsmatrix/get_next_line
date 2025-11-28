# 📚 get_next_line

**get_next_line** is a project from the 42 curriculum focused on reading a file **line-by-line**, managing **persistent state** across function calls, and handling **memory safely** in C.

Although the goal seems simple—“return the next line”—the project introduces fundamental systems-programming concepts such as buffering, static variables, heap allocation, pointer manipulation, and handling multiple file descriptors.

---

## 🚀 Goal of the Project

Implement the function:
```c
char *get_next_line(int fd);
```
Each call should return one complete line, ending with `\n` when present, until EOF is reached.

Reading must be performed using a buffer of size `BUFFER_SIZE`, either predefined or user-defined.

---

## 🧠 What This Project Teaches

### 1. Managing Dynamic Memory

- Using `malloc` and `free` repeatedly and safely.  
- Avoiding memory leaks.  
- Preventing double-free and dangling pointers.

### 2. Using Static Variables

The function keeps leftover data between calls:

```c
static char *stash;
```

This introduces:  
- The purpose of static storage.  
- Why modifying `stash` often requires `char **`.  
- Understanding pass-by-value in C.

### 3. Reading in Chunks

`read()` does **not** guarantee:
- Reading a full line.
- Stopping at a newline.
- Returning consistent byte counts.
- Returning the entire file.

You must build predictable behavior on top of this inconsistent system call.

### 4. Handling Edge Cases

Important edge cases include:
- Files with no newline.
- Files ending with a newline.
- Empty files.
- Very small or very large `BUFFER_SIZE`.
- Multiple consecutive `\n`.
- Leftover becoming an empty string (`""`).

This project teaches you to avoid issues like:
- Infinite loops.
- Premature EOF.
- Returning `NULL` too early.
- Segmentation faults due to pointer misuse.

### 5. Bonus: Multi-FD Support

GNL function to support multiple file descriptors:

```c
static char *stash[OPEN_MAX];
```

The bonus includes:
- Tracking state independently for each FD.
- Preventing data mixing.
- Careful cleanup logic.

---

## 🏗️ How It Works

1. **Initial Call**  
   `get_next_line(fd)` validates the input and prepares internal state.

2. **read_join()**  
   Repeatedly reads into a buffer -> Appends new data to stash -> Stops when a newline or EOF is encountered.

3. **extract_new_line()**  
   Splits the stored data into:
   - A full line (returned to the user)
   - Leftover data (saved for the next call)

   This step often requires pointer-to-pointer logic to safely update `stash`.

---

## 🧯 Challenges I Faced

- Understanding when to free `stash` and when to retain it.
- Ensuring the buffer is freed at exactly the right moment.
- Avoiding premature `NULL` return at EOF.
- Correctly handling an empty leftover string.
- Making `extract_new_line()` modify the original stash.
- Bonus: isolating `stash` for each file descriptor.

This project teaches not only coding, but also how to think like you're implementing a C library function. It involves brainstorming to solve problems, aligning variables, functions, loops, and conditions so that they work as expected.

---

## 🏅 Grade

**125% ✅**

---

## 🤖 Gen AI Usage

- Used mainly for edge-case verification
- Vibecode usage: 5%
