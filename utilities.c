#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mtmflix.h"
#include "utilities.h"
#include "set.h"
#define KEY_VALUE_SIZE 3

//creates a const copy of a given string
const char* copyString(const char* str) {
  int length = strlen(str);
  char* new_str = malloc(sizeof(char)*length+1);
  if (new_str == NULL) {
    return NULL;
  }
  assert(new_str);
  strcpy(new_str, str);
  return new_str;
}

//frees a string
void freeString(const char* str) {
  free((void*)str);
}

//compares two strings
int compareStrings(void * str_a, void * str_b) {
  return strcmp((char*)str_a, (char*)str_b);
}

//Checks if the string can be
//legal series or user name
bool stringCheck(const char* string) {
	int length = strlen(string);
	if(length==0){
        return false;
	}
	for (int i = 0; i < length; i++) {
		if (!((string[i] >= 'A' && string[i] <= 'Z') || 
      (string[i] >= 'a' && string[i] <= 'z') || 
      (string[i] >= '0' && string[i] <= '9'))) {
			return false;
		}
	}
	return true;
}

KeyValuePair createKeyValuePair(void* key, void* value) {
    KeyValuePair key_value_pair = malloc(sizeof(struct key_value_pair_t));
    if (key_value_pair == NULL) {
        return NULL;
    }
    key_value_pair->key   = key;
    key_value_pair->value = value;
    return key_value_pair;
}

//Creates a copy of the element of the
//specific type list, which stores key-value pairs
KeyValuePair copyKeyValuePair(KeyValuePair keyValuePair) {
  assert(keyValuePair);
  KeyValuePair copy = malloc(sizeof(KeyValuePair)*
          KEY_VALUE_SIZE);
  if (keyValuePair == NULL) {
      freeKeyValuePair(copy);
      return NULL;
  }
  copy->key   = ((KeyValuePair) keyValuePair)->key;
  copy->value = ((KeyValuePair) keyValuePair)->value;
  return copy;
}

//frees memory allocated to a key-value pair
void freeKeyValuePair(KeyValuePair keyValuePair) {
  free(keyValuePair);
  keyValuePair = NULL;
}

//Creates a list based on the given map
//List stores elements as key-value pairs
List mapToList(Map map, ListResult* status) {
  *status = LIST_SUCCESS;
  if (map == NULL) {
    *status = LIST_NULL_ARGUMENT;
    return NULL;
  }
  List newList = listCreate((CopyListElement)copyKeyValuePair, 
    (FreeListElement)freeKeyValuePair);
  int mapSize = mapGetSize(map);
  if (mapSize == 0) {
    return newList;
  }
  MAP_FOREACH(MapKeyElement, map_key, map) {
    KeyValuePair listElement = malloc(sizeof(KeyValuePair)*KEY_VALUE_SIZE);
    if (listElement == NULL) {
      *status = LIST_OUT_OF_MEMORY;
      listDestroy(newList);
      return NULL;
    }
    listElement->key   = map_key;
    listElement->value = mapGet(map, map_key);
    ListResult list_result = listInsertLast(newList, listElement);
    freeKeyValuePair(listElement);
    if (list_result != LIST_SUCCESS) {
      *status = LIST_INVALID_CURRENT;
      listDestroy(newList);
      return NULL;
    }
  }
  return newList;
}

//Creates a list based on the given set
List mtmSetToList(Set set, ListResult* status){
    *status=LIST_SUCCESS;
    if (set == NULL) {
        *status = LIST_NULL_ARGUMENT;
        return NULL;
    }
    List newList = listCreate((CopyListElement)copyString,
            (FreeListElement)freeString);
    int setSize = setGetSize(set);
    if (setSize == 0) {
        return newList;
    }
    SET_FOREACH(SetElement, setElement, set) {
        if (listInsertLast(newList, (ListElement)setElement) != LIST_SUCCESS) {
            *status = LIST_INVALID_CURRENT;
            listDestroy(newList);
            return NULL;
        }
    }
    return newList;
}

//Creates a simple list based on the given map
List mapKeyToList(Map map, ListResult* status){
    *status=LIST_SUCCESS;
    if (map == NULL) {
        *status = LIST_NULL_ARGUMENT;
        return NULL;
    }
    List newList = listCreate((CopyListElement)copyString,
            (FreeListElement)freeString);
    int mapSize = mapGetSize(map);
    if (mapSize == 0) {
        return newList;
    }
    MAP_FOREACH(MapKeyElement, mapKeyElement, map) {
        if (listInsertLast(newList, (ListElement)mapKeyElement) 
          != LIST_SUCCESS) {
            *status = LIST_INVALID_CURRENT;
            listDestroy(newList);
            return NULL;
        }
    }
    return newList;
}

//Puts value into the value field
//of list element of the key-value type
void listPutValue(KeyValuePair listElement, void* value){
    printf("Putting %d\n", *(int*)value);
    if(listElement==NULL||value==NULL){
        return;
    }
    listElement->value=value;
}

//Returns value of list element
//of the key-value type
void* listGetValue(KeyValuePair listElement){
    if(listElement==NULL){
        return NULL;
    }
    return listElement->value;
}

//Returns key of list element
//of the key-value type
void* listGetKey(KeyValuePair listElement){
    if(listElement==NULL){
        return NULL;
    }
    return listElement->key;
}
