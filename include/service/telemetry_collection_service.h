/*
* Service responsible for collecting and sending telemetry to comms.
* Ensures data transmitted at the right time.
*/

/*
* Sends a request to submodule, collects telemetry and store in a buffer.
* TODO: Add parameters (port for connection, buffer etc.)
* return 0 if successful, else error code
*/
int collect_telemetry();

/*
* Sends data to a submodule, store response in a buffer.
* TODO: Add parameters (port for connection, buffer etc.)
* return 0 if successful, else error code
*/
int send_telemetry();


/*
* We may need to write a conversion function for every struct
*/

/*
* Converts the struct to a character buffer
* TODO: Add parameters (struct, buffer, etc.)
* return 0 if successful, else error code
*/
int struct_to_char_buff();

/*
* Converts the buffer (should be in the form of a char[]) to a struct
* TODO: Add parameters (struct, buffer, etc.)
* return 0 if successful, else error code
*/
int char_buff_to_struct();