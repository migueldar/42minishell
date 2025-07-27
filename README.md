# minishell

A minimal Unix shell implementation written in C, developed as part of the 42 School curriculum. It replicates key features of standard shells like bash and zsh, focusing on process management, parsing, and terminal control; all built from scratch without external parsing libraries.

## Features

- Prompt with interactive input
- Command execution with arguments and PATH resolution
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Pipes (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- Environment variable expansion (`$VAR`)
- Quote handling (`'`, `"`)
- Signal handling for `Ctrl-C` and `Ctrl-\`
- Command history

## Build & Run

```bash
git clone https://github.com/migueldar/42minishell
cd 42minishell
make
./minishell
