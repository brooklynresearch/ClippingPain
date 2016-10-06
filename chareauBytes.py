import socket
import struct
import time
import logging

logging.basicConfig()
log = logging.getLogger()
log.setLevel(logging.DEBUG)

def sendMessage(count, i):

	value = i / 100.0

	byteVal = bytearray(struct.pack("f", value))

	header = bytearray()
	header += bytearray([0,1, 0,0, 0,27, 0, 16,])

	function = bytearray()
	function += bytearray([0,0, 0,10, 20])

	data = byteVal + bytearray([0]*16)

	cmd = bytearray(header + function + data)

	print("MESSAGE: " + ''.join('{:02x}'.format(x) for x in cmd))

	client.sendall(cmd)

	data = client.recv(12)

	print("RESPONSE: " + ''.join('{:02x}'.format(x) for x in data))


count = 1
serverAddr = ('127.0.0.1', 5020)
for x in range(100000):

	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect(serverAddr)
	sendMessage(count, x)
	count += 1
	client.close()
	time.sleep(50.0/1000.0) #~30fps


	



