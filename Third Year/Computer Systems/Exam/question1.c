int debug_get_long (int processid, long *targetaddr, long *result){
	
	//Copies the process table into a new pagetable
	x86_64_pagetable* pagetable = copy_pagetable(current->p_pagetable,processes[processid].p_pid);

	//Finds virtual memory addr from pagetable
 	vamapping temp = virtual_memory_lookup(pagetable,targetaddr);

 	//If the physical address does not exist
 	if(temp.pa == -1)
 		return 0
 	
 	//Sets the pointer of result to the physical address 
 	result = temp.pa;
 	return 1;

}

//Case statement
case SYS_DEBUG_GET_LONG: {

	//If target addr is invalid
 	if(targetaddr > MEMSIZE_VIRTUAL || targetaddr < 0){
 		break;
 	}

 	//if process ID is invalid
 	if(processid != 0){
 		break;
 	}

 	//call to function
 	debug_get_long(processid,targetaddr,result);



 }
