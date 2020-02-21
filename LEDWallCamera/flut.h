#include <ESP32Lib.h>
#include <WiFiUdp.h>

#pragma once

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
    uint8_t a;
} pixel;

struct Packet {
    uint16_t header;
    struct Pixel pixel[PACKET_SIZE];
} packet;


void flutSend(struct Packet &myPacket, const char *udpAddress, const int udpPort)
{
    unsigned char framedPacket[sizeof(myPacket)];
    memcpy(framedPacket, &myPacket, sizeof(myPacket));

    udp.beginPacket(udpAddress,udpPort);
    udp.write((uint8_t*) framedPacket, sizeof(myPacket));
    udp.endPacket();
    udp.stop();

    // Serial.write((uint8_t*) framedPacket, sizeof(myPacket));
    // Serial.println(sizeof(myPacket));
    // Serial.println(sizeof(myPacket.pixel)/sizeof(myPacket.pixel[0])); // number of pixels in packet
    // Serial.println(sizeof(myPacket.pixel[0])); // size of a pixel

    // Serial.println();
}


// // To end possible trailing data
// void flutEnd(union Packet &myPacket, const char *udpAddress, const int udpPort, int pixelCnt)
// {
//     unsigned char framedPacket[sizeof(myPacket)];

//     int packetSize = sizeof(framedPacket) - (PACKET_SIZE - pixelCnt) * 7 + 2;  // why?
//     memcpy(framedPacket, &myPacket, packetSize);

//     udp.beginPacket(udpAddress, udpPort);
//     udp.write((uint8_t* )framedPacket, sizeof(myPacket));
//     udp.endPacket();
//     udp.stop();

//     Serial.write((uint8_t*) framedPacket, sizeof(myPacket));
//     Serial.println("End of the line.");
// }
