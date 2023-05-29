#include <sstream>
using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;
const unsigned int PRIME_CONST = 31;

template<typename TK, typename TV>
class ChainHash {
private:    
    struct HashEntry {
        TK key;
        TV value;
        HashEntry* next = nullptr;   // puntero al siguiente HashEntry en caso de colisión

        HashEntry(const TK& key, TV value): key(key), value(value) {}

        HashEntry*& operator=(HashEntry* other) {
            HashEntry* temp = other;
            while (temp->next != nullptr) {
                this->key = temp->key;
                this->value = temp->value;
                temp = temp->next;
            }
        }
    };

    HashEntry** buckets;
    int capacity;              //tamanio del buckets
    int size;                  //cantidad de elementos totales

public:
    ChainHash() = default;
    ~ChainHash() = default;
    
    ChainHash(int capacity) {
        this->capacity = 10; 
        buckets = new HashEntry*[capacity];
        size = 0;
	}

    size_t hashFunction(TK key) {
        stringstream *skey = new stringstream;  
        skey << key;          // se llama a operator << para pasar a string
        string strkey = ss.str();
        int sum;

        // algoritmo Rolling polynomial
        for (int i = 0; i < strkey.size(); i++) {
            sum += (strkey[i] * (int)pow(PRIME_CONST, i)) % capacity;
        }
        delete skey;
        return sum % capacity;
    }

	void set(TK key, TV value){
		size_t index = hashFunction(key);
        HashEntry* entry = new HashEntry(key, value);

        if (buckets[index] != nullptr) {
            HashEntry* current = buckets[index];
            while (current->next != nullptr)
                current = current->next;
            
            current->next = entry;
        } else
            buckets[index] = entry;

        ++size;
    }

    TV get(TK key){
        size_t index = hashFunction(key);
        HashEntry* entry = buckets[index];
        while (entry->next != nullptr) {
            if (entry->key == key)
                return entry->value;
            
            entry = entry->next;
        }
        throw std::out_of_range("key unbound in hashtable");
    };

    bool search(TK key) {
        try{
            get(key);   return true;
        } catch {
            return false;
        }
    }

    int bucket_count() const {
        return capacity;
    }

    int bucket_size(unsigned int pos) const {
        HashEntry* temp = buckets[pos];
        int count = 0;
        while (temp->next != nullptr) {;
            temp = temp->next;
            ++count;
        }
        return count;
    };

private:
    double fillFactor(){
        return static_cast<double>(size) / (capacity * maxColision);
    }

    void rehashing(){
        // Aumentar la capacidad del arreglo original
        int newCapacity = capacity * 2;
        HashEntry** newbuckets = new HashEntry*[newCapacity];

        // Insertar todos los elementos del arreglo original en el nuevo arreglo
        for (int i = 0; i < capacity; ++i) {
            if (buckets[i] != nullptr)
                newbuckets[i] = std::move(buckets[i]);
        }

        // Actualizar los campos de la clase con los nuevos valores
        delete[] buckets;
        buckets = newbuckets;
        capacity = newCapacity;
    }
};