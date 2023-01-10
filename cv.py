import cv2
from jinja2 import Environment, FileSystemLoader

# read qr

cam = cv2.VideoCapture(0)
detector = cv2.QRCodeDetector()

while True:
	ret, image = cam.read()
	cv2.imshow('Imagetest',image)
	data, bbox, _ = detector.detectAndDecode(image)
	if data:
		a=data
		break
	k = cv2.waitKey(1)
	if k != -1:
		break
cv2.imwrite('/var/www/html/qr_reader/qr_pic.jpg', image)
print(a)
cam.release()
cv2.destroyAllWindows()

# write template

environment = Environment(loader=FileSystemLoader("./"))
template = environment.get_template("qr_template.html")

filename = "qr.html"
content = template.render(link=a)
html = open(filename, mode="w", encoding="utf-8")
html.write(content)