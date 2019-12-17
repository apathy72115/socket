#!/usr/bin/env python
# -*- coding:utf8 -*-
 
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
 
import socket
 
class UdpClient(object):
    def tcpclient(self):
        clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        while 1:
		sendDataLen = clientSock.sendto("this is send data from client", ('localhost', 9527))
		recvData = clientSock.recvfrom(1024)
		print "sendDataLen: ", sendDataLen
		print "recvData: ", recvData
        
        clientSock.close()
        
if __name__ == "__main__":
    udpClient = UdpClient()
    udpClient.tcpclient()


