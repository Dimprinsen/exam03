FUNCTION ft_popen(file, argv, type) RETURNS file_descriptor

PURPOSE:
  Execute a program as a subprocess and create a pipe for communication.
  Similar to the standard library's popen(), but simpler.

PARAMETERS:
  - file: Name of the program to execute
  - argv: Array of arguments to pass to the program (must end with NULL)
  - type: 'r' = read from program's output, 'w' = send input to program

PROCESS:

1. VALIDATION
   IF file is NULL OR argv is NULL OR (type is 'r' AND type is 'w')
     RETURN error (-1)

2. CREATE PIPE
   Create a pipe with two file descriptors:
     - fd[0]: read end
     - fd[1]: write end

3. FORK PROCESS
   pid = fork()
   
   CHILD PROCESS (pid == 0):
   ├── IF type == 'r':
   │   Redirect stdout (FD 1) → pipe write end (fd[1])
   │   (child's output will go through the pipe)
   │
   ├── IF type == 'w':
   │   Redirect stdin (FD 0) → pipe read end (fd[0])
   │   (child will read from the pipe)
   │
   ├── Close both pipe file descriptors
   │   (child has duplicated them, originals not needed)
   │
   └── Execute the program using argv
       If execution fails, exit(1)

   PARENT PROCESS (pid > 0):
   ├── IF type == 'r':
   │   Close pipe write end (fd[1])
   │   RETURN read end (fd[0])
   │   (parent reads what child outputs)
   │
   └── IF type == 'w':
       Close pipe read end (fd[0])
       RETURN write end (fd[1])
       (parent writes what child reads)

RETURN VALUE:
  - File descriptor to communicate with the subprocess
  - Parent can read from or write to this FD depending on type
  - -1 on error

Key Concepts:
Pipe: Allows inter-process communication. Data written to fd[1] can be read from fd[0].

Fork: Creates a child process. Both parent and child continue executing.

dup2: Duplicates a file descriptor to a standard stream:

dup2(fd[1], 1) → redirect stdout to the pipe's write end
dup2(fd[0], 0) → redirect stdin to the pipe's read end
Type 'r' (Read):

Parent reads from subprocess's output
Child writes stdout to pipe → parent reads from pipe
Type 'w' (Write):

Parent sends data to subprocess's input
Parent writes to pipe → child reads from stdin