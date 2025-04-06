#include <stdio.h>
#include "kbstore.h"

#include "persistence.h"

int main() {
    kb_init();
    load_from_file("store.txt");

    kb_set("name", "Erin");
    kb_set("role", "Engineer");
    printf("Name: %s\n", kb_get("name"));

    kb_delete("role");
    save_to_file("store.txt");

    kb_free();
    return 0;
}
