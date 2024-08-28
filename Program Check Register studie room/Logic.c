#include<stdio.h>
#include<string.h>

#include "Node_storage_data.h"
#include "parse_json_local_storage.h"
#include "Node_struct.h"
#include "Logic.h"
#include "parse_malop_for_dang_ki.h"

char getDetail() {
    char c;
    do {
        printf("Want show All detail or Not (Y/n): ");
        c = getchar();

        // Clear the input buffer
        char tp;
        while ((tp = getchar()) != '\n' && tp != EOF);

        // Check if the input is valid
        if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') {
            break;
        } else {
            printf("Invalid input, please enter Y or N.\n");
        }
    } while (1);

    return c;
}

void Show_byDetail(List_Data* src,List_Data* p2,char detail,ID type){
    List_Data* curr = src;
    while (curr)
        {
            List_Data* temp = find2(p2,curr->data->total_data[type],type,curr->data->total_data[Loai_lop],Loai_lop);
            if(temp){
                
                if(detail == 'N' || detail == 'n'){
                    List_Data* curr2 = temp;
                    printf("You have the save subject is:\n");
                    while (curr2)
                    {
                        show_one_two_topic_by_id(curr2->data,MaHP,Ten_HP_ENG);
                        printf("Enter to continue...");getchar();
                        curr2 = curr2->next;
                    }
                }else if(detail == 'Y' || detail == 'y'){
                    printf("You have the save subject is:\n");
                    show_list(temp);
                    printf("Enter to continue...");getchar();
                }
            }
            free_list_data(&temp);
            
            curr = curr->next;
        }
}

void Show_SAME(List_Data* p1,List_Data* p2,typecompare_flag f){
    char detail = getDetail();
   switch (f)
   {
   case FLAG_ID:Show_byDetail(p1,p2,detail,MaHP);break;
   case FLAG_TIME:printf("Comming Soon\n");break;
   case FLAG_SUBJECT:Show_byDetail(p1,p2,detail,Ten_HP_ENG);break;
   default:break;
   }
}

void PayLoad(const char* person1, const char* person2){
    List_Data *p1 = NULL, *p2 = NULL;
    p1 = Load_Json_Data(person1);
    p2 = Load_Json_Data(person2);

    if (!p1 || !p2) {
        printf("Failed to load JSON data\n");
        free_list_data(&p1);
        free_list_data(&p2);
        return;
    }

    int command;
    do {
        printf("What type do you want to compare\n"
            "1.ID of Subject\n"
            "2.Time\n"
            "3.Name of Subject\n"
            "4.Get File ID of Room for register in web university\n"
            "0.for end program\n"
            "please enter 1-4 to selection: ");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n');  // Clear the input buffer
            printf("Invalid input, please enter a number between 0 and 4.\n");
            continue;
        }

        while (getchar() != '\n');  // Clear any leftover newline characters

        if (command < 0 || command > 4) {
            printf("Please Enter again to correct command\n");
        } else {
            switch (command) {
                case 1: Show_SAME(p1, p2, FLAG_ID); break;
                case 2: Show_SAME(p1, p2, FLAG_TIME); break;
                case 3: Show_SAME(p1, p2, FLAG_SUBJECT); break;
                case 4: write_txt(person1, person2, p1, p2); break;
                default: break;
            }
        }
    } while (command != 0);

    
    free_list_data(&p1);
    free_list_data(&p2);
}
