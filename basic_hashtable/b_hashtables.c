#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char *u_str = (unsigned char *)str;

  while ((c = *u_str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht;
  ht = malloc(sizeof(BasicHashTable));
  ht->capacity = capacity;
  // initialize storage to null
  ht->storage = calloc(capacity, sizeof(Pair *));
  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // create a Pair with key, value
  Pair *new_pair = create_pair(key, value);
  // get index of key
  int index = hash(key, ht->capacity);
  // check if anything is already in ht at index
  if (ht->storage[index])
  {
    // if yes print warning, clear existing
    printf("Warning: overwriting %s.\n", ht->storage[index]->value);
    free(ht->storage[index]);
  }
  // put Pair in storage
  ht->storage[index] = new_pair;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  printf("removing %s\n", key);
  // get index of key
  int index = hash(key, ht->capacity);
  // if nothing is there print warning, done
  if (ht->storage[index] == NULL)
  {
    printf("nothing to remove for %s.\n", key);
    return;
  }
  // else destroy pair (frees malloc'd memory for the pair)
  destroy_pair(ht->storage[index]);
  // set storage[index] to NULL
  ht->storage[index] = NULL;
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  char *rv = NULL;
  int index;
  printf("retreiving %s\n", key);
  // get index of key
  index = hash(key, ht->capacity);
  // check if there's anything at storage[index]
  if (ht->storage[index] == NULL)
  {
    // if NULL is there print warning
    printf("no value corresponding to %s.\n", key);
  }
  else
  {
    // get storage[index]
    rv = ht->storage[index]->value;
  }
  return rv;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  printf("destroying hash table\n");
  for (int i = 0; i < ht->capacity; i++)
  {
    // look through all of ht's storage, free any pairs stored there
    if (ht->storage[i] != NULL)
    {
      destroy_pair(ht->storage[i]);
    }
  }
  // free ht itself
  free(ht->storage);
  free(ht);
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL)
  {
    printf("...gone tomorrow. (success)\n");
  }
  else
  {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
