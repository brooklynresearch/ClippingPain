from pymodbus3.client.sync import ModbusTcpClient
import time


logging.basicConfig()
log = logging.getLogger()
log.setLevel(logging.DEBUG)

client = ModbusTcpClient('127.0.0.1', method='ascii', port=5020)

while True:
	for x in range(0, 1000):



		client.write_registers(0, [x,0,0,0,0,0,0,0,0,0])
		#result = client.read_registers(0,10)
		#print(result.bits[0])
		client.close()
		time.sleep(50.0/1000.0) #~30fps

	time.sleep(10) # 10 secs

	for y in range(1000, 0, -1):
		client.write_registers(0, y)
		client.close()
		time.sleep(50.0/1000.0) #~30fps