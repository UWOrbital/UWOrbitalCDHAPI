/*
Copyright 2018 olmanqj
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

/**
 * Build this example on linux with:
 * ./waf configure --enable-examples --enable-if-kiss --with-driver-usart=linux --enable-crc32 clean build
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>

#include <csp/csp.h>
#include <csp/interfaces/csp_if_kiss.h>
#include <csp/interfaces/csp_if_lo.h>
#include <csp/drivers/usart.h>
#include <csp/arch/csp_thread.h>

// Address of this node (ground station)
#define GS_ADDRESS          9

// CSP Transaction Arguments
#define PACKET_PRIO         2
#define DEST_ADDRESS        1
#define CMD_PORT            11
#define TRANSACTION_TIMEOUT 400

// Command Codes
#define CMD_DUMMY           0x01
#define CMD_GET_PARAM       0x02
#define CMD_SET_PARAM       0x03
#define CMD_REBOOT_OBC      0x04

// Command execution option
#define ON_REAL_TIME        0x01


// Wair for unser input
bool kbhit()
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return (FD_ISSET(0, &fds));
}


// Print the info for supported commands
void print_help_info()
{
    printf("Commands:\n\n");
    printf("help                                  Display this info\n");
    printf("dummy                                 Send a dummy command \n");
    printf("get       [parameter name]            Get the value of a parameter\n");
    printf("set       [parameter name],[value]    Set the value of a parameter\n" );
    printf("reboot                                Reboot the OBC\n" );
    printf("\n\n");
}


// This task wait to receive a beacon
void * task_hk_client(void* parameter)
{
    csp_packet_t *beacon_packet;
    csp_socket_t * beacon_socket;
    beacon_socket = csp_socket( CSP_SO_CONN_LESS ); // Create socket for receive beacons
    csp_bind(beacon_socket, 10);
    // Loop that receive beacons
    while(1)
    {
        // Try to receive a packet from the Beacon port
        beacon_packet = csp_recvfrom( beacon_socket, 200 );
        // Wait until a Beacon is received
        if ( beacon_packet == NULL ) continue;
        // Truncate the packet at the end, to avoid read trash
        beacon_packet->data[ beacon_packet->length] = '\0';
        // Print the beacon data
        printf("> Client: Beacon Received:%s\n", beacon_packet->data);
        //Free Beacon packet
        csp_buffer_free(beacon_packet);

    }
    // Should never reach here
    csp_thread_exit();
}


void * task_client(void* parameter)
{
    int i;
    int c;
    int transaction_result;
    char *line;
    char *cmd_args;
    size_t len;
    ssize_t nread;
    char outbuf[256];
    char inbuf[1024];
    char aux_buffer[254];


    // Need stdin for read user imput
    if (stdin == NULL) {
        perror("Unable to open stdin!!!");
        exit(EXIT_FAILURE);
    }
    // Wait for the other tasks to be running!
    csp_sleep_ms(100);
    // Print usage info
    printf("\nMini Groud Station Example...\n");
    print_help_info();
    // Loop that reads the user command input
    while(1)
    {
        // Get user command
        if((nread = getline(&line, &len, stdin)) < 1) continue;
        // Delete new line caracter
        line[nread-1] = '\0';
        // Clean aux buffer
        bzero(aux_buffer, sizeof(aux_buffer));
        // Look for arguments for the command in the user input
        for( c = 0; line[c]!=' ' && c<nread; c++);
        // If any argument
        if(c < nread)
        {
            // Split the command from the argument
            line[c] = '\0';
            // Point cmd_args pointer to where the arguments start
            cmd_args = (char*) line + c + 1;
            // Copy the arguments to a new buff
            strcpy(aux_buffer, cmd_args);
        }
        // Clear transaction buffers
        bzero(inbuf, sizeof(inbuf));
        bzero(outbuf, sizeof(outbuf));

        /////// HELP //////////////////////
        if(strcmp( line, "help" ) == 0)
        {
            print_help_info();
        }

        /////// DUMMY COMMAND   ////////////
        else if(strcmp( line, "dummy" ) == 0)
        {
            printf("> Client: Sending message %d to server...\n",  i);
            // Encode Command
            snprintf(outbuf, sizeof(outbuf),  "%c%c", CMD_DUMMY, ON_REAL_TIME);
            // Send Command
            transaction_result = csp_transaction(PACKET_PRIO, DEST_ADDRESS, CMD_PORT, TRANSACTION_TIMEOUT, &outbuf, strlen(outbuf), inbuf, -1);
            // Check if reply
            if(transaction_result > 0 ) printf("> Client: Response from server: %s\n", inbuf);
            else printf("> Client: Transaction Failed, no Response from Server!!!\n");
        }

        //////// GET PARAM     /////////////////
        else if(strcmp( line, "get" ) == 0)
        {
            printf("> Client: Sending message %d to server...\n", i);
            // Encode Command
            snprintf(outbuf, sizeof(outbuf), "%c%c%s", CMD_GET_PARAM, ON_REAL_TIME, aux_buffer);
            // Send Command
            transaction_result = csp_transaction(PACKET_PRIO, DEST_ADDRESS, CMD_PORT, TRANSACTION_TIMEOUT, &outbuf, strlen(outbuf), inbuf, -1);
            // Check if reply
            if(transaction_result > 0 ) printf("> Client: Response from server: %s\n", inbuf);
            else printf("> Client: Transaction Failed, no Response from Server!!!\n");
        }

        //////// SET PARAM    /////////////////
        else if(strcmp( line, "set" ) == 0)
        {
            printf("> Client: Sending message %d to server...\n", i);
            // Encode Command
            snprintf(outbuf, sizeof(outbuf),  "%c%c%s", CMD_SET_PARAM, ON_REAL_TIME, aux_buffer);
            // Send Command
            transaction_result = csp_transaction(PACKET_PRIO, DEST_ADDRESS, CMD_PORT, TRANSACTION_TIMEOUT, &outbuf, strlen(outbuf), inbuf, -1);
            // Check if reply
            if(transaction_result > 0 ) printf("> Client: Response from server: %s\n", inbuf);
            else printf("> Client: Transaction Failed, no Response from Server!!!\n");
        }

         //////// Restart OBC  /////////////////
        else if(strcmp( line, "reboot" ) == 0)
        {
            printf("> Client: Sending message %d to server...\n", i);
            // Encode Command
            snprintf(outbuf, sizeof(outbuf),  "%c%c", CMD_REBOOT_OBC, ON_REAL_TIME );
            // Send Command
            transaction_result = csp_transaction(PACKET_PRIO, DEST_ADDRESS, CMD_PORT, TRANSACTION_TIMEOUT, &outbuf, strlen(outbuf), inbuf, -1);
            // Check if reply
            if(transaction_result > 0 ) printf("> Client: Response from server: %s\n", inbuf);
            else printf("> Client: Transaction Failed, no Response from Server!!!\n");
        }

        /////// UNKNOWN COMMAND ////////////////
        // If something readed, but the command is unknown
        else if(nread > 1)
        {
            printf("\nError: Unknown command \"%s\"\n", line);
            printf("Type \"help\" for the command list\n\n");
        }

        csp_sleep_ms(300);

        printf("\n");


        i++;
    }
    csp_thread_exit();
}


int main(int argc, char **argv)
{

    // Check that user assigned serial port
    if(argc != 2)
    {
        printf("Missing Serial Port!\n");
        printf("Usage: ./ground_station SERIAL_PORT_NAME\n\n");
        exit(1);
    }


    csp_debug_toggle_level(CSP_PACKET);
    csp_debug_toggle_level(CSP_INFO);


    // Init CSP
  	// Get default configurations
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
  	// Set custon configurations
    csp_conf.address = GS_ADDRESS;

  	// Try init
    int error = csp_init(&csp_conf);
    if (error != CSP_ERR_NONE) {
        printf("csp_init() failed, error: %d", error);
        exit(1);
    }

  	// Set up communications interface
    csp_iface_t * csp_if_kiss;
    csp_usart_conf_t conf = {
        .device = argv[1],
        .baudrate = 57600,
        .databits = 8,
        .stopbits = 1,
        .paritysetting = 0,
        .checkparity = 0};
    error = csp_usart_open_and_add_kiss_interface(&conf, CSP_IF_KISS_DEFAULT_NAME,  &csp_if_kiss);
    if (error != CSP_ERR_NONE) {
        printf("failed to add KISS interface [%s], error: %d", argv[1], error);
        exit(1);
    }

    // Static routing
    csp_route_set(9, &csp_if_lo, CSP_NODE_MAC);
    csp_route_set(1, csp_if_kiss, CSP_NODE_MAC);

    csp_route_start_task(0, 0);

    printf("Route table\r\n");
  	csp_route_print_table();
  	printf("Interfaces\r\n");
  	csp_route_print_interfaces();

    csp_thread_handle_t handle_hk_client;
    csp_thread_create(task_hk_client, "HK_CLIENT", 1000, NULL, 0, &handle_hk_client);

    csp_thread_handle_t handle_client;
    csp_thread_create(task_client, "CLIENT", 1000, NULL, 0, &handle_client);

    /* Wait for program to terminate (ctrl + c) */
    while(1) {
    	csp_sleep_ms(1000000);
    }

    return 0;

}
