def linenum(lines, index):
    if index % 49 == 0:
        return index
    else:
        return int(index/49)*49 + 49 - (index%49)

ifile = open("moy.csv")

lines = ifile.readlines();

ofile = open("moy_turned.csv", "w")

for l in range(0, len(lines)):
    print(linenum(lines, l))
    ofile.write(lines[linenum(lines, l)])
    
