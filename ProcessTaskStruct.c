#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include "process_task_struct.h"
//#include "stdio.h"
//#include <../include/linux/errno.h>
asmlinkage long sys_listProcessInfo(long p_id, char* file_name) 
{   

     struct task_struct *proces;

  //  char output[1000];
  // FILE *fptr;

  // fptr = open(file_name,"w");
  // if(fptr == NULL){
  // printk("Error Reading file. Error no = o %d \n",errno); 
  // return 0;
   //}
   int flag=0;
    for_each_process(proces) {
 
   if((long)task_pid_nr(proces)==p_id){
	
    flag=1;

    printk(
      "Process: %s\n \
       PID_Number: %ld\n \
       Process State: %ld\n \
       Priority: %ld\n \
       RT_Priority: %ld\n \
       Static Priority: %ld\n \
       Normal Priority: %ld\n", \
       proces->comm, \
       (long)task_pid_nr(proces), \
       (long)proces->state, \
       (long)proces->prio, \
       (long)proces->rt_priority, \
       (long)proces->static_prio, \
       (long)proces->normal_prio \
    );
 
/*
fprintf(fptr,
      "Process: %s\n \
       PID_Number: %ld\n \
       Process State: %ld\n \
       Priority: %ld\n \
       RT_Priority: %ld\n \
       Static Priority: %ld\n \
       Normal Priority: %ld\n", \
       proces->comm, \
       (long)task_pid_nr(proces), \
       (long)proces->state, \
       (long)proces->prio, \
       (long)proces->rt_priority, \
       (long)proces->static_prio, \
       (long)proces->normal_prio \
    );  
*/  
   if(proces->parent) 
      printk(
        "Parent process: %s, \
         PID_Number: %ld", \ 
         proces->parent->comm, \
         (long)task_pid_nr(proces->parent) \
      );
  
   printk("\n\n");
/*
fprint(fptr,
        "Parent process: %s, \
         PID_Number: %ld \n\n", \ 
         proces->parent->comm, \
         (long)task_pid_nr(proces->parent) \
      );
  
   
*/  
 }
//  fclose(fptr);  

  }

if(flag==0){
printk("No process with PID %ld\n",p_id);
}
  

  return 0;
}
