# Minishell Project Documentation

## 1. Prompt and Command Execution

**Approach:** We implemented a REPL (Read-Eval-Print Loop) system to continuously accept user input, tokenize commands, and execute tasks based on user-defined operators like pipes and redirection.

**Key Steps:**
- **Session Initialization:** Initialization of the main session structure manages each command input's state, including tokens, commands, pipes, and operators.
- **Processing the Input Line:** Each input line is processed by tokenizing, applying operator rules, and managing pipes, redirections, and documents as needed.
- **Task Execution:** Commands and sub-commands are executed sequentially, with dependencies managed for pipes and conditional execution.

## 2. Tokenization and Parsing

**Approach:** To interpret commands, we parse the input line for symbols such as `$`, `|`, `'`, or `"`.
We create, classify and manage tokens to represent each command segment.

**Key Steps:**
- **Token Generation:** The system splits the line into tokens, handles string expansions (e.g., environment variables), and contracts strings when quotes are closed.
- **Error Handling:** Syntax errors are detected early, with checks for unsupported or misplaced special characters.


## 3. Pipe and Redirection Handling

**Approach:** We implemented dynamic pipe allocation and management to enable inter-process communication efficiently.

**Key Steps:**
- **Pipe Allocation:** Memory for pipes is allocated dynamically based on the number of tasks in a command sequence.
- **Syntax and Logical Validation:** Redirections (`<`, `>`, `|`) are validated for syntax and logical correctness, with error handling for invalid configurations.
- **Pipeline Execution:** Commands are executed sequentially in the pipeline, passing output from one command as input to the next.

## 4. Signal Management

**Approach:** Custom signal handlers manage interruptions gracefully, handling signals like `SIGINT` and `SIGQUIT` to prevent shell crashes.

**Key Steps:**
- **Signal Ignoring:** Specific signals are ignored during command execution to avoid unexpected termination.
- **Custom Handlers:** Custom actions for received signals help maintain the shell’s consistent state, even when interrupted.

## 5. Execution of Binaries and Built-ins

**Approach:** Our execution model allows for both built-in commands and external binaries to be run in the shell.

**Key Steps:**
- **Path Resolution:** Paths for executable binaries are resolved, checking their existence in the system’s `PATH`.
- **Error Messaging:** Informative error messages are provided to the user when execution fails.
- **Directory Detection:** Directories are validated to prevent mistaken execution as binaries, enhancing reliability.


This project was developed by @iurilandolt and @rogerccs