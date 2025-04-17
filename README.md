
# Custom Linux Shell in C

## Overview

This project implements a **custom shell environment in C** on Linux (Ubuntu), consisting of a main shell and three specialized sub-shells. Each sub-shell handles different categories of commands using low-level system calls (e.g., `fork`, `exec`, `open`, `read`, `write`). The shell replicates basic Linux functionality and introduces custom file manipulation features.

## Features

### Main Shell (`shell.c`)
- Displays an interactive prompt: `Shell$`
- Allows navigation to sub-shells: `shell1`, `shell2`, `shell3`
- Supports `exit` to quit the shell environment

### Sub-Shell 1 (`shell1.c`)
- Supports Linux commands **without parameters**, e.g., `ls`, `ps`, `date`, `clear`
- Includes a custom `history` command (shared with shell2)
- Uses `Esc` to return to the main shell

### Sub-Shell 2 (`shell2.c`)
- Supports Linux commands **with parameters**, e.g., `ls -l`, `mkdir mydir`, `grep -c hello a.txt`
- Includes a shared `history` command with shell1
- Uses `Esc` to return to the main shell

### Sub-Shell 3 (`shell3.c`)
- **File Editing Commands**:
  - `Merge file1 file2`: Prints alternating words from two files to `stdout`
  - `Merge file1 file2 file3`: Writes alternating words to `file3`
  - `Size file`: Displays the number of characters in the file
  - `Delete file`: Deletes the specified file
- Uses `Esc` to return to the main shell

## Technical Details

- Implemented using only **system calls**: `fork`, `exec`, `open`, `read`, `write`, `close`
- No usage of the `system()` function
- Command parsing and validation handled manually
- Custom `history` feature implemented using either a text file or a linked list

## File Structure

- `shell.c` – Main shell logic
- `shell1.c` – Shell for Linux commands without parameters
- `shell2.c` – Shell for Linux commands with parameters
- `shell3.c` – Shell for file operations (merge, size, delete)
- `history.c/.h` – Shared history implementation
- `Sys_shell.sh` – Bash script for compiling and running the project
- `doc.docx` – Report with student names and execution screenshots

## Compilation

Use the provided shell script (`Sys_shell.sh`) or compile manually:

```bash
cc shell.c -o shell
cc shell1.c -o shell1
cc shell2.c -o shell2
cc shell3.c -o shell3
```

## Running the Shell

```bash
./shell
```

Sample output:

```text
Enter <shell1> to run linux commands without parameters
Enter <shell2> to run linux commands with parameters
Enter <shell3> to run commands to file editing
Shell$ shell1
Shell1$ date
Wed Nov 20 14:04:14 IST 2019
Shell1$ Esc
Shell$ shell2
Shell2$ grep -c Hello a.txt
1
Shell2$ exit
Not Supported
Shell2$ Esc
Shell$ shell3
Shell3$ Merge a.txt b.txt
I Hello am World a student
Shell3$ Merge a.txt b.txt c.txt
Shell3$ Esc
Shell$ Exit
```

## Notes

- Incorrect usage or unsupported commands trigger appropriate error messages
- Only one sub-shell is active at any time
- Project adheres to Linux process and file management best practices

## License

This project is for educational purposes.
