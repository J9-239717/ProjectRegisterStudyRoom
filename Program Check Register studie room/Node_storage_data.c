#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Node_struct.h"
#include "Node_storage_data.h"

////////////////////////////////////////////////////////
void set_all_null(NODE_DATA *data) { 
    for (int i = 0; i < NUM_FIELDS; i++) {
        data->total_data[i] = NULL;
    }
}

char *allocate_and_copy_string(const char *input) {
    if (!input) return NULL;
    char *str = malloc(strlen(input) + 1);
    if (str) strcpy(str, input);
    return str;
}

void insert_data(NODE_DATA *node, const char *fields[NUM_FIELDS]) {
    for (int i = 0; i < NUM_FIELDS; i++) {
        node->total_data[i] = allocate_and_copy_string(fields[i]);
    }
}

void free_node_data(NODE_DATA *node) {
    for (int i = 0; i < NUM_FIELDS; i++) {
        free(node->total_data[i]);
    }
}

NODE_DATA* create_node_data(const char *fields[NUM_FIELDS]) {
    NODE_DATA *node = malloc(sizeof(NODE_DATA));
    if (!node) return NULL;
    set_all_null(node);
    insert_data(node, fields);
    return node;
}

const char* get_field_by_index(const NODE_DATA *data, ID index) {
    if (index >= 0 && index < NUM_FIELDS) {
        return data->total_data[index];
    }
    return NULL; // Return NULL if index is out of range
}
///////////////////////////////////////////////////////////////////////

NODE_DATA* copy_node(NODE_DATA* src){
    NODE_DATA*newnode = (NODE_DATA*)malloc(sizeof(NODE_DATA));
    for(int i = 0; i < NUM_FIELDS; i++){
        newnode->total_data[i] = allocate_and_copy_string(src->total_data[i]);
    }
    return newnode;
}

void free_list_data(List_Data **head) {
    while (*head) { // AI Change: Corrected the loop condition to *head
        List_Data *next = (*head)->next;
        free_node_data((*head)->data);
        free((*head)->data);
        free(*head); // AI Change: Corrected to free *head instead of head
        *head = next; // AI Change: Correctly update the head pointer
    }
}

void add_list(List_Data **head, const char *fields[NUM_FIELDS]) {
    NODE_DATA *new_data = create_node_data(fields);
    if (!new_data) return;

    List_Data *new_node = malloc(sizeof(List_Data));
    if (!new_node) {
        free_node_data(new_data);
        free(new_data);
        return;
    }
    new_node->data = new_data;
    new_node->next = NULL;

    if (!(*head)) { // AI Change: Added this block to handle the case where the list is initially empty
        *head = new_node;
        return; // AI Change: Return after assigning the new node as the head
    }

    List_Data *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

void show_list(const List_Data *head) {
    if (head == NULL) { // AI Change: Added check to handle NULL head case
        printf("List is NULL\n");
        return;
    }

    const char* field_names[NUM_FIELDS] = {
        "KI", "Tr_Vien_Kh", "MaLop", "MaLopKem", "MaHP", "Ten_HP_ENG",
        "Khoi_luong", "Buoi_so", "Thu", "Thoi_gain", "Tuan", "Phong",
        "Can_TN", "SL_Max", "Loai_lop", "Dot_mo", "TeachingType"
    };

    while (head) {
        for (int i = 0; i < NUM_FIELDS; i++) {
            printf("%s: %s\n", field_names[i], get_field_by_index(head->data, i));
        }
        printf("----------------------\n");
        head = head->next;
    }
}

void show_one_node(const NODE_DATA *node){
    const char* field_names[NUM_FIELDS] = {
        "KI", "Tr_Vien_Kh", "MaLop", "MaLopKem", "MaHP", "Ten_HP_ENG",
        "Khoi_luong", "Buoi_so", "Thu", "Thoi_gain", "Tuan", "Phong",
        "Can_TN", "SL_Max", "Loai_lop", "Dot_mo", "TeachingType"
    };
    for (int i = 0; i < NUM_FIELDS; i++) {
            printf("%s: %s\n", field_names[i], get_field_by_index(node, i));
    }
    printf("----------------------\n");
}

List_Data* find(List_Data* src,const char* string_find,ID i){
    List_Data* curr = src;
    List_Data* result_head = NULL;
    List_Data* result_tail = NULL;
    while (curr)
    {
        if(strcmp(curr->data->total_data[i],string_find) == 0){
            NODE_DATA* temp = copy_node(curr->data);
            // Create a new list node
            List_Data* new_node = (List_Data*)malloc(sizeof(List_Data));
            new_node->data = temp;
            new_node->next = NULL;

            if (result_head == NULL) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }
        curr = curr->next;
    }
    return result_head;
}

List_Data* find2(List_Data* src,const char* string_find,ID i,const char *string2_find,ID i2){
     List_Data* curr = src;
    List_Data* result_head = NULL;
    List_Data* result_tail = NULL;
    while (curr)
    {
        if(strcmp(curr->data->total_data[i],string_find) == 0 && strcmp(curr->data->total_data[i2],string2_find) == 0){
            NODE_DATA* temp = copy_node(curr->data);
            // Create a new list node
            List_Data* new_node = (List_Data*)malloc(sizeof(List_Data));
            new_node->data = temp;
            new_node->next = NULL;

            if (result_head == NULL) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }
        curr = curr->next;
    }
    return result_head;
}