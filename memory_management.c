#include<stdio.h>
#include<unistd.h>
#include<string.h>

typedef struct Block{
    size_t size;
    int free;
    struct Block *next;
}Block;

#define BLOCK_SIZE sizeof(Block)

Block *freeList = NULL;

Block *freeCheckList(size_t size);

void *my_malloc(size_t size);

void my_free(void* ptr);

int main(){

    int *a = my_malloc(sizeof(int));
    *a = 100;

    printf("Size of a: %p\n",a);
    printf("Value of a: %d\n",*a);

    my_free(a);

    int *b = my_malloc(sizeof(int));
    *b = 200;

    printf("Size of b: %p\n",b);
    printf("Value of b: %d\n",*b);

    my_free(b);

    char *str = my_malloc(50);
    strcpy(str,"My name is Rumit Maharjan!");

    printf("Size of str: %p\n",str);
    printf("Value of str: %s\n",str);

    my_free(str);

    return 0;
}

void *my_malloc(size_t size){
    Block *block = freeCheckList(size);

    if(block != NULL){
        block->free = 0;
        printf("Reusing the block of %zu bytes\n", block->size);
        return (void*)(block+1);
    }

    block = sbrk(size+BLOCK_SIZE);
    if(block == (void*)-1) return NULL;
    block->free = 0;
    block->size = size;
    block->next = freeList;
    freeList = block;
    printf("New Block of %zu bytes from OS is assigned\n",size);
    return (void*)(block+1);
}

Block *freeCheckList(size_t size){
    Block *current = freeList;
    while(current!=NULL){
        if(current->free == 1 && current->size >= size){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void my_free(void* ptr){
    Block *block = (Block*)ptr-1;
    block->free = 1;
    printf("Freed block of %zu bytes\n", block->size);
}