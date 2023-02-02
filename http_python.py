import requests

url = 'http://hutiss0stgweb81/Linecontrol/camxhandler.ashx'
xml = open("message.xml", "r")
x = xml.readlines()
#print(x)
response = requests.post(url, xml)
print(response.text)