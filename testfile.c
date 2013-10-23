#include<stdio.h>
#include<string.h>
#include "systemcalls.h"



int publish_interestgroup_not_present(void);
int publish_interestgroup_pub_not_belong(void);
int subscribe_interestgroup_not_present(void);
int subscribe_interestgroup_pub_not_belong(void);
int subscriber_read_empty_buffer(void);
int subscriber_read_more_than_msgs_present(void);
int publish_input_more_than_five_msgs(void);
int publisher_subscribing(void);
int subscriber_publishing(void);

int main(int argc, char** argv)
{

    char input=-1;

    printf("Testing Project 2: Publish and Subscribe IPC's \n");
    printf(" \n");
    printf("\n The following scenarios can be tested \n");

    while(1)
    {
        printf("1) Publisher publishing to an interestgroup that is not present \n");
        printf("2) Publisher publishing to an interestgroup that a publisher does not belong to \n");
        printf("3) Subscriber subscribing to an interestgroup that is not present\n");
        printf("4) Subscriber subscribing to an interestgroup that a subscriber does not belong to \n");
        printf("5) Subscriber reading  empty buffer \n");
        printf("6) Subscriber reading more messages than the actual present in the buffer\n");
        printf("7) Publisher publishing more than message count limit(>5) \n");
        printf("8) Publisher subscribing from a valid interest group\n");
        printf("9) Subscriber publishing to a valid interest group\n");
        printf("0) Exit the Program \n\n");


        printf("Please choose one option  ");
        scanf(" %c",&input);


        switch(input)
        {
        case '1' :
            publish_interestgroup_not_present();
            break;
        case '2' :
            publish_interestgroup_pub_not_belong();
            break;
        case '3' :
            subscribe_interestgroup_not_present();
            break;
        case '4' :
            subscribe_interestgroup_pub_not_belong();
            break;
        case '5' :
            subscriber_read_empty_buffer();
            break;
        case '6' :
            subscriber_read_more_than_msgs_present();
            break;
        case '7' :
            publish_input_more_than_five_msgs();
            break;
        case '8' :
            publisher_subscribing();
            break;
        case '9' :
            subscriber_publishing();
            break;
        case '0' :
            exit(0);
            break;
        default :
            printf("Wrong Input \n");
            break;
        }
    }

}

int publish_interestgroup_not_present(void)  /*Case 1*/
{
    int publisher_pid,group_Id;
    int group;
    char *name;
    char *choice;
    int publisher_id = 0;

    //resetAll();

    printf(" Test :Publisher publishing to an interestgroup that is not present \n");

    /*
    		printf("\n This test will perform the following: \n");
    		printf("1) Create an Interest Group \n");
            printf("2) Register a publisher \n");
            printf("3) Publish to an interestgroup that is not present \n");
            */

    group = IG_Create(&group_Id,name);

    if(group == -1)
    {

        printf("Fail:Add of a  interestgroup failed\n");
        return -1;
    }
    else
    {
        printf("Success:Add of  interestgroup groupid passed=%d\n",group_Id);
    }

    if((publisher_pid =fork())== 0)
    {
        printf("Publisher Registering \n");

        printf("\n Do you have a publisher id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\n Enter publisher id:");
            scanf("%d",&publisher_id);
        }

        group=IG_Publisher(group_Id+1,publisher_id);
        if(group == -1)
        {

            printf("Fail:Publisher Registering failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Publisher Registering succeeded\n");
        }
        exit(0);
    }

    waitpid(publisher_pid,NULL,0);
    printf("Test:Publisher publishing to an interestgroup that is not present PASSED\n");
    return 0;
}

