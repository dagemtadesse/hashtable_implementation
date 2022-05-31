#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hashtable.h"

enum
{
	BUCKET_COUNT = 1024
};

typedef struct Binding
{
	const char *key;
	int value;
	Binding *next;
} Binding;

int getValue(Binding *binding)
{
	return binding->value;
}

void setValue(Binding *binding, int new_value)
{
	binding->value = new_value;
}

typedef struct HashTable
{
	struct Binding *buckets[BUCKET_COUNT];
} HashTable;

HashTable *create()
{
	return (HashTable *)malloc(sizeof(HashTable));
}

// deallocate both the key and the struct containing the key and value
void free_binding(Binding *binding)
{
	free((char *)binding->key);
	free(binding);
}

unsigned int hash(const char *key)
{
	// uses djb2
	int hash = 5381;
	for (int i = 0; key[i] != '\0'; i++)
	{
		hash = ((hash << 5) + (hash)) + key[i];
	}

	return ((unsigned int)hash) % BUCKET_COUNT;
}

bool add(HashTable *hashTable, const char *key, int value)
{
	int index = hash(key);
	Binding *binding = hashTable->buckets[index];
	while (binding != NULL)
	{
		if (strcmp(key, binding->key) == 0)
		{ // key is found
			binding->value = value;
			return false;
		}
		binding = binding->next;
	}
	// key is not found
	Binding *new_binding = malloc(sizeof(binding));
	char *ownedKey = (char *)malloc(strlen(key) + 1);
	strcpy(ownedKey, key);

	new_binding->key = ownedKey;
	new_binding->value = value;
	new_binding->next = hashTable->buckets[index];
	hashTable->buckets[index] = new_binding;
	return true;
}

bool remove (HashTable *hashTable, const char *key)
{
	unsigned int index = hash(key);
	Binding *binding = hashTable->buckets[index];
	Binding *prev_binding;
	// if the key is on the first item of linked list
	if (strcmp(binding->key, key) == 0)
	{
		hashTable->buckets[index] = binding->next;
		free_binding(binding);
		return true;
	}
	// if the key is not on the first item of the linked list
	while (binding != NULL)
	{
		prev_binding = binding;
		binding = binding->next;

		if (strcmp(key, binding->key) == 0)
		{
			prev_binding->next = binding->next;
			free_binding(binding);
			return true;
		}
	}
	return false;
}

struct Binding *find(HashTable *hashTable, const char *key)
{
	unsigned int index = hash(key);
	Binding *binding = hashTable->buckets[index];

	while (binding != NULL)
	{
		if (strcmp(key, binding->key) == 0)
			return binding;
		binding = binding->next;
	}

	return NULL;
}

void delete_table(HashTable *hashTable)
{
	for (int i = 0; i < BUCKET_COUNT; i++)
	{
		while (hashTable->buckets[i] != NULL)
		{
			Binding *binding = hashTable->buckets[i];
			hashTable->buckets[i] = binding->next;
			free_binding(binding);
		}
	}
	free(hashTable);
}
