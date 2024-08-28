#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Node_storage_data.h"
#include "Node_struct.h"

#define SRC_FILE "output/person.txt"

void getNameInfilePath(const char* src, char* result) {
    int count = 0;
    const char* temp = strrchr(src, '/');
    if (temp != NULL) {
        temp++;
    } else {
        temp = src;
    }

    while (temp[count] != '.' && temp[count] != '\0') {
        result[count] = temp[count];
        count++;
    }
    result[count] = '\0';
}

void write_txt(const char* person1, const char* person2, const List_Data* p1, const List_Data* p2) {
    char name[256];
    int c;
    do {
        printf("What person do you want 1 or 2: ");
        scanf("%d", &c);
        while (getchar() != '\n');  // Consume the newline character after scanf
        if (c < 1 || c > 2) printf("Please enter again\n");
        else break;
    } while (1);

    switch (c) {
        case 1: getNameInfilePath(person1, name); break;
        case 2: getNameInfilePath(person2, name); break;
        default: getNameInfilePath(person1, name); break;
    }

    FILE* fp = fopen(SRC_FILE, "w");
    if (fp == NULL) {
        printf("Failed to open file %s for writing\n", SRC_FILE);
        return;
    }

    fprintf(fp, "//////////////////////////////////////%s//////////////////////////////////////\n"
               "///// MA LOP FOR DK/////\n\n", name);

    const List_Data* curr = (c == 2) ? p2 : p1;

    while (curr) {
        fprintf(fp, "//%s//\n"
                    "%s\t%s\n", curr->data->total_data[Ten_HP_ENG], curr->data->total_data[MaLop],curr->data->total_data[Loai_lop]);

        if (curr->next && strcmp(curr->next->data->total_data[Ten_HP_ENG], curr->data->total_data[Ten_HP_ENG]) == 0) {
            fprintf(fp, "%s\t%s\n", curr->next->data->total_data[MaLop], curr->next->data->total_data[Loai_lop]);
            fprintf(fp, "//////////\n\n");
            curr = curr->next;
        } else {
            fprintf(fp, "//////////\n\n");
        }
        curr = curr->next;
    }

    fprintf(fp, "///////////////////////////////////////////////////////////////////////////////////");
    fclose(fp);
}
