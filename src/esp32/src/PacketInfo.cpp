#include "PacketInfo.h"
#include "hardwareControllers.h"
#include "global_vars.h"
#include "helpers.h"
#include "parsers.h"

bool PacketInfo::isPacketAvailable() {
    return packet_size > 0;
}

void PacketInfo::updateLastPacketSize() {
    last_packet_size = packet_size;
}


bool PacketInfo::isLastPacketAvailable() {
    return last_packet_size > 0;
}

void PacketInfo::updatePacketTime() {
    packet_time = micros();
}

void PacketInfo::printLastPacketSize() {
    PRINT((int)last_packet_size, " | ");
}

void PacketInfo::updatePacketSize(WiFiUDP &udp) {
    packet_size = udp.parsePacket();
}

void PacketInfo::readAllPackets(WiFiUDP &udp) {
    while (isPacketAvailable())
    {
        udp.read(commsBuffer.packet_buffer, MAX_PACKET_SIZE);
        updateLastPacketSize();
        updatePacketSize(udp);
    }
}

void PacketInfo::processLastPacket(RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state) {
    if (isLastPacketAvailable())
    {
        turnLEDOn(LED_PIN);

        updatePacketTime();
        printLastPacketSize();

        for (uint16_t i = 0; i < last_packet_size; i++)
        {
            char c = commsBuffer.packet_buffer[i];
            handleNewChar(c, robotVelocity, motor_command, kicker_state);
        }

        turnLEDOff(LED_PIN);
    }
}

void PacketInfo::resetLastPacketSize() {
    last_packet_size = 0;
}

void PacketInfo::updatePacketSizeAndReadAllPackets(WiFiUDP &udp) {
    updatePacketSize(udp);
    readAllPackets(udp);
}

void PacketInfo::updatePacketSizeAndReadAllPacketsAndProcessLastPacket(WiFiUDP &udp, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state) {
    updatePacketSizeAndReadAllPackets(udp);
    processLastPacket(robotVelocity, motor_command, kicker_state);
}

void PacketInfo::updatePacketSizesAndReadAllPacketsAndProcessLastPacket(WiFiUDP &udp, RobotVelocity &robotVelocity, std::array<uint8_t, MOTOR_COMMAND_SIZE> &motor_command, KickerState &kicker_state)
{
    resetLastPacketSize();
    updatePacketSizeAndReadAllPackets(udp);
    processLastPacket(robotVelocity, motor_command, kicker_state);
}