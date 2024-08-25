#include<stdio.h>
#include<string.h>

#include "Node_storage_data.h"
#include "parse_json_local_storage.h"
#include "Node_struct.h"
#include "Logic.h"


List_Data* Show_SAME(List_Data* p1,List_Data* p2,typecompare_flag f){
    List_Data* result = NULL;
    if(f & FLAG_SUBJECT){
        // Subject
        List_Data* curr = p1;
        while (curr)
        {
            List_Data* temp = find2(p2,curr->data->total_data[Ten_HP_ENG],Ten_HP_ENG,curr->data->total_data[Loai_lop],Loai_lop);
            if(temp){
                printf("You have the save subject is:\n");
                show_list(temp);
                printf("Enter to continue...");getchar();
            }
            free_list_data(&temp);
            
            curr = curr->next;
        }
    }else if(f & FLAG_TIME){
        printf("Comming soon\n");
    }else{
        return NULL;
    }
    return NULL;
}

void PayLoad(const char* person1, const char* person2){
    List_Data *p1,*p2;
    p1 = Load_Json_Data(person1);
    p2 = Load_Json_Data(person2);
    Show_SAME(p1,p2,FLAG_SUBJECT);
    free_list_data(&p1);
    free_list_data(&p2);
}
