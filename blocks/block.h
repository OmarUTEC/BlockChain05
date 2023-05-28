#ifndef BLOCK_COMPONENT_H
#define BLOCK_COMPONENT_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include "../structures/heap.h"
#include "../structures/doubleList.h"
#include "../structures/chainHash.h"
#include "transaction.h"

using namespace std;

const int DIFFICULTY = 4;       // Número de ceros iniciales requeridos en el hash

// Definición de la estructura del bloque
struct Block {
    int index;                          // Índice del bloque en la cadena
    std::string timestamp;              // Marca de tiempo en la que se crea el bloque
    DoubleList<Transaction*>* data = new DoubleList<Transaction*>;
    ChainHash<string,Transaction*> data_hash;
    std::string previousHash;           // Hash del bloque anterior en la cadena
    std::string hash;                   // Hash del bloque actual
    int nonce = 0;                      // Número utilizado en la Prueba de Trabajo

 public:

    Block() = default;

    Block(int idx, string prevHash) {
        this->index = idx;
        this->timestamp = to_string(time(0));
        this->previousHash = prevHash;
        this->hash = calculateHash();
        mineBlock();
    }

    Block(const Block &other) {
        this->index = other.index;
        this->nonce = other.nonce;
        this->data = other.data;
        // this->maxFecha = other.maxFecha;
        // this->minFecha = other.minFecha;
        // this->maxMonto = other.maxMonto;
        // this->minMonto= other.minMonto;
        this->previousHash = other.previousHash;
        this->hash = other.hash;
    }

    
    void insert(Transaction* transaction) {

    }

    bool search(Transaction* transaction) {

    }


    std::string calculateHash() {
        std::stringstream ss;
        ss << index << timestamp << data << previousHash << nonce;
        std::string input = ss.str();

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)input.c_str(), input.length(), hash);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashStream << std::hex << (int)hash[i];
        }

        return hashStream.str()
    }


// Devuelve el heap de transacciones del menor monto como raiz
Heap<Transaction *, MIN_HEAP> minMonto() {
    
    Heap<Transaction *, MIN_HEAP> minMontoHeap;

    // Agrega transacciones al minHeap

    // Obtén la raíz del minHeap
    Transaction *rootTransaction = minMontoHeap.top();

    return minMontoHeap;
}

// Devuelve el heap de transacciones del mayor monto como raíz
Heap<Transaction *, MAX_HEAP> maxMonto() {
    Heap<Transaction *, MAX_HEAP> maxMontoHeap;
    
    // Obtén la raíz del minHeap
    Transaction *rootTransaction = maxMontoHeap.top();

    // Accede a los datos de la transacción raíz
    std::cout << "Root Transaction: ";
    rootTransaction->printTransaction();
    
    return maxMontoHeap;
}

// Devuelve el heap de transacciones del menor fecha como raiz
Heap<Transaction *, MIN_HEAP> minFecha() {
    
    Heap<Transaction *, MIN_HEAP> minFechaHeap;

    // Agrega transacciones al minHeap


    // Obtén la raíz del minHeap
    Transaction *rootTransaction = minFechaHeap.top();

    // Accede a los datos de la transacción raíz
    std::cout << "Root Transaction: ";
    rootTransaction->printTransaction();
    return minFechaHeap;
}

// Devuelve el heap de transacciones del mayor fecha como raíz
Heap<Transaction *, MAX_HEAP> maxFecha() {
    Heap<Transaction *, MAX_HEAP> maxFechaHeap;
    
    // Obtén la raíz del minHeap
    Transaction *rootTransaction = maxFechaHeap.top();

    // Accede a los datos de la transacción raíz
    std::cout << "Root Transaction: ";
    rootTransaction->printTransaction();
    
    return maxFechaHeap;
}

    ~Block() = default;
    
    // Calcula el hash del bloque actual y se compara con el hash objetivo
    // Si el hash actual no es igual al hash objetivo, se incrementa el nonce
    // -→ Prueba de Trabajo (Proof of Work)

    void mineBlock() {
        std::string target(DIFFICULTY, '0');
        while (hash.substr(0, DIFFICULTY) != target) {
            nonce++;
            hash = calculateHash();
        }
        std::cout << "Block mined: " << hash << std::endl;
    }

    void printBlock(Block block){
        std::cout << "Block Index N°: " << block.index << std::endl;
        //std::cout << "Timestamp: " << block.timestamp << std::endl; //
        std::cout << "Data: " << block.data << std::endl;
        std::cout << "Previous Hash: " << block.previousHash << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << std::endl;
    }
};

#endif // BLOCK_COMPONENT_H