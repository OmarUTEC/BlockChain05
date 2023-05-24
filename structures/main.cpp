#include <iostream>
#include "doubleList.h"
#include "heap.h"

using namespace std;

// Test Heap
int main() {
    // Crear un arreglo de elementos
    int arr[] = {5, 2, 8, 1, 10, 3};

    // Crear un objeto Heap con el arreglo
    Heap<int> heap(arr, sizeof(arr) / sizeof(arr[0]));

    // Imprimir el tamaño del Heap
    std::cout << "Tamaño del Heap: " << heap.size() << std::endl;

    // Imprimir el elemento superior del Heap
    std::cout << "Elemento superior del Heap: " << heap.top() << std::endl;

    // Insertar un nuevo elemento en el Heap
    heap.push(7);

    // Extraer y mostrar los 3 elementos principales del Heap
    std::cout << "Los 3 elementos principales del Heap: ";
    std::vector<int> top3 = heap.extractTheTopK(3);
    for (int num : top3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Ordenar el arreglo en orden ascendente utilizando Heap
    Heap<int>::sortAsc(arr, sizeof(arr) / sizeof(arr[0]));
    std::cout << "Arreglo ordenado en orden ascendente: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}


/*
// Test para doublelist

int main() {
    DoubleList<int> myList;

    // Agregar elementos a la lista
    myList.push_back(10);
    myList.push_front(5);
    myList.push_back(20);
    myList.push_front(2);

    // Imprimir los elementos de la lista
    std::cout << "Lista: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Eliminar un elemento de la lista
    myList.remove(2);

    // Insertar un elemento en una posición específica
    myList.insert(15, 1);

    // Imprimir los elementos de la lista después de las modificaciones
    std::cout << "Lista modificada: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Realizar operaciones adicionales
    std::cout << "Front: " << myList.front() << std::endl;
    std::cout << "Back: " << myList.back() << std::endl;
    std::cout << "Tamanio: " << myList.size() << std::endl;
    std::cout << "¿Esta vacia? " << (myList.is_empty() ? "Sí" : "No") << std::endl;

    // Ordenar la lista
    myList.sort();

    // Imprimir los elementos de la lista ordenada
    std::cout << "Lista ordenada: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Invertir la lista
    myList.reverse();

    // Imprimir los elementos de la lista invertida
    std::cout << "Lista invertida: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

*/