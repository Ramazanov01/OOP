#include "CatalogManager.h"

int main()
{
    CatalogManager manager;                  // Create an instance of CatalogManager
    manager.parseCatalog("data.txt");        // Parse the catalog from data.txt
    manager.processCommands("commands.txt"); // Process commands from commands.txt
    return 0;
}
