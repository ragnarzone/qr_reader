#!/usr/bin/python3
from datetime import datetime
import requests
import os
import subprocess
import time


#http://hutiss0stgweb81/Linecontrol/camxhandler.ashx


def send_message():
    url = 'http://hutiss0stgweb81/Linecontrol/camxhandler.ashx'
    xml = open("/var/www/html/qr_reader/tested_code/message.xml", "r")
    headers = {'Content-Type':'text/xml'}
    response = requests.post(url, xml, headers)
    print(response.text)


def generate_message(itemInstanceId):
    now = datetime.now().strftime("%Y-%m-%dT%H:%M:%S.+01:00")
    itemInstanceId=itemInstanceId
    laneId="1"
    zoneId="1"
    scannerId="1234"

    contentLength = str(955 + len(itemInstanceId))
    sender = "C120"
    actor = "C120"

    file1 = open('/var/www/html/qr_reader/tested_code/message.xml', 'w')

    toWrite = [
        "\n---BOUNDARY-\n",
        "Content-Type: text/xml\n",
        "Content-Transfer-Encoding: 8bit\n",
        "Content-ID: <example:soap:MaRC>\n"
        "Content-Length: " + contentLength + "\n",
        "\n",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
        "<soap-env:Envelope xmlns:soap-env=\"http://schemas.xmlsoap.org/soap/envelope/\">\n",
        "<soap-env:Header>\n",
        "<ipc2501mh:MessageInfo\n xmlns:ipc2501mh=\"http://webstds.ipc.org/2501/MessageInfo.xsd\"\n " +
        "soap-env:actor=\"" + actor +"\"\n" + 
        " sender=\"" + sender + "\" \n" +
        " destination=\"Jabil.TIS.LineControl\" \n" +
        " dateTime=\"" + now + "\"\n" + 
        " messageSchema=\"http://webstds.ipc.org/2541/ItemIdentifierRead.xsd\"\n" +
        " messageId=\"CAMX-API Georgia Tech" + now + "\"\n" +  
        " />\n",
        "</soap-env:Header>\n",
        "</soap-env:Envelope>\n",
        "\n",
        "---BOUNDARY-\n",
        "Content-Type: text/xml\n",
        "Content-Transfer-Encoding: 8bit\n",
        "Content-ID: CAMX-API Georgia Tech" + now + "\n",
        "Content-Length: " + contentLength + "\n",
        "\n",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
        "<ItemIdentifierRead\n", 
        "dateTime=\"" + now + "\"\n",
        "scannerId=\"" + scannerId + "\"\n",
        "itemInstanceId=\"" + itemInstanceId + "\"\n",
        "laneId=\"" + laneId + "\"\n",
        "zoneId=\"" + zoneId + "\"\n",
        "/>\n",
        "---BOUNDARY---\n"
    ]
  
    file1.writelines(toWrite)
    file1.close()


itemIdFile = open("/var/www/html/qr_reader/tested_code/out.txt", "r")
generate_message(itemIdFile.readline())
send_message()