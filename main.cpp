// por consola

#include "blocks/blockchain.h"

int main() {
    Blockchain* blockchain = new Blockchain;
    blockchain->init_blockchain();
    delete blockchain;
}

// por SFML
/*
#include <iostream>
#include "structures/heap.h"
#include "interface/gui.h"

using namespace std;

int main() {
    AppGui* gui = new AppGui;
    gui->init_visualize_app();
    delete gui;
}
*/