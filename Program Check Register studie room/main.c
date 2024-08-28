#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Include your header files
#include "parse_csv_json_own_edit.h"
#include "Node_storage_data.h"
#include "parse_json_local_storage.h"
#include "Node_struct.h"
#include "Logic.h"

int main() {
    char CSV1[100] = "file/", CSV2[100] = "file/";
    char Json1[100] = "file/", Json2[100] = "file/";
    char buffer[100] = "";  // Initialize buffer
    char json[10] = ".json", csv[10] = ".csv";

    do {
        printf("Please Enter Name File CSV 1 (Ex:you will enter like jerry.csv): ");
        if (scanf("%99s", buffer) != 1) {
            printf("Input error. Please try again.\n");
            continue;
        }
        strcat(CSV1, buffer);
        strcat(CSV1, csv);
        strcat(Json1, buffer);
        strcat(Json1, json);

        printf("Please Enter Name File CSV 2 (Ex:you will enter like jerry.csv): ");
        if (scanf("%99s", buffer) != 1) {
            printf("Input error. Please try again.\n");
            continue;
        }
        strcat(CSV2, buffer);
        strcat(CSV2, csv);
        strcat(Json2, buffer);
        strcat(Json2, json);

        FILE *f1 = fopen(CSV1, "r");
        FILE *f2 = fopen(CSV2, "r");

        if (!f1 || !f2) {
            printf("Can't find file\n");
            printf("Please try entering the correct name of the file or upload the file before running the program\n");
            printf("Press Enter to retry..."); getchar();
            strcpy(CSV1, "file/");
            strcpy(CSV2, "file/");
            strcpy(Json1, "file/");
            strcpy(Json2, "file/");
            if (f1) fclose(f1);
            if (f2) fclose(f2);
        } else {
            fclose(f1);
            fclose(f2);
            break;
        }
    } while (1);

    // Convert CSV to JSON
    Load_File_CSV(CSV1, Json1);
    Load_File_CSV(CSV2, Json2);

    char c;
    while ((c = getchar()) != '\n' && c != EOF);  // Clear the input buffer

    // Logic (uncomment if you want to use this part)
    PayLoad(Json1, Json2);

    remove(Json1);
    remove(Json2);

    return 0;
}

