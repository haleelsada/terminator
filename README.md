# terminator
A group of cool 3D stimulation programs that can be run in terminal.

## Contents

- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)

## Introduction

This repository contains the following 3D animations:
most of them are just tweaking the original work.
- Spinning Donut in python
- Spinning Donut in C (By [Andy Sloane](https://www.a1k0n.net/2011/07/20/donut-math.html) )
- Spinning Cube in C (By [Servet Gulnaroglu](https://www.youtube.com/watch?app=desktop&v=p09i_hoFdd0))
- Spinning hollow cube in C
- Spinning Cube with light effect in C
- Spinning cube illusion in C
- Spinning Tetrahedron in C
  

Each program is designed to run in the terminal, providing a simple yet captivating visual experience.

## Prerequisites

To compile and run these programs, you will need:
- A C compiler (e.g., `gcc` installed default in most linux distros)
- A terminal emulator that supports ASCII output


## Usage

To run the programs, two ways:

1. Clone this repository:
    ```sh
    git clone https://github.com/haleel/terminator.git
    cd terminator
    // If C file
    gcc name-of-the-file-wanted-to-run.c -lm
    ./a.out
    // If python
    python3 name-of-file.py
    ```
    eg:
   ```
    // If C file
    gcc cube.c -lm
    ./a.out
    // If python
    python3 donut.py
   ```
   

2. Copy the file wanted to run from this repo and paste it to a new file created in local system:
    ```sh
    // If C file
    gcc name-of-the-file-wanted-to-run.c -lm
    ./a.out
    // If python
    python3 name-of-file.py
    ```
    eg:
   ```
    // If C file
    gcc cube.c -lm
    ./a.out
    // If python
    python3 donut.py
   ```
## Examples

### Spinning Donut
![Spinning Donut](example_images/spinning_donut.gif)

### Spinning Cube
![Spinning Cube](example_images/spinning_cube.gif)

### Spinning Hollow Cube
![Spinning Hollow Cube](example_images/spinning_hollow_cube.gif)

### Spinning Tetrahedron
![Spinning Tetrahedron](example_images/spinning_tetrahedron.gif)

## Contributing

Contributions are welcome! If you have an idea for a new 3D shape or an improvement to an existing one, please feel free to fork this repository and submit a pull request.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. You are free to use the code for personal purposes, but you are not allowed to distribute or commercialize it.

[Read the full license here](https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode).

