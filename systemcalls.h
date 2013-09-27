#include <lib.h>
#include <unistd.h>
#include <minix/callnr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 int IGLookup(int groups[]){
 message m;  
    m.m7_p1 = groups;

    return(_syscall( PM_PROC_NR, 45, &m ));

}

 int IGCreate(int * groupNo){
message m;

	m.m7_p1 = groupNo;
    
	return (_syscall( PM_PROC_NR, 69, &m ));
}

 int IGDelete(int groupNo){
message m;

	m.m7_i1 = (int)groupNo;
	
	return(_syscall( PM_PROC_NR, 70, &m ));

}

 int IGPublisher(int groupNo){
message m;
   m.m7_i1=(int)groupNo;
   m.m7_i2 = (pid_t)getpid();
   return( _syscall( PM_PROC_NR, 83, &m ) );

}

 int IGSubscriber(int groupNo){
 message m;
   m.m7_i1=groupNo;
   m.m7_i2 = (pid_t)getpid();
   return( _syscall( PM_PROC_NR, 84, &m ) );
}

 int IGPublish(int groupNo, char *msg){
message m;
   char *p=msg;
   m.m7_i1 = groupNo;
   m.m7_i2 = (pid_t)getpid();
   m.m7_p1 = msg;
   return( _syscall( PM_PROC_NR, 49, &m ) );

}

 int IGRetreive(int groupNo, char *msg){
 message m;	
   m.m7_i1 = groupNo;
   m.m7_p1 = msg;
   m.m7_i2 = (pid_t)getpid();
   return(_syscall( PM_PROC_NR, 50, &m ));

}

 int leaveGroupSubsrciber(int groupNo){
message m;
	m.m7_i1 = groupNo;
	m.m7_i2 = getpid();
	return (_syscall( PM_PROC_NR, 106, &m ));
}

 int leaveGroupPublisher(int groupNo){
message m;
	m.m7_i1 = groupNo;
	m.m7_i2 = getpid();
   	return(_syscall( PM_PROC_NR, 105, &m ));

}

