#include <telemetry_collection_service.h>

#include <csp/csp.h>

// Command Codes
// values can be subject to change
#define CMD_DUMMY 0x01
#define CMD_GET_PARAM 0x02

// Command execution option
#define ON_REAL_TIME 0x01

/*
  outbuf should be 2 chars larger than aux_buffer, aux_buffer should be 254 chars max for now
  TODO: add check to make sure aux_butter isnt too large
*/

// same as sfsf get command
int collect_telemetry(uint8_t prio, subsystem_address_t dest, subsystem_port_t port, uint32_t timeout, void * aux_buffer, int outlen, void * inbuf, int inlen) {
    char outbuf[256];
    snprintf(outbuf, sizeof(outbuf), "%c%c", CMD_GET_PARAM, ON_REAL_TIME);
    return csp_transaction(prio, dest, port, timeout, outbuf, outlen, inbuf, inlen);
}

// buffer doesn't need a command to send data, can just use dummy command
int send_telemetry(uint8_t prio, subsystem_address_t dest, subsystem_port_t port, uint32_t timeout, void * aux_buffer, int outlen, void * inbuf, int inlen) {
    char outbuf[256];
    snprintf(outbuf, sizeof(outbuf), "%c%c", CMD_DUMMY, ON_REAL_TIME);
    return csp_transaction(prio, dest, port, timeout, outbuf, outlen, inbuf, inlen);
}

int struct_to_char_buff(void * inbuf, uint32_t inlen, subsystem_parameters_t subsystem_param) {
    // choose which helper to call
    switch(subsystem_param) {
        default:
            break;
    }
    return 1;
}

int char_buff_to_struct(void * outbuf, uint32_t outlen, subsystem_parameters_t subsystem_param) {
    // choose which helper to call
    switch(subsystem_param) {
        default:
            break;
    }
    return 1;
}