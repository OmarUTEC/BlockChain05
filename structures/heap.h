#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

const enum Type { MAX_HEAP, MIN_HEAP };

// template <typename T, enum Type>
template <typename T, Type heapType>
class Heap
{
private:
    T *elements;
    int capacity;//capacidad maxima del arbol
    int n;//cantidad de elementos en el arbol
    Type type;

public:
    Heap() = default;
    Heap(T *elements, int n, Type type=MAX_HEAP) : elements(elements), n(n), type(type)
    {
        buildFromArray(elements, n);
    }

    Heap(int capacity, Type type=MAX_HEAP) : capacity(capacity), type(type)
    {
        this->elements = new T[capacity];
        this->n = 0;
    }

    ~Heap(){ 
        delete [] this->elements;
    }

    void buildFromArray(T *elements, int n){
    for (int i = 0; i < n; i++){
        push(elements[i]);
        }  
    }

    int size()
    {
        return n;
    }

    bool is_empty()
    {
        //verificar si el arbol esta vacio
        if (n == 0){
            return true;
        }
        else{
            return false;
        }
    }

    void push(T value)
    {
        // agregar un elemento al arbol
        if (n < capacity){
            elements[n] = value;
            heapify_up(n);
            n++;
        }
        else if (n == capacity){
            //Redimensionamos:
            T *arr2 = new T[capacity*2];
            for (int i = 0; i < capacity; i++){
                arr2[i] = elements[i];
            }
            delete [] elements;
            elements = arr2;
            capacity = capacity*2;
            elements[n] = value;
            heapify_up(n);
            n++;
        }
    }

    T pop()
    {
        // eliminar un elemento del arbol
            T aux = elements[0];
            elements[0] = elements[n-1];
            n--;
            heapify_down(0);
            return aux;
    }

    T top()
    {
        //devuelve el elemento de la raiz
        return elements[0];
    }

    vector<T> extractTheTopK(int k){
        //devuelve un vector con los k elementos mas grandes o mas pequeños,
        // dependiendo del tipo de heap
        vector<T> topk;
        if (k > n){//no se puede extraer mas elementos de los que hay
            throw runtime_error("The heap has less elements than k");
        }
        else{
            if (type == MAX_HEAP){
                for (int i = 0; i < k; i++){
                    topk.push_back(pop());
                }
            }
            else{
                for (int i = 0; i < k; i++){
                    topk.push_back(pop());
                }
            }
        }
        return topk;
    }

    static void sortAsc(T* arr, int n){
        // Construimos un Max Heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extraemos los elementos uno a uno del heap en orden descendente
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);  // Movemos el elemento máximo al final
            heapify(arr, i, 0);    // Ajustamos el subárbol reducido
        }
    }
    
    //Funcion auxiliar para sortAsc
    static void heapify(T* arr, int n, int i) {
        int largest = i;        // Inicializamos el nodo raíz como el más grande
        int left = 2 * i + 1;   // Índice del hijo izquierdo
        int right = 2 * i + 2;  // Índice del hijo derecho

        // Si el hijo izquierdo es más grande que la raíz
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // Si el hijo derecho es más grande que la raíz
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // Si el mayor no es la raíz, intercambiamos y volvemos a ajustar
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
    }
}        
    static void minheapify(T* arr, int n, int i) {
        int smallest = i;     // Inicializar el índice más pequeño como la raíz
        int left = 2 * i + 1; // Índice del hijo izquierdo
        int right = 2 * i + 2; // Índice del hijo derecho

        // Si el hijo izquierdo es más pequeño que la raíz
        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }

        // Si el hijo derecho es más pequeño que el más pequeño hasta ahora
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }

        // Si el más pequeño no es la raíz, intercambiar y aplicar minheapify al subárbol afectado
        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            minheapify(arr, n, smallest);
        }
    }

    static void sortDesc(T* arr, int n){
        // Construir el min heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            minheapify(arr, n, i);
        }

        // Extraer los elementos del heap en orden ascendente
        for (int i = n - 1; i > 0; i--) {
            // Intercambiar el elemento raíz (mínimo) con el último elemento sin ordenar
            std::swap(arr[0], arr[i]);

            // Aplicar minheapify al subárbol reducido
            minheapify(arr, i, 0);
        }
    }


private:
    int Parent(int i)
    {
        return (i - 1) / 2;
    }

    int Left(int i)
    {
        return (2 * i + 1);
    }

    int Right(int i)
    {
        return (2 * i + 2);
    }

    void heapify_down(int i)
    {
        if (type == MAX_HEAP){
            if (elements[Left(i)] > elements[i] && elements[Left(i)]>=elements[Right(i)] && Left(i) < n){
                swap(elements[Left(i)], elements[i]);
                heapify_down(Left(i));
            }
            if (elements[Right(i)] > elements[i] && elements[Right(i)]>=elements[Left(i)] && Right(i) < n){
                swap(elements[Right(i)], elements[i]);
                heapify_down(Right(i));
            }
        }
        else{
            if (elements[Left(i)] < elements[i] && elements[Left(i)]<=elements[Right(i)] && Left(i) < n){
                swap(elements[Left(i)], elements[i]);
                heapify_down(Left(i));
            }
            if (elements[Right(i)] < elements[i] && elements[Right(i)]<=elements[Left(i)] && Right(i) < n){
                swap(elements[Right(i)], elements[i]);
                heapify_down(Right(i));
            }
        }
       //throw ("Function not implemented"); 
    }

    void heapify_up(int i)
    { 
        if (type == MAX_HEAP){
            if (elements[Parent(i)] < elements[i] && i > 0){
                swap(elements[Parent(i)], elements[i]);
                heapify_up(Parent(i));
            }
        }
        else{
            if (elements[Parent(i)] > elements[i] && i > 0){
                swap(elements[Parent(i)], elements[i]);
                heapify_up(Parent(i));
            }
        }
    }
};