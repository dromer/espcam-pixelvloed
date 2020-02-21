import socket
import codecs
import binascii


UDP_IP = "10.208.42.25"
UDP_PORT = 5004

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.bind((UDP_IP, UDP_PORT))

count=0
while True:
    #data, addr = sock.recvfrom(128) # buffer size is 1024 bytes
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    # data = sock.recv(1024) # buffer size is 1024 bytes

#    print(data)
    print(binascii.hexlify(data))    
    print(len(data))
#    print(addr)
    

