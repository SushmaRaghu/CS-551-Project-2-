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
int reset();



int main(){

//    while (true) {
    
int option ;

printf("Hi.. Welcome to the application\n");
printf("Here is a list of things that can be done in the application: For any option, please enter the group_id\n");
printf("1. Create a group \n");
printf("2. Can look up for the existing groups\n");
printf("3. Can subscribe as a client for an existing group\n");
printf("4. Can become a publisher for a group\n");
printf("5. Can send a message\n");
printf("6. Can receive a message\n");
printf("7. Delete a group \n");
printf("8. Reset MINIX\n");
printf("9. Exit\n");


printf("Please enter your option\n");
scanf("%d", &option);


switch(option){
case 1: create_a_group(); break;
case 2: look_up_for_a_group();break;
case 3: act_as_a_subscriber();break;
case 4: act_as_a_publisher();break;
case 5: publish();break;
case 6: retreive();break;
case 7: delete_a_group();break;
case 8: exit(0);
default:  break;

}
    }
//}



int create_a_group(){
int group_id;
char name[50]={0};
int newGroup;

printf("enter the name u want to associate to the group\n");
scanf("%s", name);

printf("name in entry file is %s", name);
    newGroup = IG_Create(&group_id,name);
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
newGroup =  IG_Lookup(&group_id);
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
    int publisher_id = 0;
    char *choice;

int newGroup1;
    int newGroup2;
newGroup1 = IG_Lookup(&group_id);
    printf("\nEnter group Id for which you want to be publisher:");
    scanf("%d",&group_id);
    printf("\nDo you have a publisher_id?(y/n)");
    scanf("%s",choice);
    if(strcmp(choice,"y") == 0){
        printf("\nEnter publisher id:");
        scanf("%d",&publisher_id);
    }
    


newGroup2 = IG_Publisher(group_id,publisher_id);
    if(newGroup2 == -1) {
           printf("Registering as a publiseher failed\n");
           return -1;
        }else{
           printf("Registering as a publiseher succeeded\n");
		   return 1;
        }

    

};

int act_as_a_subscriber(){
int group_id;
int newGroup;
    char *choice;
    int subscriber_id =0;
    printf("\nEnter group Id for which you want to be subscriber:");
    scanf("%d",&group_id);
    printf("\nDo you have a subsciber_id?(y/n)");
    scanf("%s",choice);
    if(strcmp(choice,"y") == 0){
        printf("\nEnter subscriber id:");
        scanf("%d",&subscriber_id);
    }

    newGroup = IG_Subscriber(group_id,subscriber_id);
    if(newGroup == -1) {
           printf("Registering as a subscribr failed\n");
           return -1;
        }else{
           printf("Registering as a subscriber succeeded\n");
		   return 1;
        }
};


int publish(){
int group_id,publisher_id;

int newGroup;
//char message[200] ={0};
//    char *message = "";
    
    printf("\nEnter your publisher id");
    scanf("%d",&publisher_id);
    printf("\nEnter the group id you wish to publish to:");
    scanf("%d",&group_id);

    char m;
    char message[200];
    strcpy(message,"");
    
    // READ till eof
    while(getc(stdin) != '\n'){
    }
    
    printf("\nEnter the message you wish to publish");
    while((m = getc(stdin)) != '\n'){
        int len = strlen(message);
        message[len] = m;
        message[len+1] = '\0';
    }
    printf("\nMessage is :%s",message);
    newGroup = IG_Publish(group_id,publisher_id,message);
    if(newGroup == -1) {
           printf("Publishing message failed\n");
           return -1;
        }else{
           printf("Publishing succeeded\n");
		   return 1;
        }

    

};

int retreive(){
int group_id,subscriber_id;

int newGroup;
char message[200]={0};

    printf("\nEnter your subscriber id");
    scanf("%d",&subscriber_id);
    printf("\nEnter the group id from which u want to receive from:");
    scanf("%d",&group_id);
    
 
newGroup = IG_Retreive(group_id,subscriber_id,message);
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
    printf("\nEnter group Id you want to delete:");
    scanf("%d",&group_id);

 
 
newGroup = IG_Delete(group_id);
    if(newGroup == -1) {
           printf("deletion failed\n");
           return -1;
        }else{
           printf("Deletion succeeded\n");
		   return 1;
        }

    

};



