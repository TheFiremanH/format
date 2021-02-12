filepath = str()
while filepath == "":
    filepath = input("File path : ")

doc = open(filepath, "r")
data = doc.read()
replaced = 1
while "\n " in data or "\t\n" in data:
    data = data.replace("\n ", "\n")
    data = data.replace("\t\n", "\t")

