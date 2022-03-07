/*
* Service responsible for reboot, emergency mode, and resolving system errors
*/

/*
* Reboots the system.
* Should only be used if necessary.
* return 0 if successful, else error code
*/
int sys_reboot(void);

/*
* Changes state of satellite to emergency mode in the case of an error.
* Appropriately chooses how to handle the error, use system reboot as last resort.
* param error, the error causing the emergency
* return result of error handler response
*/
int sys_emergency_state();

/*
*  Error handling functions below
*/