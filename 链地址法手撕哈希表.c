#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct List {
    int key;
    int val;
    struct List* next;
};

void listPush(struct List* head, int key, int val) {
    struct List* tmp = malloc(sizeof(struct List));
    tmp->key = key;
    tmp->val = val;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List* head, int key) {
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            struct List* tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

struct List* listFind(struct List* head, int key) {
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            return it->next;
        }
    }
    return NULL;
}

void listFree(struct List* head) {
    while (head->next) {
        struct List* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;

int hash(int key) {
    return key % base;
}

typedef struct {
    struct List* data;
} MyHashMap;

MyHashMap* myHashMapCreate() {
    MyHashMap* ret = malloc(sizeof(MyHashMap));
    ret->data = malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        ret->data[i].key = 0;
        ret->data[i].val = 0;
        ret->data[i].next = NULL;
    }
    return ret;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int h = hash(key);
    struct List* rec = listFind(&(obj->data[h]), key);
    if (rec == NULL) {
        listPush(&(obj->data[h]), key, value);
    }
    else {
        rec->val = value;
    }
}

int myHashMapGet(MyHashMap* obj, int key) {
    int h = hash(key);
    struct List* rec = listFind(&(obj->data[h]), key);
    if (rec == NULL) {
        return -1;
    }
    else {
        return rec->val;
    }
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int h = hash(key);
    listDelete(&(obj->data[h]), key);
}

void myHashMapFree(MyHashMap* obj) {
    for (int i = 0; i < base; i++) {
        listFree(&(obj->data[i]));
    }
    free(obj->data);
}