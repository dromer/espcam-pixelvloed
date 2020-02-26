import socket
import codecs
import binascii
import struct
import json

from ctypes import *


# UDP_IP = "10.208.42.25"
# UDP_IP = "192.168.178.11"
UDP_IP = "192.168.178.6"
UDP_PORT = 5004

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.bind((UDP_IP, UDP_PORT))


# struct Pixel {
#     uint16_t y;
#     uint16_t x;
#     uint8_t r;
#     uint8_t g;
#     uint8_t b;
# } pixel;

# struct Packet {
#     uint16_t header;
#     struct Pixel pixel[PACKET_SIZE];
# } packet;

PACKET_SIZE = 16

# def parse_packet(data):

#     s = struct.unpack_from(
#         'HHBBB' * PACKET_SIZE,
#         data,
#         offset=2
#     )

#     s = data.decode('ascii')

#     # print(s)

#     packet = []

#     for i in range(2, PACKET_SIZE+2):
#         pixel = {
#             'x': s[0*i],
#             'y': s[1*i],
#             'r': s[2*i],
#             'g': s[3*i],
#             'b': s[4*i],
#             # 'a': s[5*i]
#         }
#         packet.append(pixel)

#     # print(packet)
#     print(json.dumps(packet, indent=4))

def parse_packet(data):

    pixels = (len(data) - 2) / 7
    # print(pixels)

    packet = []
    for i in range(0, int(pixels)):
        offset = 2 + (7 * i)
        s = struct.unpack_from("<2H3B", data, offset=offset)
        pixel = {
            'y': s[0],
            'x': s[1],
            'r': s[2],
            'g': s[3],
            'b': s[4],
        }
        packet.append(pixel)

    # return packet
    print(json.dumps(packet, indent=4))


def parse_header(data):

    s = struct.unpack_from("2B", data)

    header = {
        'v_head': s[0],
        'c_head': s[1]
    }

    print(json.dumps(header, indent=4))

xbuf = 255
ybuf = 255
imagebuf = [[0] * xbuf for i in range(ybuf)]

def create_buffer(data):
    s = struct.unpack_from(
        'HHBBB' * PACKET_SIZE,
        data,
        offset=2
    )

    for i in range(0, PACKET_SIZE):
        xcoord = s[0*i]
        ycoord = s[1*i]
        pixel = {
            'r': s[2*i],
            'g': s[3*i],
            'b': s[4*i],
            # 'a': s[5*i]
        }

        imagebuf[xcoord][ycoord] = pixel

    # print(imagebuf)

count=0
while True:
    #data, addr = sock.recvfrom(128) # buffer size is 1024 bytes
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    # data = sock.recv(1024) # buffer size is 1024 bytes

    # print(data)
    # print(binascii.hexlify(data))
    # print(len(data))
#    print(addr)

    # parse_packet(data)
    parse_header(data)
    # create_buffer(data)
