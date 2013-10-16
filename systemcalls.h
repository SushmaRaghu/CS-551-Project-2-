#include <lib.h>
#include <unistd.h>
#include <minix/callnr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 int IG_Lookup(int groups[]){
    message m;  
   //m.m7_p1 = groups;

    return(_syscall( PM_PROC_NR, 45, &m ));

}

  int IG_Create(int * groupId){
 
  message m;

	//m.m7_p1 = groupId;
    
	return (_syscall( PM_PROC_NR, 114, &m ));
}

 int IG_Delete(int groupNo){
message m;

	m.m7_i1 = (int)groupNo;
	
	return(_syscall( PM_PROC_NR, 70, &m ));

}

 int IG_Publisher(int groupNo){
message m;
   m.m7_i1=(int)groupNo;
   m.m7_i2 = (pid_t)getpid();
   return( _syscall( PM_PROC_NR, 83, &m ) );

}

 int IG_Subscriber(int groupNo){
 message m;
   m.m7_i1=groupNo;
   m.m7_i2 = (pid_t)getpid();
   return( _syscall( PM_PROC_NR, 84, &m ) );
}

 int IG_Publish(int groupNo, char *msg){
message m;
   char *p=msg;
   m.m7_i1 = groupNo;
   m.m7_i2 = (pid_t)getpid();
   m.m7_p1 = msg;
   return( _syscall( PM_PROC_NR, 49, &m ) );

}

 int IG_Retreive(int groupNo, char *msg){
 message m;	
   m.m7_i1 = groupNo;
   m.m7_p1 = msg;
   m.m7_i2 = (pid_t)getpid();
   return(_syscall( PM_PROC_NR, 50, &m ));

}

 int leave_Group_Subsrciber(int groupNo){
message m;
	m.m7_i1 = groupNo;
	m.m7_i2 = getpid();
	return (_syscall( PM_PROC_NR, 106, &m ));
}

 int leave_Group_Publisher(int groupNo){
message m;
	m.m7_i1 = groupNo;
	m.m7_i2 = getpid();
   	return(_syscall( PM_PROC_NR, 105, &m ));

}

