#include <stdio.h>

struct item *head = NULL;

struct item {
    int key;
    int data;
    struct item *next;
};

