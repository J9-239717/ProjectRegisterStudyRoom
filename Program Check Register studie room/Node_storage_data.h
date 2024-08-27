#ifndef NODEDATA_H
#define NODEDATA_H

#include "Node_struct.h"
NODE_DATA* copy_node(NODE_DATA* src);
void free_list_data(List_Data **head);
void add_list(List_Data **head,const char *fields[NUM_FIELDS]);
void show_list(const List_Data *head);
void show_one_node(const NODE_DATA *node);
List_Data* find(List_Data* src,const char* string_find,ID i);
List_Data* find2(List_Data* src,const char* string_find,ID i,const char *string2_find,ID i2);
void show_one_two_topic_by_id(const NODE_DATA *node,ID id1,ID id2);
#endif