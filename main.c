#include <assert.h>
#include <stdlib.h>
#include "impl/hashtable.h"

int main()
{

    struct HashTable* table = create();

    assert( find(table, "Test Key") == NULL);

    assert( add(table, "Test Key", 11) == true);

    assert( add(table, "Test Key", 11) == false);

    struct Binding* binding =  find(table, "Test Key");

    assert( binding != NULL &&  getValue(binding) == 11);
    
    delete_table(table);

    return 0;

}
