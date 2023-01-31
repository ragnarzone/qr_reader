import xml.sax

class ClassHandler( xml.sax.ContentHandler ):
    def __init__(self):
        self.CurrentData = ""
        self.FirstName = ""
        self.MiddleName = ""
        self.LastName = ""
        self.RollNo = ""
        self.Section = ""

   # Gets called at the start of element 
    def startElement(self, tag, attributes):
        self.CurrentData = tag
        if tag == "Class":
            print ("*****Class*****")

   # Gets called at the end of elements
    def endElement(self, tag):
        if self.CurrentData == "FirstName":
            print ("FirstName:", self.FirstName)
        elif self.CurrentData == "MiddleName":
            print ("MiddleName:", self.MiddleName)
        elif self.CurrentData == "LastName":
            print ("LastName:", self.LastName)
        elif self.CurrentData == "RollNo":
            print ("RollNo:", self.RollNo)
        elif self.CurrentData == "Section":
            print ("Section:", self.Section)
        self.CurrentData = ""

   # Gets called when a character is read
    def characters(self, content):
        if self.CurrentData == "FirstName":
             self.FirstName = content
        elif self.CurrentData == "MiddleName":
             self.MiddleName = content
        elif self.CurrentData == "LastName":
             self.LastName = content
        elif self.CurrentData == "RollNo":
             self.RollNo = content
        elif self.CurrentData == "Section":
             self.Section = content
if ( __name__ == "__main__"):
   
   # creates an XMLReader
    parser = xml.sax.make_parser()
   # turnsoff namepsaces
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)

   # overrides the default Handler
    handler = ClassHandler()
    parser.setContentHandler( handler )
   
    parser.parse("xml_to_parse.xml")