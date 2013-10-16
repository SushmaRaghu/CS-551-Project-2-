#include<stdio.h>
#include<string.h>
#include "systemcalls.h"


int create_a_group( );



int main(){

int option ;

printf("Hi.. Welcome to the application\n");
printf("Here is a list of things that can be done in the application: For any option, please enter the group_id\n");
printf("1. Can look up for the existing groups\n");
printf("2. Create a group\n");
printf("3. Can subscribe as a client for an existing group\n");
printf("4. Can become a publisher for a group\n");
printf("5. Can unsubscribe from a group(if u r a member of any group)\n");
printf("6. Can send a message\n");
printf("7. Can receive a message\n");
printf("8. Leave a group as a publisher\n");
printf("9. Delete a group \n");


printf("Please enter your option\n");
scanf("%d", &option);


switch(option){
//case 1: look_up_for_a_group(group_id); break;
case 2: create_a_group();break;
//case 3: subscribe(group_id);break;
//case 4: act_as_a_publisher(group_id);break;
//case 5: unsubscribe_from_a_group(group_id);break;
//case 6: send_a_message(group_id);break;
//case 7: receive_a_message(group_id);break;
//case 8: leave_a_group_as_publisher(group_id);break;
//case 9: delete_a_group(group_id);break;
default:  break;

}
}

      

int create_a_group(){
int group_id;

int newGroup;

 

newGroup = IG_Create(&group_id);
    if(newGroup == -1) {
           printf("Creation of a new interest group failed\n");
           return -1;
        }else{
           printf("Creation of a new interest group succeeded\n");
		   return 1;
        }

    

};

    

