#include <stdio.h>
#include "Node_struct.h"
#include "parse_json_local_storage.h"
#include <string.h>
#include <stdlib.h>
#include "write_json_for_web.h"

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
