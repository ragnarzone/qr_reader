from datetime import datetime

def generate_message(itemInstanceId):
    now = datetime.now().strftime("%Y-%m-%dT%H:%M:%S.+01:00")
    itemInstanceId=itemInstanceId
    laneId="some string"
    zoneId="some string"
    scannerId="some string"

    contentLength = "0"
    sender = "some sender"

    file1 = open('/var/www/html/qr_reader/message.xml', 'w')

    toWrite = [
        "---BOUNDARY-\n",
        "Content-Type: text/xml\n",
        "Content-Transfer-Encoding: 8bit\n",
        "Content-Length: " + contentLength + "\n",
        "\n",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
        "<soap-env:Envelope xmlns:soap-env=\"http://schemas.xmlsoap.org/soap/envelope/\">\n",
        "<soap-env:Header>\n",
        "<ipc2502mh:MessageInfo\n xmlns:ipc2501mh=\"http://webstds.ipc.org/2501/MessageInfo.xsd\"\n " +
        "soap-env:actor=\"Jabil.TIS.CAMXSwitch.Listener\"\n" + 
        " sender=\"" + sender + "\" \n" +
        " destination=\"Jabil.TIS.CAMXSwitch.Listener\" \n" +
        " dateTime=\"" + now + "\"\n" + 
        " messageSchema=\"http://webstds.ipc.org/2541/ItemIdentifierRead.xsd\"\n" +
        " messageId=\"CAMX-API\"\n" +  
        " />\n",
        "</soap-env:Header>\n",
        "</soap-env:Envelope>\n",
        "\n",
        "---BOUNDARY-\n",
        "Content-Type: text/xml\n",
        "Content-Transfer-Encoding: 8bit\n",
        "Content-ID: CAMX-API\n",
        "Content-Length: " + contentLength + "\n",
        "\n",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
        "<ItemIdentifierRead\n", 
        "\tdateTime=\"" + now + "\"\n",
        "\titemInstanceId=\"" + itemInstanceId + "\"\n",
        "\tlaneId=\"" + laneId + "\"\n",
        "\tzoneId=\"" + zoneId + "\"\n",
        "\tscannerId=\"" + scannerId + "\"\n",
        "/>\n",
        "---BOUNDARY---"
    ]
  
    file1.writelines(toWrite)
    file1.close()

generate_message("12345")


