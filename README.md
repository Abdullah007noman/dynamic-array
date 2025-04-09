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
``` cpp
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
```
# Dynamic Table
The implementation includes methods for inserting and deleting elements, as well as resizing the underlying array when necessary. It also includes a demonstration function that shows how the table size, number of items, and load factor change as elements are inserted and deleted.

## a) Using the Aggregate Method
The aggregate method computes the amortized cost by dividing the total cost of a sequence of operations by the number of operations.
For a dynamic table with n insertions:

When the table doubles in size, we need to copy all existing elements
Doubling happens when the table size is 1, 2, 4, 8, ..., 2^k where k = ⌊log n⌋

For n insertions, the total cost is:

 * Basic insertion cost: n operations × O(1) = O(n)
 * Resizing cost: copying elements when doubling
   * 1 + 2 + 4 + 8 + ... + 2^k = 2^(k+1) - 1 < 2n

Therefore, the total cost is O(n), and the amortized cost per operation is O(n)/n = O(1).
## b) Using the Accounting Method
In the accounting method, we charge each operation a certain amount (the amortized cost) that may be higher than its actual cost. The excess payment is stored as "credit" that can be used to pay for more expensive operations later.
For our dynamic table:

 * We charge 3 units for each insertion operation:
    * 1 unit for the actual insertion
    * 2 units as credit for future table doubling
When the table needs to double:
 * If we've inserted i items, doubling requires copying i items
 * But we've accumulated 2i units of credit (2 units per insertion)
 * This credit exactly covers the cost of copying during expansion

For deletions (when implementing contraction):
* We can similarly charge a constant amount that covers both the deletion and potential resizing

This shows that with a constant amortized cost per operation (O(1)), we can cover all actual costs, even though individual operations might occasionally cost O(n) when resizing occurs.
The accounting method confirms that both insertions and deletions have O(1) amortized time complexity in a dynamic table that doubles in size when full and halves in size when it's 1/4 full, maintaining a bounded load factor.
