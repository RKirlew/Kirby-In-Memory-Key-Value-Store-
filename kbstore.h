#ifndef KBSTORE_H
#define KBSTORE_H

#define MAX_KEY_LEN 128
#define MAX_VALUE_LEN 256
#define MAX_ITEMS 100


typedef struct Entry{

	char key[MAX_KEY_LEN];
	char value[MAX_VALUE_LEN];
	struct Entry* next;
}Entry;

void kb_init();

void kb_set(const char* key,const char* value);
const char* kb_get(const char* key);
void kb_delete(const char* key);
void kb_free();

#endif
