#include<stdio.h>
#include<string.h>

#include "Node_storage_data.h"
#include "parse_json_local_storage.h"
#include "Node_struct.h"
#include "Logic.h"

char getDetail(){
    char c;
        do{
            printf("Want show All detail or Not(Y/n):");c = getchar();
            char tp;
            while(tp = getchar() && tp == '\n');
            if(c != 'Y' || c != 'y' || c != 'N' || c != 'n')break;
        }while(1);
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
    List_Data *p1,*p2;
    p1 = Load_Json_Data(person1);
    p2 = Load_Json_Data(person2);
    int command;
    do{
        printf("What type do you want to compare\n"
            "1.ID of Subject\n"
            "2.Time\n"
            "3.Name of Subject\n"
            "0.for end program\n"
            "please enter 1-3 to seletion: ");scanf("%d", &command);
        if(command < 0 || command > 3){
            printf("Please Enter again to correct command\n");
        }else if(command == 1 || command == 2 || command == 3){
            char tp;
            while(tp = getchar() && tp == '\n');
            switch (command)
            {
                case 1:Show_SAME(p1,p2,FLAG_ID);break;
                case 2:Show_SAME(p1,p2,FLAG_TIME);break;
                case 3:Show_SAME(p1,p2,FLAG_SUBJECT);break;
                default:break;
            }
        }else{
            printf("Thank you\n");
            break;
        }
        
    }while(1);
    
    free_list_data(&p1);
    free_list_data(&p2);
}
