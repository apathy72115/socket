
#!/usr/bin/env python
# -*- coding:utf8 -*-
 
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
 
import socket
 
class UdpServer(object):
    def tcpServer(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(('', 9527))      
        
        while True:
            revcData, (remoteHost, remotePort) = sock.recvfrom(1024)
            print("[%s:%s] connect" % (remoteHost, remotePort))    
            
            sendDataLen = sock.sendto("this is send  data from server", (remoteHost, remotePort))
            print "revcData: ", revcData
            print "sendDataLen: ", sendDataLen
            
       
            
if __name__ == "__main__":
    udpServer = UdpServer()
    udpServer.tcpServer()

