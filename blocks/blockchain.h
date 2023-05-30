#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "block.h"
#include "../structures/node.h"
#include "../structures/doubleList.h"
#include "../structures/chainHash.h"

using namespace std;


class BlockChain {

private:
    DoubleList<Block *> chain;
    // Faltaria el btree;
    ChainHash <std::string, Block*> usersHash;
    int cantblocks;
    
public:
 
  BlockChain() = default;
  ~BlockChain() = default;

  void init_blockchain();

  BlockChain(const string &users,const string &transacciones); //Leo
  void createUser(const string &username, const string &password); //Leo
  bool searchUser(const string &username, const string &password); //Leo
  void setTransaction(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  void theTransactions(const std::string &username, const std::string &password); //Noemi
  void date(const std::string &username, const std::string &password); //Noemi
  void Amount(const std::string &username, const std::string &password); //Noemi
  void MaxDate(const std::string &username, const std::string &password); //Noemi
  void MinDate(const std::string &username, const std::string &password); // Mariel
  void MaxAmount(const std::string &username, const std::string &password); // Mariel
  void MinAmount(const std::string &username, const std::string &password); // Mariel
  void cascade(const string &username, const string &password); // Mariel
  static void loadFile(DoubleList<Transaction*>* doubleList, const std::string& path = "./assets/data/datos.txt"); //Mariel
  
};


BlockChain::BlockChain(const string &users,const string &transactions){
    string line;
    auto *file=new ifstream(users);
    getline(*file,line,'\n');
    string username,password;

    while((*file)>>username>>password){
        createUser(username,password);
    }
    file->close();

    file= new ifstream(transactions);
    getline(*file,line,'\n');
    string client,amount,place,date;

    while((*file)>>client>>password>>date>>place>>amount){
        setTransaction(client,password,place,stof(amount),date);
    }
    file->close();
}


void BlockChain::init_blockchain() {

}


void BlockChain::createUser(const string &username, const string &password){
    string hash = username + password;
    if(chain.is_empty()){
        auto *block = new Block();
        auto *node = new NodeList<Block *>(block);
        chain.push_back(block);
        usersHash.set(hash,chain.begin());
    }
    else{
        chain.push_back(new Block{chain.size(),chain.end()->data->hash});
        usersHash.set(hash,chain.end());
    }
}

bool BlockChain::searchUser(const string &username, const string &password){
    string hash = username + password;
    return usersHash.search(hash);
}

void BlockChain::setTransaction(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash = username + password;
    auto *transaccion = new Transaction(username,place, date, amount);
    usersHash.get(hash)->data->insert(transaccion);
    usersHash.get(hash)->data->hash = usersHash.get(hash)->data->calculateHash();

    auto it = usersHash.get(hash);
    while (it != nullptr){
        it->data->previousHash = it->prev->data->hash;
        it->data->hash = it->data->calculateHash();
        it = it->next;
    }
}

bool BlockChain::searchData(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash=username+password;
    auto *transaccion= new Transaction(username, place, date,amount);
    stringstream key;
    key << *(transaccion);
    return usersHash.get(hash)->data->data_hash.search(key.str());
}

void BlockChain::theTransactions(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->data->data;
    loadFile(&transactions);
}

void BlockChain::date(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->data;
    loadFile(&transactions);
}

void BlockChain::Amount(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->data;
    loadFile(&transactions);
}

void BlockChain::MaxDate(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->maxFecha;
    loadFile(&transactions);

}

void BlockChain::MinDate(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->minFecha;
    loadFile(&transactions);
}

void BlockChain::MaxAmount(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->maxMonto;
    loadFile(&transactions);
}

void BlockChain::MinAmount(const std::string &username, const std::string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->minMonto;
    loadFile(&transactions);
}

void BlockChain::cascade(const string &username, const string &password){
    string hash = username + password;
    DoubleList<Transaction *> transactions = this->usersHash.get(hash)->data;
    loadFile(&transactions);
}

void BlockChain::loadFile(DoubleList<Transaction*>* doubleList, const std::string& path = "./assets/data/datos.txt") {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Suponiendo que cada línea del archivo contiene los datos de una transacción
        // y que tienes un constructor de Transaction que acepta una cadena de texto con los datos
        Transaction* transaction = new Transaction(line);
        doubleList->addBack(transaction);
    }

    file.close();
}