int publish_interestgroup_pub_not_belong(void) /* Case 2*/
{
    int publisher_pid,group_Id1,group_Id2;
    int group;
    char message[200]= {0};
    int publisher_id = 0;
    char *choice,*name;

    //resetAll();

    printf(" Test: Publisher publishing to an interestgroup that a publisher does not belong to \n");

    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating 2 Interest Groups \n");
            printf("2. Registering a publisher to Interestgroup1 \n");
            printf("3. publisher publishes message to wrong interest group \n");
            */


    group = IG_Create(&group_Id1,name);

    if(group == -1)
    {

        printf("Fail:Add of a  interestgroup failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup group1 passed=%d\n",group_Id1);
    }

    group = IG_Create(&group_Id2,name);

    if(group == -1)
    {

        printf("Fail:Add of a  interestgroup failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup group2 passed=%d\n",group_Id2);
    }


    if((publisher_id=fork()) == 0)
    {
        printf("Publisher Registering \n");

        printf("\n Do you have a publisher id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter publisher id:");
            scanf("%d",&publisher_id);
        }

        group=IG_Publisher(group_Id1,publisher_id);
        if(group == -1)
        {
            printf("Fail:Publisher register  failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Publisher register succeded\n");
        }

        printf("\nEnter your publisher id");
        scanf("%d",&publisher_id);

        sprintf(message,"Publisher publishing message");
        printf("\n Publisher published message is: %s\n ",message);
        group=IG_Publish(group_Id2,publisher_id,message)  ;     /* Publish */
              if(group == -1)
        {

            printf("Fail:Publisher publishing message failed \n");
            exit(127);
        }
        else
        {
            printf("Success:Publisher publishing message succeded  \n");
        }
        exit(0);
    }

    waitpid(publisher_pid,NULL,0);
    printf("Test: Publisher publishing to an interestgroup that a publisher does not belong to PASSED \n");
    return 0;


}

