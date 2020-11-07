#include "hashtable.h"

#include <stdlib.h>

/*
 conn
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */

//
HashTable * createHashTable(int size, unsigned int( * hashFunction)(void * ),
  int( * equalFunction)(void * , void * )) {
  int i = 0;
  HashTable * newTable = malloc(sizeof(HashTable));
  newTable -> size = size;
  newTable -> data = malloc(sizeof(struct HashBucket * ) * size);
  for (i = 0; i < size; ++i) {
    newTable -> data[i] = NULL;
  }
  newTable -> hashFunction = hashFunction;
  newTable -> equalFunction = equalFunction;
  return newTable;
}

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
void insertData(HashTable * table, void * key, void * data) {
  // -- TODO --
    int size = table -> size;
    int MAX = 60;
    char * key1 = (char *) key;
    char * data1 = (char *) data;
    unsigned int bucketIndex = ((unsigned int)(table -> hashFunction)(key1) % (size));
    struct HashBucket * newBucket = malloc(sizeof(struct HashBucket));
    char * newdata = malloc(sizeof(char) * MAX);
    char * newkey  = malloc(sizeof(char) * MAX);
    int place = 0;
    //copy from key
    while(data1[place] != '\0') {
        newdata[place] =(char) data1[place];
        newkey[place] = (char)key1[place];
        place++;
        if(place >= MAX) {
            newdata = realloc(newdata,(sizeof(char) * place) + 1);
            newkey = realloc(newkey,(sizeof(char) * place)+ 1);
        }
    }
    //
    struct HashBucket * head = table -> data[bucketIndex];
    if (head == NULL) {
        table->data[bucketIndex] = newBucket;
        newBucket->data = newdata;
        newBucket->key = newkey;
        newBucket->next = NULL;
        return;
    }
    newBucket->key = newkey;
    newBucket->data = newdata;
    newBucket->next = head;
    head = newBucket;
  return;
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found.
 */
void * findData(HashTable * table, void * key) {
  int size = table -> size;
  char * key1 = (char * ) key;
  unsigned int bucketIndex = (unsigned int)((table -> hashFunction)(key) % (size));
  struct HashBucket * ptr = (table -> data[bucketIndex]);
  if (ptr == NULL) {
    return NULL;
  }
  while (ptr -> next != NULL) {
    if ((table -> equalFunction)(key1, ptr -> data)) {
      return ptr -> data;
    }
    ptr = ptr -> next;
  }
  if ((table -> equalFunction)(key1, (ptr) -> data)) {
    return ptr -> data;
  }
  return NULL;
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
}

