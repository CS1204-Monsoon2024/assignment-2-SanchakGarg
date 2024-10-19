#include <iostream>

class HashTable {
private:
    int* table;    // The array representing the hash table
    int size;      // The size of the hash table
    int count;     // Number of elements currently in the table
    const int EMPTY = -1;   // Indicates an empty cell
    const int DELETED = -2; // Indicates a deleted cell

    // Helper function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            ++n;
        }
        return n;
    }

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Hash function: h(k) = k mod size
    int hash(int key) {
        return key % size;
    }

    // Quadratic probing function: (h(k) + i^2) % size
    int quadraticProbing(int key, int i) {
        return (hash(key) + i * i) % size;
    }

    // Resizes the hash table when the load factor exceeds 0.8
    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2);  // Get the next prime number as the new size
        int* oldTable = table;       // Save the old table
        table = new int[size];       // Create a new table with the new size

        for (int i = 0; i < size; ++i) {
            table[i] = EMPTY;        // Initialize the new table to all empty
        }

        count = 0;

        // Rehash all elements from the old table
        for (int i = 0; i < oldSize; ++i) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);  // Reinsert elements into the new table
            }
        }

        delete[] oldTable;  // Free the old table memory
    }

    // Returns the current load factor
    double loadFactor() {
        return (double)count / size;
    }

public:
    // Constructor: Initializes the hash table with a given initial size
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = new int[size];
        for (int i = 0; i < size; ++i) {
            table[i] = EMPTY;  // Set all cells to empty
        }
        count = 0;
    }

    // Destructor: Frees the allocated memory
    ~HashTable() {
        delete[] table;
    }

    // Inserts a key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (loadFactor() > 0.8) {
            resize();  // Resize the table if load factor exceeds 0.8
        }

        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == EMPTY || table[index] == DELETED) {
                table[index] = key;
                count++;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    // Searches for a key in the hash table and returns its index, or -1 if not found
    int search(int key) {
        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == EMPTY) {
                return -1;
            }
            if (table[index] == key) {
                return index;
            }
            i++;
        }
        return -1;
    }

    // Removes a key from the hash table
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = DELETED;
            count--;
        }
    }

    // Prints the current state of the hash table
    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
