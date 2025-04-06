
#include "kbstore.h"

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

Entry* head= NULL;
static pthread_mutex_t lock;

void kb_init(){

	pthread_mutex_init(&lock,NULL);
}

static Entry* find_entry(const char* key, Entry** prev) {
    Entry* curr = head;
    *prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr;
        *prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void kb_set(const char* key, const char* value) {
    pthread_mutex_lock(&lock);
    Entry* prev = NULL;
    Entry* existing = find_entry(key, &prev);
    if (existing) {
        strncpy(existing->value, value, MAX_VALUE_LEN);
    } else {
        Entry* new_entry = malloc(sizeof(Entry));
        strncpy(new_entry->key, key, MAX_KEY_LEN);
        strncpy(new_entry->value, value, MAX_VALUE_LEN);
        new_entry->next = head;
        head = new_entry;
    }
    pthread_mutex_unlock(&lock);
}

const char* kb_get(const char* key) {
    pthread_mutex_lock(&lock);
    Entry* prev = NULL;
    Entry* e = find_entry(key, &prev);
    pthread_mutex_unlock(&lock);
    return e ? e->value : NULL;
}

void kb_delete(const char* key) {
    pthread_mutex_lock(&lock);
    Entry* prev = NULL;
    Entry* e = find_entry(key, &prev);
    if (e) {
        if (prev) prev->next = e->next;
        else head = e->next;
        free(e);
    }
    pthread_mutex_unlock(&lock);
}

void kb_free() {
    pthread_mutex_lock(&lock);
    Entry* curr = head;
    while (curr) {
        Entry* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    head = NULL;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
}
