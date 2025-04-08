# C++ Dynamic Array Implementation
This is a custom implementation of a dynamic array similar to std::vector in C++, built using only C-style arrays. The implementation demonstrates how vectors work internally with automatic memory management and resizing.
## Core Structure
The dynamic array is built with three main components:
 * A pointer to the raw array (int* array)
 * Current number of elements (size_t size)
 * Total allocated capacity (size_t capacity)
