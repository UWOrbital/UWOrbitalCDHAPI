#ifndef SYS_STAT_SERVICE_H
#define SYS_STAT_SERVICE_H

/**
* Service responsible for reboot, emergency mode, and resolving system errors
*/


/**
  System health data encompassing all submodules 
*/
typedef struct {
	// TODO: Add important system health parameters
} sys_health_t;

/**
  Reboots the system.
  Should only be used if necessary.
  @return 1 if success, 0 on fail
*/
int sys_reboot(void);

/**
  Changes state of satellite to emergency mode in the case of an error.
  Should be used purely as a state changer
  @return 1 if successful state change, else 0 on fail
*/
int sys_emergency_state(void);

/**
  Chooses how to handle the error, should use system reboot as last resort.
  @param TODO: Add parameters (error causing error handler etc.)
  @param sys_health current system health data 
  @return handling function
*/
int sys_error_handler(sys_health_t *sys_health);

/**
  Error handling functions below
*/

// TODO: Implement error handling functions as needed, will depend on system health params

#endif