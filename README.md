# cppFileBuilder
`cppFileBuilder` is a C++ project template generator designed to streamline the creation of C++ class files, main.cpp, and Makefile. This tool helps you quickly set up a new C++ project with a consistent structure, reducing the time spent on boilerplate code.

## Features

- **Class File Generation**: Automatically generates `.hpp` and `.cpp` files for specified class names.
- **Main File Generation**: Optionally creates a `main.cpp` file.
- **Makefile Generation**: Optionally creates a `Makefile` for building the project.
- **Customizable Paths**: Allows specifying a custom directory for generated files.
- **Interactive Setup**: Provides an interactive setup process to guide you through file creation.
## Usage
### Command-Line Arguments
You can pass class names as command-line arguments to generate the corresponding `.hpp` and `.cpp` files:
```bash
./cppFileBuilder ClassName1 ClassName2 ClassName3
```

### Interactive Mode
If no command-line arguments are provided, the tool will enter interactive mode:
```bash
./cppFileBuilder
```
In interactive mode, you will be prompted to enter the class names, project name, and whether to create `main.cpp` and `Makefile`.

## Example
```shell
./cppFileBuilder MyClass AnotherClass
```
This will generate the following files:

- `MyClass.hpp`
- `MyClass.cpp`
- `AnotherClass.hpp`
- `AnotherClass.cpp`
- `main.cpp` (if specified)
- `Makefile` (if specified)

## Installation
1. Clone the repository:
    ```shell
    git clone https://github.com/JonatV/cppFileBuilder.git
    ```
2. Navigate to the project directory:
    ```shell
    cd cppFileBuilder
    ```
3. Build the project:
    ```shell
    make
    ```
4. Move to a Directory register in PATH (i.e):
    ```shell
    sudo mv cppFileBuilder /usr/bin/
    ```
5. And now it is accessible everywhere
    ```shell
    cppFileBuilder
    ```
## Wanna Help?
- Shell installer
- New features
- More security
- Cleaner functions

Contributions are welcome! Please fork the repository and submit a pull request with your changes.
