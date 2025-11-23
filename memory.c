#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* start;
    char* next_free;
    size_t block_size;
    size_t total_blocks;
    size_t used_blocks;
} MemoryStash;

MemoryStash* stash_create(size_t block_size, size_t blocks) {
    MemoryStash* stash = malloc(sizeof(MemoryStash));
    stash->start = malloc(block_size*blocks);
    stash->next_free = stash->start;
    stash->block_size = block_size;
    stash->total_blocks = blocks;
    stash->used_blocks = 0;
    printf("Created stash with %zu blocks of %zu bytes\n", blocks, block_size);
    return stash;
}

void* stash_alloc(MemoryStash* stash) {
    if (stash->used_blocks >= stash->total_blocks) {
        printf("No blocks left\n");
        return NULL;
    }
    
    void* chunk= stash->next_free;
    stash->next_free += stash->block_size;
    stash->used_blocks++;
    return chunk;
}

void stash_destroy(MemoryStash* stash) {
    free(stash->start);
    free(stash);
    
    printf("Stash cleared\n");
}

int main() {
    MemoryStash* myStash = stash_create(64, 50);

    char* first = stash_alloc(myStash);
    char* second = stash_alloc(myStash);

    strcpy(first, "First output");
    strcpy(second, "Second output");

    printf("%s | %s\n", first, second);
    printf("Used blocks: %zu/%zu\n", myStash->used_blocks, myStash->total_blocks);

    stash_destroy(myStash);
    
    return 0;
}