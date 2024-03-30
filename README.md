# RPAL Interpreter

This repository contains an implementation of a RPAL Interpreter, which includes a lexical analyzer, parser, abstract syntax tree (AST) generation, conversion to Standardized Tree (ST), and a CSE machine. It is defined by lexical rules and grammar detailed in `RPAL_Lex.pdf` and `RPAL_Grammar.pdf` under `docs` respectively.

## Usage

The program can execute using the following

### C/C++
```
$ ./myrpal file_name
```

Replace `file_name` with the name of the file containing the RPAL program.



The following sequence of commands can be used in the root of the project directory
to compile the program and execute rpal programs:
```
> make
> ./rpal20 file_name
```
To generate the Abstract Syntax Tree:
```
> ./rpal20 -ast file_name
```
To generate the Standardized Tree:
```
> ./rpal20 -st file_name
```

### Required Switch

-   `-ast`: This switch prints the abstract syntax tree and nothing else.

## Input Format

The input RPAL program should adhere to the following format:

```
let Sum(A) = Psum (A,Order A ) 
where rec Psum (T,N) = N eq 0 -> 0
 | Psum(T,N-1)+T N
in Print ( Sum (1,2,3,4,5) ) 
```

## Output Format

When the `-ast` switch is used, the output format should match the following:

```
let
.function_form
..<ID:Sum>
..<ID:A>
..where
...gamma
....<ID:Psum>
....tau
.....<ID:A>
.....gamma
......<ID:Order>
......<ID:A>
...rec
....function_form
.....<ID:Psum>
.....,
......<ID:T>
......<ID:N>
.....->
......eq
.......<ID:N>
.......<INT:0>
......<INT:0>
......+
.......gamma
........<ID:Psum>
........tau
.........<ID:T>
.........-
..........<ID:N>
..........<INT:1>
.......gamma
........<ID:T>
........<ID:N>
.gamma
..<ID:Print>
..gamma
...<ID:Sum>
...tau
....<INT:1>
....<INT:2>
....<INT:3>
....<INT:4>
....<INT:5>
```

When the `-ast` switch is not used, the output format should display the result of the RPAL program execution:

`Output of the above program is:
15` 

## Components

1.  **Lexical Analyzer**: Tokenizes the input RPAL program.
2.  **Parser**: Parses the tokens and constructs the abstract syntax tree (AST).
3.  **Abstract Syntax Tree (AST)**: Represents the parsed program as a tree structure.
4.  **Standardized Tree (ST)**: Converts the AST into a standardized tree.
5.  **CSE Machine**: Executes the RPAL program.

## Contributors

- Niruksha Sandeepa [@NirukshaSandeepa](https://www.github.com/NirukshaSandeepa)
- Lakshani Manamperi [@LRManamperi](https://www.github.com/LRManamperi)

## License

This project is licensed under the MIT License
