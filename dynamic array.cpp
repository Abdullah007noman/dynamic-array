#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;        // Pointer to the underlying array
    size_t size;       // Number of elements currently in the array
    size_t capacity;   // Total capacity of the array
} DynamicArray;

// Initialize a new dynamic array
DynamicArray* createDynamicArray(size_t initialCapacity) {
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!da) {
        return NULL;  // Memory allocation failed
    }
    
    da->array = (int*)malloc(initialCapacity * sizeof(int));
    if (!da->array) {
        free(da);
        return NULL;  // Memory allocation failed
    }
    
    da->size = 0;
    da->capacity = initialCapacity;
    return da;
}

// Free the dynamic array
void freeDynamicArray(DynamicArray* da) {
    if (da) {
        free(da->array);
        free(da);
    }
}

// Resize the underlying array
int resizeDynamicArray(DynamicArray* da, size_t newCapacity) {
    if (!da) return 0;
    
    int* newArray = (int*)realloc(da->array, newCapacity * sizeof(int));
    if (!newArray) {
        return 0;  // Memory allocation failed
    }
    
    da->array = newArray;
    da->capacity = newCapacity;
    return 1;
}

// Add an element to the end of the array
int pushBack(DynamicArray* da, int value) {
    if (!da) return 0;
    
    // If we're at capacity, resize
    if (da->size >= da->capacity) {
        size_t newCapacity = da->capacity * 2;  // Double the capacity
        if (!resizeDynamicArray(da, newCapacity)) {
            return 0;  // Resize failed
        }
    }
    
    da->array[da->size] = value;
    da->size++;
    return 1;
}

// Remove the last element
int popBack(DynamicArray* da) {
    if (!da || da->size == 0) return 0;
    
    da->size--;
    return 1;
}

// Get element at index
int at(DynamicArray* da, size_t index, int* value) {
    if (!da || index >= da->size) return 0;
    
    *value = da->array[index];
    return 1;
}

// Set element at index
int set(DynamicArray* da, size_t index, int value) {
    if (!da || index >= da->size) return 0;
    
    da->array[index] = value;
    return 1;
}

// Get current size
size_t size(DynamicArray* da) {
    return da ? da->size : 0;
}

// Get current capacity
size_t capacity(DynamicArray* da) {
    return da ? da->capacity : 0;
}

// Check if array is empty
int isEmpty(DynamicArray* da) {
    return da ? da->size == 0 : 1;
}

// Clear all elements
void clear(DynamicArray* da) {
    if (da) {
        da->size = 0;
    }
}

// Insert element at specific position
int insert(DynamicArray* da, size_t index, int value) {
    if (!da || index > da->size) return 0;
    
    // If we're at capacity, resize
    if (da->size >= da->capacity) {
        size_t newCapacity = da->capacity * 2;
        if (!resizeDynamicArray(da, newCapacity)) {
            return 0;  // Resize failed
        }
    }
    
    // Shift elements to the right
    for (size_t i = da->size; i > index; i--) {
        da->array[i] = da->array[i-1];
    }
    
    // Insert the new element
    da->array[index] = value;
    da->size++;
    return 1;
}

// Remove element at specific position
int erase(DynamicArray* da, size_t index) {
    if (!da || index >= da->size) return 0;
    
    // Shift elements to the left
    for (size_t i = index; i < da->size - 1; i++) {
        da->array[i] = da->array[i+1];
    }
    
    da->size--;
    return 1;
}

// Shrink capacity to fit size
int shrinkToFit(DynamicArray* da) {
    if (!da || da->capacity == da->size) return 1;
    
    // Don't resize if empty - keep some minimum capacity
    size_t newCapacity = da->size > 0 ? da->size : 1;
    return resizeDynamicArray(da, newCapacity);
}

// Example usage
int main() {
    // Create a dynamic array with initial capacity of 2
    DynamicArray* da = createDynamicArray(2);
    if (!da) {
        printf("Failed to create dynamic array\n");
        return 1;
    }
    
    // Add elements and observe automatic resizing
    printf("Adding elements...\n");
    for (int i = 0; i < 10; i++) {
        pushBack(da, i * 10);
        printf("Size: %zu, Capacity: %zu\n", size(da), capacity(da));
    }
    
    // Print all elements
    printf("\nElements: ");
    for (size_t i = 0; i < size(da); i++) {
        int value;
        at(da, i, &value);
        printf("%d ", value);
    }
    printf("\n");
    
    // Insert element at position 3
    insert(da, 3, 35);
    printf("\nAfter inserting 35 at position 3:\n");
    for (size_t i = 0; i < size(da); i++) {
        int value;
        at(da, i, &value);
        printf("%d ", value);
    }
    printf("\n");
    
    // Remove element at position 5
    erase(da, 5);
    printf("\nAfter removing element at position 5:\n");
    for (size_t i = 0; i < size(da); i++) {
        int value;
        at(da, i, &value);
        printf("%d ", value);
    }
    printf("\n");
    
    // Shrink to fit
    shrinkToFit(da);
    printf("\nAfter shrink to fit: Size: %zu, Capacity: %zu\n", size(da), capacity(da));
    
    // Free memory
    freeDynamicArray(da);
    return 0;
}