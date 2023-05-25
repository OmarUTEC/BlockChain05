#include <vector>
#include <list>

using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

template<typename TK, typename TV>
class ChainHash
{
private:    
    struct Entry{
		TK key;
		TV value;
		size_t hashcode;
        TK first;
	};
    list<Entry> *array;
	int capacity;//tamanio del array
    int size;//cantidad de elementos totales

public:
    ChainHash(){
		// TODO: asignar un tamanio inicial al array
		capacity = 10; 
		array = new list<Entry>[capacity];
		size = 0;
	}

	void set(TK key, TV value){
		if(fillFactor() >= maxFillFactor) rehashing();
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		//TODO: insertar el Entry(key, value) en index, manejando colisiones
        for (auto& entry : array[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        array[index].push_back(Entry{key, value, hashcode, key});
        size++;
	}

	TV get(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        for (auto& entry : array[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::out_of_range("La clave no existe en la tabla hash");
    };

    void remove(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        for (auto it = array[index].begin(); it != array[index].end(); ++it) {
            if (it->key == key) {
                array[index].erase(it);
                size--;
                return;
            }
        }
        throw std::out_of_range("La clave no existe en la tabla hash");
    };
    TV& operator[](TK key) {
        if (fillFactor() >= maxFillFactor) rehashing();
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        // buscar la entrada con la clave key en index, manejando colisiones
        for (auto& entry : array[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        // si la entrada no existe, agregarla al final de la lista
        array[index].push_back(Entry{key, TV(), hashcode});
        size++;
        return array[index].back().value;
    };

	//TODO: implementar el operador corchete [ ]
    int bucket_count() const {
        return capacity;
    }
    int bucket_size(unsigned n) const {
        return array[n].size();
    };
    using iterator = typename list<Entry>::iterator;
    iterator begin(unsigned n) {
        return array[n].begin();
    };
    iterator end(unsigned n){
        return array[n].end();
    }


private:
    double fillFactor(){
        return static_cast<double>(size) / (capacity * maxColision);
    }

    size_t getHashCode(TK key){
        std::hash<TK> ptr_hash;
        return ptr_hash(key);
    }

    void rehashing(){
        // Aumentar la capacidad del arreglo original
        int newCapacity = capacity * 2;
        list<Entry> *newArray = new list<Entry>[newCapacity];

        // Insertar todos los elementos del arreglo original en el nuevo arreglo
        for (int i = 0; i < capacity; i++) {
            for (auto entry : array[i]) {
                size_t hashcode = getHashCode(entry.key);
                int index = hashcode % newCapacity;
                newArray[index].push_back(entry);
            }
        }

        // Actualizar los campos de la clase con los nuevos valores
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    };
};