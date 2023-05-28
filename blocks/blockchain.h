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
  BlockChain() = default;
  BlockChain(const string &users,const string &transacciones);
  void createUser(const string &username, const string &password);
  bool searchUser(const string &username, const string &password);
  void setData(const string &username, const string &password, const string &place, float amount, const string &date);
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date);

};


BlockChain::BlockChain(const string &users,const string &transacciones){
    string 
}

void BlockChain::createUser(const string &username, const string &password){
    

}

bool BlockChain::searchUser(const string &username, const string &password){
    
}

void BlockChain::setData(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash = username + password;
    auto *transaccion = new Transaction(username,place, date, amount);
}

bool BlockChain::searchData(const string &username, const string &password, const string &place, float amount, const string &date){
    Block *block = usersHash.get(username);
    if (block != nullptr){
        return block->searchData(username, password, place, amount, date);
    }
    return false;
}
