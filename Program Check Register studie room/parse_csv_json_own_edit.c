#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_csv_json_own_edit.h"

#define MAX_LINE_LEN 1024
#define MAX_FIELDS 100
#define SIZEOFHEADOWNEDIT 17

int is_phrase_delete(int i) {
    int delete_index[] = {5, 8, 12, 13, 14, 18, 20, 23, 25};
    int size_dele = sizeof(delete_index) / sizeof(delete_index[0]);

    // Binary search
    int L = 0;
    int R = size_dele - 1;
    while (L <= R) {
        int M = L + (R - L) / 2;
        if (delete_index[M] == i) {
            return 1;
        } else if (delete_index[M] < i) {
            L = M + 1;
        } else {
            R = M - 1;
        }
    }
    return 0;
}

void csv_to_json(const char *csv_filename, const char *json_filename) {
    FILE *csv_file = fopen(csv_filename, "r");
    FILE *json_file = fopen(json_filename, "w");

    if (!csv_file || !json_file) {
        perror("Unable to open file");
        if (csv_file) fclose(csv_file);
        if (json_file) fclose(json_file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    char *fields[MAX_FIELDS];
    int field_count = 0;
    int line_number = 0;

    // Read the first line to get the headers
    if (fgets(line, MAX_LINE_LEN, csv_file)) {
        char *token = strtok(line, ",");
        while (token) {
            token[strcspn(token, "\r\n")] = '\0';
            fields[field_count] = strdup(token);
            if (!fields[field_count]) {
                perror("Unable to allocate memory");
                exit(EXIT_FAILURE);
            }
            field_count++;
            if (field_count >= MAX_FIELDS) {
                fprintf(stderr, "Too many fields in CSV\n");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, ",");
        }
    }

    fprintf(json_file, "[\n");
////////////////////////////////// SKIP TITLE /////////////////////////////////////////////
    // Write the title section
    if (fgets(line, MAX_LINE_LEN, csv_file)) {
        // fprintf(json_file, "  {\n");
        // const char *title[] = {
        //     "Ki", "Truong_Vien_Khoa", "Ma_lop", "Ma_lop_kem", "Ma_HP",
        //     "Ten_HP_Tieng_Anh", "Khoi_luong", "Buoi_so", "Thu", "Thoi_gian",
        //     "Tuan", "Phong", "Can_TN", "SL_Max", "Loai_lop", "Dot_mo", "TeachingType"
        // };
        // for (int i = 0; i < SIZEOFHEADOWNEDIT; i++) {
        //     fprintf(json_file, "    \"%d\": \"%s\"", i, title[i]);
        //     if (i < SIZEOFHEADOWNEDIT - 1) {
        //         fprintf(json_file, ",\n");
        //     } else {
        //         fprintf(json_file, "\n");
        //     }
        // }
        // fprintf(json_file, "  }");
        // line_number++;
    }
////////////////////////////////////////////////////////////////////////////////////////    
    int count_index = 0;
    char buffer[256];
    int colum = 0;
    // Process the rest of the lines
    while (fgets(line, MAX_LINE_LEN, csv_file)) {
        line[strcspn(line,"\r\n")] = '\0';
        if (line_number > 0) {
            fprintf(json_file, ",\n");
        }
        fprintf(json_file, "  {\n");
        count_index = 0;
        colum = 0;
        int index = 0;
        int count = 0;
        while(line[count_index] != '\0' && count < SIZEOFHEADOWNEDIT){
            if(line[count_index] != '\"'){
                index = 0;
                while (line[count_index] != ','&& index < 256){
                    buffer[index++] = line[count_index++];
                }
                buffer[index] = '\0';
            }else{
                count_index++;
                index = 0;
                while (line[count_index] != '\"'){
                    buffer[index++] = line[count_index++];
                }
                buffer[index] = '\0';
                count_index++;
            }
            int check = atoi(fields[colum]);
            if(!is_phrase_delete(check)){
                fprintf(json_file, "    \"%d\": \"%s\"", count, buffer);
                if (count < SIZEOFHEADOWNEDIT - 1) {
                    fprintf(json_file, ",\n");
                } else {
                    fprintf(json_file, "\n");
                }
                count++;
            }
            count_index++;
            colum++;
        }

        fprintf(json_file, "  }");
        line_number++;
    }

    fprintf(json_file, "\n]\n");

    // Close files
    fclose(csv_file);
    fclose(json_file);

    // Free allocated memory for headers
    for (int i = 0; i < field_count; i++) {
        free(fields[i]);
    }
}

void Load_File_CSV(const char* f,const char* name){
    csv_to_json(f,name);
}
