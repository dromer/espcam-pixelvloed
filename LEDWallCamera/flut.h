#include <ESP32Lib.h>
#include <WiFiUdp.h>

#pragma once
#pragma pack(1)

#define PACKET_SIZE 16
// #define PACKET_SIZE 1
#define PACKET_SIZE_BYTES 114

WiFiUDP udp;


struct Pixel {
    uint16_t y;
    uint16_t x;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel;

struct Packet {
    uint16_t header;
    struct Pixel pixel[PACKET_SIZE];
} packet;


void flutSend(struct Packet &myPacket, const char *udpAddress, const int udpPort)
{
    udp.beginPacket(udpAddress,udpPort);
    udp.write((uint8_t*) &myPacket, sizeof(myPacket));
    udp.endPacket();
    udp.stop();

    // Serial.write((uint8_t*) framedPacket, sizeof(myPacket));
    // Serial.println(sizeof(myPacket));
    // Serial.println(sizeof(myPacket.pixel)/sizeof(myPacket.pixel[0])); // number of pixels in packet
    // Serial.println(sizeof(myPacket.pixel[0])); // size of a pixel

    // Serial.println();
}


// To end possible trailing data
void flutEnd(struct Packet &myPacket, const char *udpAddress, const int udpPort, int pixelCnt)
{
    int packetSize = sizeof(myPacket) - (PACKET_SIZE - pixelCnt) * 7;

    udp.beginPacket(udpAddress, udpPort);
    udp.write((uint8_t*) &myPacket, packetSize);
    udp.endPacket();
    udp.stop();

    // Serial.write((uint8_t*) &myPacket, sizeof(myPacket));
    // Serial.println();
    // Serial.println(packetSize);

    Serial.println("End of the line.");
}
