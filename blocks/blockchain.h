#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//
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
  void setData(const string &username, const string &password, const string &place, float amount, const string &date);
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date);

  

};


BlockChain::BlockChain(const string &users,const string &transacciones){
    
}

void BlockChain::setData(const string &username, const string &password, const string &place, float amount, const string &date){
    Block *block = new Block(username, password, place, amount, date);
    chain.insert(block);
    usersHash.set(username, block);
}

bool BlockChain::searchData(const string &username, const string &password, const string &place, float amount, const string &date){
    Block *block = usersHash.get(username);
    if (block != nullptr){
        return block->searchData(username, password, place, amount, date);
    }
    return false;
}
