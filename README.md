# Minishell

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <div class="header-container">
        <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/covers/cover-minishell-bonus.png" width="400" alt="Imagem 1"/>
        <img src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExZHoyeW15YWlhYjc2YjRsYmVodWtiM2p5anA0eHdyOTdqNWsweDNjZSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/cZUo8CgKF5lfQTOYQP/giphy.webp" width="200" alt="Imagem 2"/>
    </div>
</body>
</html>


<h1 align="center">Your own shell form scratch</h1>

This repository contains the files for the Minishell project, developed in collaboration with [alisson marcos](https://github.com/alissonmarcs)
## About
This project requires the development of a mini shell based on Bash. The program should handle basic functionalities similar to those of Bash, including:

- Command Execution: Execute basic commands and programs.
- Built-in Commands: Support for essential built-in commands such as cd, exit, pwd, echo (with the -n option), export, and import.
- Signal Handling: Manage signals for process control.

## Requirements
The functions are written in __C language__ and need the `gcc` compiler.

## Instructions

### 1. Compiling the archives

To compile the project, go to its path and run:

For __mandatory__ functions:
```
$ make
```
### 2. Cleaning all binary (.o) and executable files (.a)

To delete all files generated with make, go to the path and run:
```
$ make fclean
```
## Testing
This function have been tested with (https://github.com/LucasKuhn/minishell_tester).
