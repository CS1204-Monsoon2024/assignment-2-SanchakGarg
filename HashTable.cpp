#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    int bucketCount; // number of buckets
    int elementCount; // current number of elements
    int* table; // array for storing key-value pairs

public:
    HashTable(int initialSize) {
        bucketCount = initialSize; 
        elementCount = 0; 
        table = new int[bucketCount]; 
        fill_n(table, bucketCount, -1);
    }

    // Resize table
    void resize() {
        int newBucketCount = nextPrime(2 * bucketCount); 
        int* newTable = new int[newBucketCount]; 
        fill_n(newTable, newBucketCount, -1); 

        for (int i = 0; i < bucketCount; i++) {
            if (table[i] != -1) {
                int key = table[i];
                int newIndex = key % newBucketCount;

                if (newTable[newIndex] == -1) {
                    newTable[newIndex] = key; 
                } else {
                    for (int j = 1; j < newBucketCount; j++) {
                        int newIndexProbing = (newIndex + j * j) % newBucketCount;

                        if (newTable[newIndexProbing] == -1) {
                            newTable[newIndexProbing] = key; 
                            break; 
                        }
                    }
                }
            }
        }

        delete[] table; 
        table = newTable; 
        bucketCount = newBucketCount; 
    }

    // Print table
    void printTable() {
        for (int i = 0; i < bucketCount; i++) {
            cout << (table[i] == -1 ? "- " : to_string(table[i]) + " ");
        }
        cout << endl; 
    }

    // Remove key
    void remove(int key) {
        int index = key % bucketCount;

        if (table[index] == key) {
            table[index] = -1; 
            elementCount--; 
            return; 
        } else {
            int originalIndex = index; 

            for (int i = 1; (index + i * i) % bucketCount != originalIndex; i++) {
                int newIndex = (index + i * i) % bucketCount;

                if (table[newIndex] == key) {
                    table[newIndex] = -1; 
                    elementCount--; 
                    return; 
                }
            }
        }
        cout << "Element not found" << endl; 
    }

    // Search key
    int search(int key) {
        int index = key % bucketCount;

        if (table[index] == key) {
            return index; 
        } else {
            for (int i = 1; (index + i * i) % bucketCount != index; i++) {
                int newIndex = (index + i * i) % bucketCount;

                if (table[newIndex] == -1) {
                    return -1; 
                }

                if (table[newIndex] == key) {
                    return newIndex; 
                }
            }
        }
        return -1; 
    }

    // Insert key
    void insert(int key) {
        float loadFactor = static_cast<float>(elementCount) / bucketCount;

        if (loadFactor >= 0.8) {
            resize();
        }

        int index = key % bucketCount;

        if (table[index] == key) {
            cout << "Duplicate key insertion is not allowed" << endl; 
            return; 
        }

        if (table[index] == -1) { 
            table[index] = key; 
            elementCount++; 
            return; 
        } else {
            for (int i = 1; i < bucketCount; i++) {
                int newIndex = (index + i * i) % bucketCount;

                if (table[newIndex] == key) {
                    cout << "Duplicate key insertion is not allowed" << endl; 
                    return; 
                }

                if (table[newIndex] == -1) {
                    table[newIndex] = key; 
                    elementCount++; 
                    return; 
                }
            }
        }

        cout << "Max probing limit reached!" << endl; 
    }

    // Prime checking
    bool isPrime(int num) {
        if (num <= 1) return false; 
        if (num == 2 || num == 3) return true; 
        if (num % 2 == 0 || num % 3 == 0) return false; 

        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false; 
        }
        return true; 
    }

    // Next prime
    int nextPrime(int n) {
        int candidate = n; 

        while (!isPrime(candidate)) {
            candidate++; 
        }
        return candidate; 
    }
};
