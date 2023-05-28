#ifndef TRANSATION_COMPONENT_H
#define TRANSATION_COMPONENT_H

#include <iostream>
#include <chrono>
using namespace std;

// Definición de la información dentro de la transacción
struct Transaction {
    string client;
    string place;
    float amount;
    string date;

public:
    
    Transaction() = default;
    ~Transaction() = default;

    Transaction(const string& client,const string& place,const string& date, float amount);
    
   
    // Función que imprime la transacción en consola.
     void printTransaction() const {
        std::time_t unixTimestamp(std::stol(date));
        string formattedDate = std::asctime(std::localtime(&unixTimestamp));

        std::cout << "Client: " << client << std::endl;
        std::cout << "Place: " << place << std::endl;
        std::cout << "Date: " << formattedDate.substr(0, 24) << std::endl;
        std::cout << "Amount: " << amount << std::endl;
    }

    // !llamada de la funcion
    /*
    Transaction tx("client", "place", "2023-05-23", 100.0);
    tx.printTransaction();  // Imprime la transacción
    */
};

Transaction::Transaction(const string& client, const string& place, const string& date, float amount) {
        this->client = client;
        this->place = place;
        this->date = date;
        this->amount = amount;
    }


#endif // TRANSATION_COMPONENT_H