#include<stdio.h>
#include<string.h>
 #include "systemcalls.h"


int create_a_group( );
int look_up_for_a_group( );
int act_as_a_publisher();
int act_as_a_subscriber();
int publish();
int retreive();
int delete_a_group();



int main(){

int option ;

printf("Hi.. Welcome to the application\n");
printf("Here is a list of things that can be done in the application: For any option, please enter the group_id\n");
printf("1. Can look up for the existing groups\n");
printf("2. Create a group\n");
printf("3. Can subscribe as a client for an existing group\n");
printf("4. Can become a publisher for a group\n");
printf("5. Can send a message\n");
printf("6. Can receive a message\n");
printf("7. Delete a group \n");


printf("Please enter your option\n");
scanf("%d", &option);


switch(option){
case 1: look_up_for_a_group(); break;
case 2: create_a_group();break;
case 3: act_as_a_subscriber();break;
case 4: act_as_a_publisher();break;
case 5: publish();break;
case 6: retreive();break;
case 7: delete_a_group();break;
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

int look_up_for_a_group(){
int group_id;

int newGroup;

 

newGroup = IG_Lookup(&group_id);
    if(newGroup == -1) {
           printf("Look up of interest group failed\n");
           return -1;
        }else{
           printf("Look up of interest group succeeded\n");
		   return 1;
        }

    

};

int act_as_a_publisher(){
int group_id;

int newGroup1;
int newGroup2;


 
newGroup1 = IG_Lookup(&group_id);
newGroup2 = IG_Publisher(group_id);
    if(newGroup2 == -1) {
           printf("Registering as a publiseher failed\n");
           return -1;
        }else{
           printf("Registering as a publiseher failed\n");
		   return 1;
        }

    

};

int act_as_a_subscriber(){
int group_id;

int newGroup;


 
 
newGroup = IG_Subscriber(group_id);
    if(newGroup == -1) {
           printf("Registering as a subscribr failed\n");
           return -1;
        }else{
           printf("Registering as a subscriber succeeded\n");
		   return 1;
        }

    

};


int publish(){
int group_id;

int newGroup;
char message[200] ={0};

  
 
newGroup = IG_Publish(group_id,message);
    if(newGroup == -1) {
           printf("Publishing message failed\n");
           return -1;
        }else{
           printf("Publishing succeeded\n");
		   return 1;
        }

    

};

int retreive(){
int group_id;

int newGroup;
char message[200]={0};

 
 
newGroup = IG_Retreive(group_id,message);
    if(newGroup == -1) {
           printf("Rx message failed\n");
           return -1;
        }else{
           printf("Rx succeeded\n");
		   return 1;
        }

    

};

int delete_a_group(){
int group_id;

int newGroup;

 
 
newGroup = IG_Delete(group_id);
    if(newGroup == -1) {
           printf("deletion failed\n");
           return -1;
        }else{
           printf("Deletion succeeded\n");
		   return 1;
        }

    

};


    

