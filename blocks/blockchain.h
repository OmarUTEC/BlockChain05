#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "block.h"
#include "../structures/node.h"

using namespace std;


class BlockChain {

private:
    DoubleList<Block *> chain {};
    ChainHash <std::string, NodeList<Block *> *> usersHash {};
    
public:
 
  ~BlockChain() = default;
  BlockChain(const string &users,const string &transacciones); //Leo
  void createUser(const string &username, const string &password); //Leo
  bool searchUser(const string &username, const string &password); //Leo
  void setData(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  void myTxs(const std::string &username, const std::string &password); //Noemi
  void date(const std::string &username, const std::string &password); //Noemi
  void Amount(const std::string &username, const std::string &password); //Noemi
  void MaxDate(const std::string &username, const std::string &password); //Noemi
  void MinDate(const std::string &username, const std::string &password); // Mariel
  void MaxAmount(const std::string &username, const std::string &password); // Mariel
  void MinAmount(const std::string &username, const std::string &password); // Mariel
  void cascade(const string &username, const string &password); // Mariel
  static void loadFile(DoubleList<Transaction*>* doubleList, const std::string& path = "./assets/data/datos.txt"); //Mariel
  
};


BlockChain::BlockChain(const string &users,const string &transacciones){
    string line;
    
}

void BlockChain::createUser(const string &username, const string &password){
    if(chain.is_empty()){
        string hash = username + password;
        auto *block = new Block();
        auto *node = new NodeList<Block *>(block);
        chain.push_back(block);
        usersHash.set(hash,chain.begin());
    }
}

bool BlockChain::searchUser(const string &username, const string &password){
    
}

void BlockChain::setData(const string &username, const string &password, const string &place, float amount, const string &date){
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
    Block *block = usersHash.get(username);
    if (block != nullptr){
        return block->searchData(username, password, place, amount, date);
    }
    return false;
}

void BlockChain::cascade(const string &username, const string &password){
    stringstream user;
    user << username;
    user << password;
    usersHash.get()
}
