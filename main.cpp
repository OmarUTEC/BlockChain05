#include <iostream>
#include "structures/heap.h"
#include "interface/gui.h"

using namespace std;

int main() {
    AppGui* gui = new AppGui;
    gui->init_visualize_app();
    delete gui;
}
