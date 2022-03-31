/**
* Service responsible for collecting and sending telemetry to comms.
* Ensures data transmitted at the right time.
*/

/**
 * Maps each subsystem to a port
 */
enum subsystem_port_t {
    // TODO: Change numbers to be real ports which are TBD
    CDH = 0,
    COMMS = 1,
    ADCS = 2
};

// TODO: Send and collect telemetry should be similar to
// existing csp functions. Should use existing functions
// when possible

// TODO: Figure out if this is necessary or if built in
// get command in sfsf will suffice
/**
  Sends a request to submodule, collects telemetry and store in a buffer.
  @param TODO: Add parameters (port for connection, buffer etc.)
  @return 0 if successful, else error code
*/
int collect_telemetry();

/**
  Sends data to a submodule, store response in a buffer.
  @param TODO: Add parameters (port for connection, buffer etc.)
  @return 0 if successful, else error code
*/
int send_telemetry();


/**
  We may need to write a conversion function for every struct
*/

/**
  Converts the struct to a character buffer
  @param struct TODO: needs to be a specific struct
  @param inbuf user provided buffer for storing converted struct
  @param inlen length of expected buffer after conversion
  @return 1 or buffer size on success, 0 on failure
*/
int struct_to_char_buff(void * inbuf, int inlen);

/**
  Converts the buffer (should be in the form of a char[]) to a struct
  @param TODO: Add parameters (struct, buffer, etc.)
  @param struct TODO: needs to be a specific struct
  @param outbuf outgoing data to be converted to struct
  @param outlen length of outgoing data
  @return 1 on success, 0 on failure
*/
int char_buff_to_struct(void * outbuf, int outlen);