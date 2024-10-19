#include <iostream>

class HashTable {
private:
    int* table;
    int size;
    int count;
    int EMPTY = -1;
    int DELETED = -2;

    int nextPrime(int n) {
        while (!isPrime(n)) {
            ++n;
        }
        return n;
    }

    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int hash(int key) {
        return key % size;
    }

    int quadraticProbing(int key, int i) {
        return (hash(key) + i * i) % size;
    }

    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2);
        int* oldTable = table;
        table = new int[size];
        for (int i = 0; i < size; ++i) table[i] = EMPTY;
        count = 0;

        for (int i = 0; i < oldSize; ++i) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);
            }
        }
        delete[] oldTable;
    }

    double loadFactor() {
        return (double)count / size;
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = new int[size];
        for (int i = 0; i < size; ++i) table[i] = EMPTY;
        count = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (loadFactor() > 0.8) {
            resize();
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

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = DELETED;
            count--;
        }
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == EMPTY) {
                std::cout << "- ";
            } else if (table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
