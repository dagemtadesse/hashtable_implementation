#include<stdbool.h>

typedef struct Binding Binding;


int getValue(Binding *binding);

void setValue(Binding *binding, int new_value);

typedef struct HashTable HashTable ;

HashTable  *create();

unsigned int hash(const char *key);

bool add(HashTable *table, const char *key, int value);

bool remove(HashTable *table, const char *key);

struct Binding *find(HashTable *table, const char *key);

void delete_table(HashTable *table);
