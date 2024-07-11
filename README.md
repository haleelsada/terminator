![cube_hollow_](https://github.com/haleelsada/terminator/assets/75977159/f510da49-119f-45af-9d11-bfa6cb182391)![donut_c](https://github.com/haleelsada/terminator/assets/75977159/059bf1aa-5ac6-42df-999c-47ec3fb10cce)# terminator
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
- Static sphere in moving light
  

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
In c

![spinning donut](https://github.com/haleelsada/terminator/assets/75977159/e942e2dd-5f0a-4bc5-b003-8ab8d273dc08)

In Python

![donut_py](https://github.com/haleelsada/terminator/assets/75977159/8b5397ba-d8a9-41c6-bb23-eca634344575)

### Spinning Cube
![Spinning Cube](https://github.com/haleelsada/terminator/assets/75977159/6a254acb-1adb-4a35-8c22-a31f3842f40e)

### Spinning Hollow Cube
![cube_hollow_](https://github.com/haleelsada/terminator/assets/75977159/1bf7dc31-aecc-45ea-b7b3-50b37e594894)

### Spinning Cube Illusion
![cube_illusion_](https://github.com/haleelsada/terminator/assets/75977159/6214390e-ba7a-4e15-ab11-fff60c945658)

### Spinning Tetrahedron
![tetrahedron_](https://github.com/haleelsada/terminator/assets/75977159/ab78da21-61a2-40bb-bf7d-e074127a3ad8)

### Sphere with spinning light
![sphere_](https://github.com/haleelsada/terminator/assets/75977159/35df3b2e-005d-4fe1-b61b-bad10f8de8ab)

## Contributing

Contributions are welcome! If you have an idea for a new 3D shape or an improvement to an existing one, please feel free to fork this repository and submit a pull request.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. You are free to use the code for personal purposes, but you are not allowed to distribute or commercialize it.

[Read the full license here](https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode).

