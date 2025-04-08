# C++ Dynamic Array Implementation
This is a custom implementation of a dynamic array similar to std::vector in C++, built using only C-style arrays. The implementation demonstrates how vectors work internally with automatic memory management and resizing.
## Core Structure
The dynamic array is built with three main components:
 * A pointer to the raw array (int* array)
 * Current number of elements (size_t size)
 * Total allocated capacity (size_t capacity)
# Key Features
## Memory Management

 * Dynamic allocation: Uses malloc, realloc, and free for memory management
 * Growth strategy: Doubles capacity when full to ensure amortized O(1) append operations
 * Resource cleanup: Proper deallocation to prevent memory leaks

## Operations

 * createDynamicArray - Initializes a new dynamic array with specified capacity
 * pushBack - Adds elements to the end (with automatic resizing)
 * popBack - Removes the last element
 * at - Bounds-checked element access
 * set - Updates element values
 * insert - Adds element at arbitrary position
 * erase - Removes element at arbitrary position
 * shrinkToFit - Optimizes memory usage by reducing capacity

## Performance Characteristics

 * Element access: O(1)
 * Add/remove at end: Amortized O(1)
 * Insert/erase in middle: O(n)
 * Memory overhead: Less than 2x the space needed for elements
## Example Usage
cpp
// Create with initial capacity
DynamicArray* da = createDynamicArray(2);

// Add elements
pushBack(da, 10);
pushBack(da, 20);
pushBack(da, 30);  // Will trigger resize

// Access elements
int value;
at(da, 1, &value);  // value = 20

// Insert and remove
insert(da, 1, 15);  // [10, 15, 20, 30]
erase(da, 2);       // [10, 15, 30]

// Clean up
freeDynamicArray(da);
