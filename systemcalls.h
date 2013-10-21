#include <lib.h>
#include <unistd.h>
#include <minix/callnr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 int IG_Lookup(int groups[]){
     message m;
//     m.m7_p1 = groups;
     return(_syscall( PM_PROC_NR, IGLOOKUP, &m ));
 }

  int IG_Create(int * groupId){
 
      message m;

      m.m7_p1 = groupId;
    
      return (_syscall( PM_PROC_NR, IGCREATE, &m ));
}

 int IG_Delete(int groupNo){
message m;

	m.m7_i1 = (int)groupNo;
	
	return(_syscall( PM_PROC_NR, IGDELETE, &m ));

}

 int IG_Publisher(int groupNo,int publisher_id){
message m;
   m.m7_i1=(int)groupNo;
     m.m7_i2 = (int) publisher_id;
   return( _syscall( PM_PROC_NR, IGPUBLISHER, &m ) );

}

 int IG_Subscriber(int groupNo,int subscriber_id){
     message m;
	m.m7_i1=groupNo;
     m.m7_i2 = (int)  subscriber_id;
   return( _syscall( PM_PROC_NR, IGSUBSCRIBER, &m ) );
}

 int IG_Publish(int groupNo,int publisher_id, char *msg){
message m;
   char *p=msg;
   m.m7_i1 = groupNo;
     m.m7_i2 = publisher_id;
   m.m7_p1 = msg;
   return( _syscall( PM_PROC_NR, IGPUBLISH, &m ) );

}

 int IG_Retreive(int groupNo,int subscriber_id, char *msg){
 message m;	
   m.m7_i1 = groupNo;
   m.m7_p1 = msg;
     m.m7_i2 = subscriber_id;
   return(_syscall( PM_PROC_NR, IGRETRIEVE, &m ));

}

 int IG_getBackToOriginalMINIX(void)
{
	message m;
   	return(_syscall( PM_PROC_NR, IGRESET, &m ));
}
 
