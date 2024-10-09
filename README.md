# cub3D

## **Project Description**

cub3D is a project that implements a simple 3D engine, inspired by the game (*Wolfenstein 3D*). The project is part of the Ecole 42 educational program. The goal is to understand the basics of 3D rendering, such as raycasting, and user interaction.

## **Project Structure**
```
cub3D/
├── includes
│   └── cub3D.h
├── Makefile
├── README.md
└── src
    ├── main.c
    └── player
        └── init.c
```

- **Makefile**: Script for automating project compilation.
- **includes/**: Folder containing header file `cub3D.h`.
- **minilibx-linux/**: Graphics library for rendering, cloned automatically.
- **src/**: Project source files.
- **obj/**: Object files generated during compilation.

## **Requirements**

To compile and run the project, you need:

- **CC** `cc` compiler
- **make**
- **X11** library with dependencies

## **Compilation**

To compile the project, run the following command in the terminal:

```
make
```

The project will be compiled, and the executable file `cub3D` will be created.

## **Running**

To run the program, use the following command:

```
./cub3D maps/<name_map>.cub
```

## **Cleaning Files**

To remove object files, you can use:

```
make clean
```

To also remove the executable file, use:

```
make fclean
```

To recompile the project from scratch, use:

```
make re
```

## **Contact**

If you have any questions or would like to get in touch regarding the project, you can reach out on LinkedIn: [Radoslaw Grochowski](https://www.linkedin.com/in/radoslaw-grochowski/)

<u>**Important Note:**</u> Make sure to install all dependencies before running the program.

