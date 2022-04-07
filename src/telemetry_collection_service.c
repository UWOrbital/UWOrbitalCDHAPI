#include <telemetry_collection_service.h>

#include <csp/csp.h>

int collect_telemetry() {

}

int send_telemetry(uint8_t prio, uint8_t dest, subsystem_port_t port, uint32_t timeout, void * outbuf, int outlen, void * inbuf, int inlen) {
    return csp_transaction(prio, dest, port, timeout, outbuf, outlen, inbuf, inlen);
}

int struct_to_char_buff(void * inbuf, uint32_t inlen) {

}

int char_buff_to_struct(void * outbuf, uint32_t outlen) {

}