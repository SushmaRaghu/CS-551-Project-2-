#include<stdio.h>
#include<string.h>


int main(){

int option=0;
int group_id;

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
scanf("%d , %d", option,group_id);


switch(option){
case 1: look_up_for_a_group(group_id); break;
case 2: create_a_group(group_id);break;
case 3: subscribe(group_id);break;
case 4: act_as_a_publisher(group_id);break;
case 5: unsubscribe_from_a_group(group_id);break;
case 6: send_a_message(group_id);break;
case 7: receive_a_message(group_id);break;
case 8: leave_a_group_as_publisher(group_id);break;
case 9: delete_a_group(group_id);break;
default: exit 0; break;

}


void look_up_for_a_group(int group_id){

/* call IG_Lookup();
if the group exists, return success
else throw an error */

}

void create_a_group(int group_id){

/* call IG_Create();
create a group,if sucessful, return success
else throw an error */

}

void subscribe(int group_id){

/* call IG_Subscriber();
if the group exists, add this as a client and return success
else throw an error */


}

void act_as_a_publisher(int group_id){


/* call IG_Publisher();
if the group exists, make this proces as a publisher, notify all clients in that group(if possible) return success
else throw an error */
}

void unsubcribe_from_a_group(int group_id){

/* call leaveGroupSubsrciber();
if the group exists, remove this process , notify all(if possible)return success
else throw an error */

}

void send_a_message(int group_id){

/* call IG_Publish();
if the group exists, send  message , return success
else throw an error */


}

void receive_a_message(int group_id){


/* call IG_Retrieve();
if the group exists, recevie the message ,  return success
else throw an error */
}


void leave_group_as_publisher(int group_id){


/* call leaveGroupPublisher();
if the group exists, remove this process as a pubisher, notify all(if possible) : decision to be taken to have this process still in the group as a client or remove  return success
else throw an error */
}

void delete_a_group(int group_id){


/* call IG_Delete();
if the group exists, remove all process ,  return success
else throw an error */

}
}
