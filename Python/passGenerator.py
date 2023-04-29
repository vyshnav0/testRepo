usname = input("Enter your name\n")
pw = "_"
for i in usname:
    if i==" ":
        pw += "_"
    elif not((i>="0") & (i<="9")):
        try:
            if pw[-1] == "_":
                pw = pw[0:-1]
                pw += i.upper()
            else:
                pw += i.lower()
        except:
            print("Exception")
    else:
        if pw[-1] == "_" : pw = pw[0:-1]
        pw += i
print("Username:",usname)
print("Password:",pw)