int subscribe_interestgroup_not_present(void) /* Case 3*/
{
    int subscriber_pid,group_Id;
    int group;
    char *choice;
    int subscriber_id =0;
    //resetAll();

    printf("Test:Subscriber subscribing to an interestgroup that is not present \n");

    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating an Interest Group \n");
            printf("2. Registering a subscriber \n");
            printf("3. Subscriber reads message from an interest group that does not exist \n");
    	printf("**************************************************** \n");
    	*/
    char *name;
    group = IG_Create(&group_Id,name);


    if(group == -1)
    {

        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }


    if( (subscriber_pid=fork()) == 0)
    {
        printf("Subscriber Registering \n");

        printf("\n Do you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id+1,subscriber_id); /* Register subscriber */
        if(group == -1)
        {

            printf("Fail:Subscriber register  failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register  succeded\n");
        }
        exit(0);
    }

    waitpid(subscriber_pid,NULL,0);
    printf("Test: Subscriber subscribing to an interestgroup that is not present PASSED \n");
        return 0;

}

int subscribe_interestgroup_pub_not_belong(void) /* Case 4 */
{

    int subscriber_pid,group_Id1,group_Id2;
    int group;
    char message[200]= {0};
    char *choice;
    int subscriber_id =0;

    //resetAll();

    printf(" Test: Subscriber subscribing to an interestgroup that a subscriber does not belong to\n");
    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating 2 Interest Groups \n");
            printf("2. Registering a subscriber to Interestgroup1 \n");
            printf("3. subscriber reads message from wrong interest group \n");
    	printf("**************************************************** \n");
    	*/
    char *name;
    group = IG_Create(&group_Id1,name);

    if(group == -1)
    {

        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup group1 passed=%d\n",group_Id1);
    }

    group = IG_Create(&group_Id2,name);
    if(group == -1)
    {

        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup group2 passed=%d\n",group_Id2);
    }


    if( (subscriber_pid=fork()) == 0)
    {
        printf(" Subscriber Registering  \n");
        printf("\nDo you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\n Enter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id1+1,subscriber_id); /* Register subscriber */


        if(group == -1)
        {

            printf("Fail:Subscriber register failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register succeeded\n");
        }

        printf("\nEnter your subscriber id");
        scanf("%d",&subscriber_id);

        group=IG_Retreive(group_Id2,subscriber_id,message);      /* Retrieve */
        if(group == -1)
        {

            printf("Fail: Subscriber retrieving message failed \n");
            exit(127);
        }
        else
        {
            printf("Success: Subscriber retrieving message succeded  \n");
            printf("\n Message retrieved by subscriber is %s\n ",message);
        }

        exit(0);
    }

    waitpid(subscriber_pid,NULL,0);
    printf("Test: Subscriber subscribing to an interestgroup that a subscriber does not belong to PASSED \n");
        return 0;

}



int subscriber_read_empty_buffer(void) /* Case 5 */
{
    int subscriber_pid,group_Id;
    int group;
    char message[200]= {0};
    int subscriber_id =0;
    //resetAll();
 char *choice;
    printf(" Test: Subscriber reading  empty buffer \n");

    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating 1 Interest Groups \n");
            printf("2. Registering a subscriber to Interestgroup \n");
            printf("3. subscriber reads message from interest group but there is no message present in the group\n");
    	printf("**************************************************** \n");
    */
    char *name;
    group = IG_Create(&group_Id,name);
    if(group == -1)
    {

        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }


    if( (subscriber_pid=fork()) == 0)
    {
        printf("Subscriber Registering  \n");
        printf("\nDo you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id,subscriber_id); /* Register subscriber */

        if(group == -1)
        {

            printf("Fail:Subscriber register failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register succeeded\n");
        }

        printf("\nEnter your subscriber id");
        scanf("%d",&subscriber_id);

        group=IG_Retreive(group_Id,subscriber_id,message);      /* Retrieve */
        if(group == -1)
        {

            printf("Fail: Subscriber retrieving message failed\n");
            exit(127);
        }
        else
        {
            printf("Success: Subscriber retrieving message succeded \n");
            printf("\n Message retrieved by subscriber is %s\n ",message);
        }

        exit(0);
    }

    waitpid(subscriber_pid,NULL,0);
    printf("Test: Subscriber reading  empty buffer PASSED \n");
        return 0;


}


int subscriber_read_more_than_msgs_present(void) /* Case 6*/
{
    int publisher_pid;
    int subscriber_pid;
    int group;
    char message[200]= {0};
    int group_Id;
    int n,m;
    int publisher_id = 0;
    int subscriber_id = 0;
    char *choice;

    int input=-1;
    int No_Publisher_Messages=1;
    int No_Subscriber_Messages=2;


    //resetAll();

    printf("Test: Subscriber reading more messages than the actual present in the buffer \n");
    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating an Interest Group \n");
            printf("2. Registering 1 publishers \n");
            printf("3. Registering 1 subscribers \n");
            printf("4. publisher publishes 2 messages\n");
            printf("5. subscriber reads 3 messages \n");
    	printf("**************************************************** \n");
    	*/

    /* Create Interest group */
    char *name;
    group = IG_Create(&group_Id,name);
    if(group == -1)
    {

        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }


    /* Registering publishers */
    if((publisher_pid=fork()) == 0)
    {
        printf("Publisher Registering  \n");

        printf("\nDo you have a publisher_id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter publisher id:");
            scanf("%d",&publisher_id);
        }

        group=IG_Publisher(group_Id,publisher_id); /* Register Publisher */
        if(group == -1)
        {

            printf("Fail:Publisher register  failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Publisher register  succeeded\n");
        }

        for(m=0; m<=No_Publisher_Messages; m++)
        {
            sprintf(message,"Publisher publishing Message %d",m+1);
            printf("\n Message %d published by Publisher is: %s\n ",m+1,message);
            printf("\n Do you have a publisher id?(y/n)");
            scanf("%s",choice);
            if(strcmp(choice,"y") == 0)
            {
                printf("\nEnter publisher id:");
                scanf("%d",&publisher_id);
            }

            group=IG_Publish(group_Id,publisher_id,message);       /* Publish */
                  if(group == -1)
            {

                printf("Fail:Publisher publishing message failed %d\n",m+1);
                exit(127);
            }
            else
            {
                printf("Success:Publisher publishing message succeeded%d\n",m+1);
            }
        }
        exit(127);
    }


    /* Registering subscribers */
    sleep(2);

    if((subscriber_pid=fork()) == 0)
    {
        printf("Subscriber Registering  \n");
        printf("\nDo you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id,subscriber_id); /* Register subscriber */

        if(group == -1)
        {

            printf("Fail:Subscriber register failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register succeeded\n");
        }


        for(m=0; m<=No_Subscriber_Messages; m++)
        {
            printf("\nEnter your subscriber id");
            scanf("%d",&subscriber_id);

            group=IG_Retreive(group_Id,subscriber_id,message);/* Retrieve */


            if(group == -1)
            {

                printf("Fail: Subscriber retrieving message failed \n");
                exit(127);
            }
            else
            {
                printf("Success: Subscriber retrieving message suceeded \n");
                printf("\n Message  %d retrieved by Subscriber is: %s\n ",m+1,message);
            }
        }
        exit(127);
    }

    waitpid(subscriber_pid,NULL,0);
    waitpid(publisher_pid,NULL,0);
    printf("Test: Subscriber reading more messages than the actual present in the buffer PASSED\n");
        return 0;

}


int publish_input_more_than_five_msgs(void) /* Case 7*/
{
    int group;
    char message[200]= {0};
    int group_Id;
    int n,m;
    int publisher_id = 0;
    int subscriber_id = 0;
    char *choice;
    int publisher_pid,subscriber_pid; /* Publisher & Subscriber pid */
    int input=-1;
    int No_Publisher_Messages=6;
    int No_Subscriber_Messages=2;

   // resetAll();

    printf("Test: Publisher publishing more than message count limit(>5) \n");

    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating an Interest Group \n");
            printf("2. Registering 1 publishers \n");
            printf("3. Registering 1 subscribers \n");
            printf("4. publisher publishes 6 messages, and gets blocked at 6th Message \n");
            printf("5. subscriber reads 1 messages \n");
            printf("6. publisher now gets unblocked \n");
    	printf("**************************************************** \n");

    */
    /* Create Interest group */
    char *name;
    group = IG_Create(&group_Id,name);
    if(group == -1)
    {
        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }
    /* Registering publishers */
    if((publisher_pid=fork()) == 0)
    {
        printf("Publisher Registering \n");

        printf("\nDo you have a publisher id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter publisher id:");
            scanf("%d",&publisher_id);
        }

        group=IG_Publisher(group_Id,publisher_id); /* Register Publisher */
        if(group == -1)
        {

            printf("Fail:Publisher register  failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Publisher register  succeeded\n");
        }

        for(m=0; m<=No_Publisher_Messages; m++)
        {
            sprintf(message,"Publisher publishing Message %d",m+1);
            printf("\n Message %d published by Publisher is: %s \n ",m+1,message);
            printf("\nDo you have a publisher id?(y/n)");
            scanf("%s",choice);
            if(strcmp(choice,"y") == 0)
            {
                printf("\nEnter publisher id:");
                scanf("%d",&publisher_id);
            }

            group=IG_Publish(group_Id,publisher_id,message) ;       /* Publish */
                  if(group == -1)
            {

                printf("Fail:Publisher publishing message failed %d\n",m+1);
                exit(127);
            }
            else
            {
                printf(" Success:Publisher publishing message succeeded %d\n",m+1);
            }
        }
        exit(127);
    }



    /* Registering subscribers */
    sleep(4);
    if((subscriber_pid=fork()) == 0)
    {
        printf("Subscriber Registering  \n");
        printf("\nDo you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id,subscriber_id); /* Register subscriber */

        if(group == -1)
        {

            printf("Fail:Subscriber register failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register succeeded\n");
        }


        for(m=0; m<=No_Subscriber_Messages; m++)
        {
            printf("\nEnter your subscriber id");
            scanf("%d",&subscriber_id);

            group=IG_Retreive(group_Id,subscriber_id,message);/* Retrieve */


            if(group == -1)
            {

                printf("Fail: Subscriber retrieving message failed \n");
                exit(127);
            }
            else
            {
                printf("Success: Subscriber retrieving message succeeded \n");
                printf("\n Message  %d retrieved by Subscriber is: %s\n ",m+1,message);
            }
        }
        exit(127);
    }

    waitpid(subscriber_pid,NULL,0);
    printf("Subscribing Message Complete by Subscriber\n");
    waitpid(publisher_pid,NULL,0);
    printf("Publishing Message Complete by Publisher\n");
    printf("Test: Publisher publishing more than message count limit(>5) PASSED \n");
        return 0;

}

int publisher_subscribing(void) /*Case 8 */
{
    int publisher_pid,group_Id;
    int publisher_id =0;
    int subscriber_id = 0;
                      int group;
    char *choice;
    char message[200]= {0};

   // resetAll();

    printf(" Test: Publisher retrieving from a valid interest group \n");
    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating 1 Interest Groups \n");
            printf("2. Registering a publisher to Interestgroup \n");
            printf("3. publisher subscribes message from interest group \n");
    	printf("**************************************************** \n");
    	*/
    char *name;
    group = IG_Create(&group_Id,name);
    if(group == -1)
    {
        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }

    if((publisher_pid=fork()) == 0)
    {
        printf("Publisher Registering  \n");

        printf("\nDo you have a publisher id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter publisher id:");
            scanf("%d",&publisher_id);
        }

        group=IG_Publisher(group_Id,publisher_id); /* Register Publisher */
        if(group == -1)
        {

            printf("Fail:Publisher register  failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Publisher register  succeeded\n");
        }


        printf("\nEnter your subscriber id");
        scanf("%d",&subscriber_id);

        group=IG_Retreive(group_Id,subscriber_id,message);/* Retrieve */
        if(group == -1)
        {

            printf("Fail: Publisher retrieving message failed \n");
            exit(127);
        }
        else
        {
            printf("Success: Publisher retrieving message succeded \n");
        }
        exit(0);
    }

    waitpid(publisher_pid,NULL,0);
    printf("Test: Publisher retrieving from a valid interest group PASSED\n");
        return 0;

}

int subscriber_publishing(void) /* Case 9*/
{
    int subscriber_pid,group_Id;
    int group;
    char *choice;
    int subscriber_id =0;
    int publisher_id= 0;
    char message[200]= {0};
    char *name;

    //resetAll();

    printf(" Test: Subscriber publishing to a valid interest group \n");
    /*
    		printf("\nThis Testcase will test following: \n");
    		printf("1. Creating 1 Interest Groups \n");
            printf("2. Registering a subscriber to Interestgroup \n");
            printf("3. subscriber publishes message to interest group \n");
    	printf("**************************************************** \n");
    	*/

    group = IG_Create(&group_Id,name);
    if(group == -1)
    {
        printf("Fail:Add of a  interest group failed\n");
        return -1;
    }
    else
    {
        printf("Success :Add of  interestgroup grpid1 passed=%d\n",group_Id);
    }


    if(  (subscriber_pid=fork()) == 0)
    {
        printf("Registering subscriber \n");
        printf("\nDo you have a subscriber id?(y/n)");
        scanf("%s",choice);
        if(strcmp(choice,"y") == 0)
        {
            printf("\nEnter subscriber id:");
            scanf("%d",&subscriber_id);
        }

        group=IG_Subscriber(group_Id,subscriber_id); /* Register subscriber */

        if(group == -1)
        {

            printf("Fail:Subscriber register failed\n");
            exit(0);

        }
        else
        {
            printf("Success:Subscriber register succeeded\n");
        }


        sprintf(message,"Publisher publishing Message");
        printf("\n Enter publisher id");
        scanf("%d", &publisher_id);
        group=IG_Publish(group_Id,publisher_id,message) ;      /* Publish */
        if(group == -1)      /* Retrieve */
        {

            printf("Fail: Subscriber publishing message failed\n");
            exit(127);
        }
        else
        {
            printf("Succeded:Subscriber publishing message succeded\n");
        }

        exit(0);
    }

    waitpid(subscriber_pid,NULL,0);
    printf("Test: Subscriber publishing to a valid interest group PASSED\n");
        return 0;

}

