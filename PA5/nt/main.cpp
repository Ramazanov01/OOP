#include "CatalogManager.h"
#include <iostream>

int main() {
    try {
        CatalogManager catalogManager;
        
        // Parse the catalog data from data.txt
        catalogManager.parseCatalog("data.txt");
        
        // Process commands from commands.txt
        catalogManager.processCommands("commands.txt");
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}