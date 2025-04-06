#include "kbstore.h"
#include <stdio.h>
#include <string.h>



extern Entry* head; 
void load_from_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;

    char key[MAX_KEY_LEN], value[MAX_VALUE_LEN];
    while (fscanf(fp, "%s %s\n", key, value) == 2) {
        kb_set(key, value);
    }

    fclose(fp);
}

void save_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return;
    
    Entry* curr = head;
    while (curr) {
        fprintf(fp, "%s %s\n", curr->key, curr->value);
        curr = curr->next;
    }

    fclose(fp);
}
