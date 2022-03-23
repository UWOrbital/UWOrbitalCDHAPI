/*
* Service responsible for reboot, emergency mode, and resolving system errors
*/


/*
* System health data encompassing all submodules 
*/
typedef struct {
	// TODO: Add important system health parameters
} sys_health_t;

/*
* Reboots the system.
* Should only be used if necessary.
* @return 0 if successful, else error code
*/
int sys_reboot(void);

/*
* Changes state of satellite to emergency mode in the case of an error.
* Should be used purely as a state changer
* @return 0 if successful state chance, else error code
*/
int sys_emergency_state();

/*
* Chooses how to handle the error, should use system reboot as last resort.
* @param TODO: Add parameters (error causing error handler etc.)
* @return handling function success or error code
*/
int sys_error_handler();

/*
*  Error handling functions below
*/

// TODO: Implement error handling functions as needed, will depend on system health params