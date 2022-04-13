#ifndef TLM_COLL_SERVICE_H
#define TLM_COLL_SERVICE_H

/**
* Service responsible for collecting and sending telemetry to comms.
* Ensures data transmitted at the right time.
*/

// CSP Includes
#include <csp/csp.h>

/**
 * @enum subsystem_port_t
 * @brief Maps each subsystem to a port
 */
typedef enum {
    // TODO: Change numbers to be real ports which are TBD
    CDH_PORT = 0,
    COMMS_PORT = 1,
    ADCS_PORT = 2
} subsystem_port_t;

/**
 * @enum 
 * @brief Maps data structure of team to placeholder int
 */
typedef enum {
    // TODO: modify when we figure out which subsystems need their own structs
    CDH_PARAM = 0,
    COMMS_PARAM = 1,
    EPS_PARAM = 2
} subsystem_parameters_t;

/**
 * @enum subsystem_address_t
 * @brief Maps each subsystem to an address
 */
typedef enum {
    // TODO: Change numbers to be real addresses which are TBD
    CDH_ADDRESS = 0,
    COMMS_ADDRESS = 1,
    ADCS_ADDRESS = 2
} subsystem_address_t;

/**
 * @brief store EPS subsystem parameters
 */
typedef struct {
	  // TODO
    int sys_temp;
} eps_sys_t;

// TODO: Send and collect telemetry should be similar to
// existing csp functions. Should use existing functions
// when possible

// TODO: Figure out if this is necessary or if built in
// get command in sfsf will suffice
/**
  Sends a request to submodule, collects telemetry and store in a buffer. Usually a get command.
  @param[in] prio priority, see #csp_prio_t
  @param[in] dest destination address
  @param[in] port destination based on submodule
  @param[in] timeout timeout in mS to wait for a reply
  @param[in] aux_buffer outgoing data (request) excluding command, should be 254 max
  @param[in] outlen length of data in \a outbuf (request)
  @param[out] inbuf user provided buffer for receiving data (reply)
  @param[in] inlen length of expected reply, -1 for unknown size (inbuf MUST be large enough), 0 for no reply.
  @return 1 or reply size on success, 0 on failure (error, incoming length does not match, timeout)
*/
int collect_telemetry(uint8_t prio, subsystem_address_t dest, subsystem_port_t port, uint32_t timeout, void * aux_buffer, int outlen, void * inbuf, int inlen);

/**
  Sends data to a submodule, store response in a buffer. Parameters almost identical to csp_transaction. Usually a set command.
  @param[in] prio priority, see #csp_prio_t
  @param[in] dest destination address
  @param[in] port destination based on submodule
  @param[in] timeout timeout in mS to wait for a reply
  @param[in] aux_buffer outgoing data (request) excluding command, should be 254 max
  @param[in] outlen length of data in \a outbuf (request)
  @param[out] inbuf user provided buffer for receiving data (reply)
  @param[in] inlen length of expected reply, -1 for unknown size (inbuf MUST be large enough), 0 for no reply.
  @return 1 or reply size on success, 0 on failure (error, incoming length does not match, timeout)
*/
int send_telemetry(uint8_t prio, subsystem_address_t dest, subsystem_port_t port, uint32_t timeout, void * aux_buffer, int outlen, void * inbuf, int inlen);
 

/**
  We may need to write a conversion function for every struct
*/

/**
  Converts the struct to a character buffer
  @param struct TODO: needs to be a specific struct
  @param inbuf user provided buffer for storing converted struct
  @param inlen length of expected buffer after conversion
  @param subsystem_param which type of struct we are converting
  @return 1 or buffer size on success, 0 on failure
*/
int struct_to_char_buff(void * inbuf, uint32_t inlen, subsystem_parameters_t subsystem_param);

/**
  Converts the buffer (should be in the form of a char[]) to a struct
  @param TODO: Add parameters (struct, buffer, etc.)
  @param struct TODO: needs to be a specific struct
  @param outbuf outgoing data to be converted to struct
  @param outlen length of outgoing data
  @param subsystem_param which type of struct we are converting
  @return 1 on success, 0 on failure
*/
int char_buff_to_struct(void * outbuf, uint32_t outlen, subsystem_parameters_t subsystem_param);

#endif