#pragma once

#include "stdint.h"
#include <Arduino.h>
#include "WiFi.h"

class PacketInfo {
    public:
    uint16_t packet_size;
    uint16_t last_packet_size;
    unsigned long packet_time;
    int numBytes;
    int bytesParsed;

    PacketInfo() : packet_size(0), last_packet_size(0), packet_time(0), numBytes(0), bytesParsed(0) {}
    bool isPacketAvailable();
    bool isLastPacketAvailable();
    void updateLastPacketSize();
    void updatePacketSize(WiFiUDP udp);
    void resetLastPacketSize();
    void updatePacketTime();
    void printLastPacketSize();

    // The network may have multiple UDP packets queue up in the buffer
    // Read all of them, but only process the last one to reduce jitter
    void readAllPackets(WiFiUDP udp);
    void processLastPacket();
    void updatePacketSizeAndReadAllPackets(WiFiUDP udp);
    void updatePacketSizeAndReadAllPacketsAndProcessLastPacket(WiFiUDP udp);
    void updatePacketSizesAndReadAllPacketsAndProcessLastPacket(WiFiUDP udp);
};