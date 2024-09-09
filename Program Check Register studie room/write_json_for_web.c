#include <stdio.h>
#include "Node_struct.h"
#include "parse_json_local_storage.h"
#include <stdlib.h>
#include "write_json_for_web.h"
#include "Node_storage_data.h"
#include<string.h>

typedef enum{
    Mon,
    Tue,
    Wed,
    Thd,
    Fri,
    Sat,
    Sun,
    sizeindexday
}indexday;

typedef enum{
    t6,
    t7,
    t8,
    t9,
    t10,
    t11,
    t12,
    t13,
    t14,
    t15,
    t16,
    t17,
    sizeoftime
}kiphoc;

typedef struct Nodetime{
    char *time[sizeoftime];
}Nodetime;

typedef struct 
{
    Nodetime day[sizeindexday];
}Nodedays;


char* get_day(char* org) {
    int day = atoi(org);
    switch (day) {
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        case 7: return "Saturday";
        default: return " ";
    }
}

char* get_day_int(int org) {
    switch (org) {
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        case 7: return "Saturday";
        default: return " ";
    }
}

indexday get_indexday(char* org){
    int day = atoi(org);
    switch (day) {
        case 2: return Mon;
        case 3: return Tue;
        case 4: return Wed;
        case 5: return Thd;
        case 6: return Fri;
        case 7: return Sat;
        default: return Sun;
    }
}

// admin command
void write_timetable() {
    FILE* fp = fopen("web/plan_jerry.json", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fprintf(fp, "[\n");

    List_Data *p1 = Load_Json_Data("file/plan_jerry.json");
    List_Data *curr = p1;

    char buffer_1[5];  // Buffer size adjusted for HH:MM format
    char buffer_2[5];

    int first = 1;  // Flag to handle comma placement

    while (curr) {
        if (!first) {
            fprintf(fp, ",\n");  // Add comma before every object except the first one
        }
        first = 0;

        // Read time data and ensure buffers are adequately sized
        sscanf(curr->data->total_data[Thoi_gain], "%4s-%4s", buffer_1, buffer_2);

        // Write JSON data to the file
        fprintf(fp, "  {\n");
        fprintf(fp, "    \"class_name\": \"%s\",\n", curr->data->total_data[Ten_HP_ENG]);
        fprintf(fp, "    \"class_id\": \"%s\",\n", curr->data->total_data[MaLop]);
        fprintf(fp, "    \"room\": \"%s\",\n", curr->data->total_data[Phong]);
        fprintf(fp, "    \"formatted_time\": {\n");
        fprintf(fp, "      \"start_time\": \"%s\",\n", buffer_1);
        fprintf(fp, "      \"end_time\": \"%s\",\n", buffer_2);
        fprintf(fp, "      \"day_weeks\": \"%s\"\n", get_day(curr->data->total_data[Thu]));
        fprintf(fp, "    }\n");
        fprintf(fp, "  }");

        curr = curr->next;  // Move to the next node
    }

    fprintf(fp, "\n]\n");
    fclose(fp);
    printf("Completed\n");
}

void set_emtry(Nodedays* org){
    for (int i = 0; i < sizeindexday; i++)
    {
        for(int j = 0 ; j < sizeoftime; j++){
            if(org->day[i].time[j] == NULL){
                const char e[] = "emtry";
                org->day[i].time[j] = allocate_and_copy_string(e);
            }
        }
    }
    
}
void set_null_day(Nodedays* org){
    for (int i = 0; i < sizeindexday; i++)
    {
        for(int j = 0 ; j < sizeoftime; j++){
            
            org->day[i].time[j] = NULL;
        }
    }
    
}

void write_data_table_web(){
    FILE* fp = fopen("web/timetables.json", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    List_Data *p1 = Load_Json_Data("file/plan_jerry.json");
    List_Data *curr = p1;

    fprintf(fp, "{\n");
    fprintf(fp,"   \"days\": [\n");
    Nodedays tabledays;
    set_null_day(&tabledays);
    while (curr)
    {
        char buffer_1_h[3],buffer_1_m[3];
        char buffer_2_h[3],buffer_2_m[3];
        sscanf(curr->data->total_data[Thoi_gain],"%2s%2s-%2s%2s", buffer_1_h,buffer_1_m,buffer_2_h,buffer_2_m);
        indexday dayi = get_indexday(curr->data->total_data[Thu]);
        int start = 0,end = 0;
        start = atoi(buffer_1_h);
        end = atoi(buffer_2_h);
        if(atoi(buffer_1_m) >= 45){
            start++;
        }
        if(atoi(buffer_2_m) >= 45){
            end++;
        }
        for (int i = start-6; i <= end-6; i++) {
            if (i >= 0 && i < sizeoftime) {  // Check that i is within valid bounds
                if(tabledays.day[dayi].time[i] == NULL){
                    char buffer_all[256] = {0};
                    snprintf(buffer_all, sizeof(buffer_all), "%s=%s=%s", 
                            curr->data->total_data[MaHP], 
                            curr->data->total_data[Tuan], 
                            curr->data->total_data[Loai_lop]);
                    tabledays.day[dayi].time[i] = strdup(buffer_all);
                }
            } else {
                printf("Time index out of bounds: %d\n", i);
            }
        }

        curr = curr->next;
    }
    set_emtry(&tabledays);
    for (int i = 0; i < sizeindexday; i++)
    {
        fprintf(fp,"        {\n");
        fprintf(fp,"            \"name\": \"%s\",\n", get_day_int(i+2));
        fprintf(fp,"            \"periods\": [");
        for (int j = 0; j < sizeoftime; j++)
        {
            fprintf(fp,"\"%s\"",tabledays.day[i].time[j]);
            if(j+1 == sizeoftime){
                fprintf(fp,"]\n");
            }else{
                fprintf(fp,", ");
            }
        }
        fprintf(fp,"        }");
        if(i+1 == sizeindexday){
            fprintf(fp,"\n");
        }else{
            fprintf(fp,",\n");
        }
    }
    fprintf(fp,"    ]\n");
    fprintf(fp,"}");
    fclose(fp);

    for (int i = 0; i < sizeindexday; i++) {
        for (int j = 0; j < sizeoftime; j++) {
            if (tabledays.day[i].time[j] != NULL) {
                free(tabledays.day[i].time[j]);  // Free allocated memory
            }
        }
    }   


    free_list_data(&p1);
    return;
}