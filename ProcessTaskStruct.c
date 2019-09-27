#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include "process_task_struct.h"
#include <linux/module.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>
asmlinkage long sys_listProcessInfo(long p_id, char* file_name) 
{   

   struct task_struct *proces;

  int flag=0;
  char* data;

  struct file *file;
  loff_t pos = 0;
  int fd;
  char buf[1];
  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);


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

    sprintf(data,
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

  
   printk("\n\n");

 }

  }

if(flag==0){
printk("No process with PID %ld\n",p_id);
sprintf(data,"No process with PID %ld\n",p_id);
}


  fd = sys_open(file_name, O_WRONLY | O_CREATE , 0644);
  if(fd>=0){
    sys_write(fd,data,strlen(data));
    file=fget(fd);
    if(file){
      vfs_write(file,data,strlen(data),&pos);
      fput(file);
    }
    sys_close(fd);
  }
  else{
    printk("Error in reading file.");
  }
  set_fs(old_fs);

  return 0;
}
