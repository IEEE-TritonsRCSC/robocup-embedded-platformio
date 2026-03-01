#pragma once

#define MAX_PACKET_SIZE 512
#define MAX_BUFFER_SIZE 64
#define MAX_COMMAND_BUFFER 8

class CommsBuffer
{
public:
    char packet_buffer[MAX_PACKET_SIZE];
    char buffer[MAX_BUFFER_SIZE];
    char cmd_buffer[MAX_COMMAND_BUFFER];

    /**
     * Initializes all buffers to zero.
     */
    CommsBuffer() : packet_buffer{0}, buffer{0}, cmd_buffer{0} {}
};
