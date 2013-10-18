/* If there were any type definitions local to the Process Manager, they would
 * be here.  This file is included only for symmetry with the kernel and File
 * System, which do have some local type definitions.
 */
 
 /* PROJECT 2 */
 
 #define LENGTH 100

struct blockedPublisher
{
    int publisher_pid;  
    int group_id; 
    int publisher;  
    int unblocked;  
    char msg[LENGTH];
    message store;  
    struct blockedPublisher *next;
};
typedef struct blockedPublisher* BLOCKED_PROCESSES;

