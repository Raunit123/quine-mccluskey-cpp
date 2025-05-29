Quine-McCluskey Minimizer
This project implements the Quine-McCluskey algorithm to simplify Boolean functions by finding the minimal sum-of-products expression for a given set of minterms. The program is written in C++17 and uses CMake for building.
Overview
The Quine-McCluskey algorithm is a method for minimizing Boolean functions, particularly useful in digital logic design for simplifying truth tables or logic circuits. Given a number of variables and a list of minterms (where the function evaluates to 1), the program outputs the simplified Boolean expression as a set of prime implicants in binary form (e.g., "00-" for a 3-variable term where the first two variables are 0 and the third is a "don't care").
Features

Accepts user input for the number of variables and minterms.
Validates input to ensure minterms are within the valid range for the given number of variables.
Outputs minimized Boolean expression terms in binary format.
Handles errors gracefully with informative messages.

Prerequisites

C++ Compiler: A C++17-compatible compiler (e.g., Apple Clang 16.0.0, GCC, or Clang).
CMake: Version 3.10 or higher.
Operating System: Compatible with macOS, Linux, or Windows (with a suitable build environment like MinGW or MSYS2 on Windows).

Project Structure
quine_mccluskey_minimizer/
├── include/
│   └── qm.hpp          # Header file with QuineMcCluskey class and Term struct
├── src/
│   ├── main.cpp        # Main program with user input and output
│   └── qm.cpp          # Implementation of the Quine-McCluskey algorithm
├── CMakeLists.txt      # CMake configuration file
└── README.md           # This file

Building the Project

Navigate to the project directory:
cd quine_mccluskey_minimizer


Create a build directory:
mkdir build
cd build


Run CMake:
cmake ..


Compile the program:
make

This generates an executable named qm in the build directory.


Running the Program

Execute the program:
./qm


Provide input:

Number of variables: Enter an integer (e.g., 3 for variables A, B, C).
Minterms: Enter space-separated integers representing the minterms where the Boolean function is true (e.g., 0 1 2 4).
Example:Enter the number of variables: 3
Enter the minterms separated by spaces: 0 1 2 4




View output:

The program outputs the minimized Boolean function as a list of binary terms, where:
0 represents a negated variable (e.g., ¬A).
1 represents an unnegated variable (e.g., A).
- represents a "don't care" (variable can be 0 or 1).


Example output for the above input:Minimized Boolean function consists of 3 terms:
00-
0-0
-00

This corresponds to the Boolean expression: ¬A ∧ ¬B ∨ ¬A ∧ ¬C ∨ ¬B ∧ ¬C.



Input/Output Format

Input:
Number of variables: An integer ( n ), where ( 1 \leq n \leq 31 ), as minterms are stored as integers (limited by 32-bit integer size).
Minterms: A list of space-separated integers in the range [0, ( 2^n - 1 )]. Invalid minterms trigger an error.


Output:
A list of binary strings, each ( n ) bits long, representing the prime implicants of the minimized Boolean function.
Each string uses 0, 1, or - to denote the state of each variable.



Example
For 3 variables and minterms 0, 1, 2, 4:
Enter the number of variables: 3
Enter the minterms separated by spaces: 0 1 2 4
Minimized Boolean function consists of 3 terms:
00-   # ¬A ∧ ¬B (covers minterms 0, 1)
0-0   # ¬A ∧ ¬C (covers minterms 0, 2)
-00   # ¬B ∧ ¬C (covers minterms 0, 4)

Notes

The program uses the Quine-McCluskey algorithm to find all prime implicants and selects a minimal set (essential prime implicants plus additional implicants to cover all minterms).
The using namespace std; directive is used for simplicity, but be cautious when extending the project, as it may cause namespace conflicts in larger codebases.
For very large numbers of variables or minterms, performance may degrade due to the exponential complexity of the Quine-McCluskey algorithm.

Troubleshooting

Compilation Errors: Ensure all files (qm.hpp, qm.cpp, main.cpp) are in the correct directories (include/ and src/). Verify that your compiler supports C++17.
Invalid Input: If you see errors like "Minterm X is out of range," check that minterms are between 0 and ( 2^n - 1 ).
CMake Issues: Ensure CMake is installed (cmake --version). On macOS, you can install it via Homebrew: brew install cmake.

License
This project is provided as-is for educational purposes. Feel free to modify and distribute it as needed.
