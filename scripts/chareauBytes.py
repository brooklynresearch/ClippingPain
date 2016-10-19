import socket
import struct
import time
import logging
import sys

logging.basicConfig()
log = logging.getLogger()
log.setLevel(logging.DEBUG)

logfile = sys.argv[1]

serverAddr = ('127.0.0.1', 5020)

with open(logfile,"rb") as f:
    readBytes = f.read(33)
    while readBytes:
        message = bytearray(readBytes)

        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(serverAddr)
        client.sendall(message)
        client.close()
        time.sleep(0.2) #5 Hz
        readBytes = f.read(33)

