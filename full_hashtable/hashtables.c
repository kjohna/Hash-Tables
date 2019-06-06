#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the 
  next `LinkedPair` in the list of `LinkedPair` nodes. 
 */
typedef struct LinkedPair
{
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable
{
  int capacity;
  LinkedPair **storage;
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
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

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  HashTable *ht;
  ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair *));
  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // compute index
  int index = hash(key, ht->capacity);
  // create a linked pair with the new values
  LinkedPair *new_pair = create_pair(key, value);
  // if nothing is at index, place new_pair there
  if (ht->storage[index] == NULL)
  {
    ht->storage[index] = new_pair;
  }
  // else check if key matches
  else
  {
    // if key matches, print warning & replace value
    if (ht->storage[index]->key == key)
    {
      printf("warning: duplicate key, replacing %s with %s.\n", ht->storage[index]->value, value);
      ht->storage[index]->value = value;
    }
    // else while there is a 'next'...
    else
    {
      LinkedPair *curr_pair = ht->storage[index];
      LinkedPair *next_pair = ht->storage[index]->next;
      while (next_pair)
      {
        // if key matches, print warning & replace value
        if (next_pair->key == key)
        {
          printf("warning: duplicate key, replacing %s with %s.\n", next_pair->value, value);
          curr_pair->next = new_pair;
          return;
        }
        // otherwise check next
        curr_pair = next_pair;
        next_pair = curr_pair->next;
      }
      // if we got to next == NULL w/o storing new pair, put the new_pair there
      curr_pair->next = new_pair;
    }
  }
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  char *rv = NULL;
  // compute index
  int index = hash(key, ht->capacity);
  LinkedPair *curr_pair = ht->storage[index];
  // determine if anything is there
  if (curr_pair)
  {
    // if curr_pair has value we're looking for return that
    if (!strcmp(key, curr_pair->key))
    {
      rv = curr_pair->value;
    }
    else
    {
      // as long as there is a next..
      while (curr_pair->next)
      {
        // move to next
        curr_pair = curr_pair->next;
        // if key matches, return the value
        if (!strcmp(key, curr_pair->key))
        {
          rv = curr_pair->value;
          break;
        }
      }
    }
    // will return null if no match was found
  }
  // otherwise notify no value w/ that key
  else
  {
    printf("nothing found for key %s.\n", key);
  }
  return rv;
}

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{
}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht;

  return new_ht;
}

#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  // int old_capacity = ht->capacity;
  // ht = hash_table_resize(ht);
  // int new_capacity = ht->capacity;

  // printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
