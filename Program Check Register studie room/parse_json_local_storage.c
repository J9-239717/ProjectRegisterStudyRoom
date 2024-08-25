#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Node_struct.h"
#include "Node_storage_data.h"
#include "parse_json_local_storage.h"

#define MAX_KEY_LEN 256
#define MAX_VALUE_LEN 256

List_Data* Get_Data(const char* file_json){
    FILE* json_file = fopen(file_json, "r");
    List_Data* head = NULL;
    if (!json_file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    int c;
    int in_string = 0;
    int is_key = 1;
    int key_index = 0;
    int value_index = 0;
    int count = 0;
    char **fields= (char**)malloc(sizeof(char*) * NUM_FIELDS);
    // Allocate memory for each field string
    for (int i = 0; i < NUM_FIELDS; i++) {
        fields[i] = malloc(MAX_VALUE_LEN);
        if (!fields[i]) {
            perror("Unable to allocate memory");
            exit(EXIT_FAILURE);
        }
    }

    while ((c = fgetc(json_file)) != EOF) {
        if (c == '"') {
            in_string = !in_string;
            if (!in_string) {
                if (is_key) {
                    key[key_index] = '\0';
                    is_key = 0;
                } else {
                    value[value_index] = '\0';
                    strcpy(fields[count],value);
                    key_index = value_index = 0;
                    is_key = 1;
                    count++;
                }
            }
        } else if (in_string) {
            if (is_key) {
                key[key_index++] = c;
            } else {
                value[value_index++] = c;
            }
        } else if (c == '{' || c == ',') {
            // Start of a new key-value pair
            key_index = value_index = 0;
            is_key = 1;
        } else if (c == '}') {
            add_list(&head,(const char**)fields);
            count = 0;
        }
    }

    for (int i = 0; i < NUM_FIELDS; i++) {
        free(fields[i]);
    }
    free(fields);
    fclose(json_file);
    return head;
}

List_Data* Load_Json_Data(const char* file){
    return Get_Data(file);
}
