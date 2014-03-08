import csv
import sys

sys.argv.append("m1.csv")
sys.argv.append("double.csv")

outfile = open(sys.argv[2], "w", newline="")
reader1 = csv.reader(open(sys.argv[1], "r"), delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
writer = csv.writer(outfile, delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')

list1 = list(reader1)

list1[0][0] = 2 * int(list1[0][0])
list1[0][1] = 2 * int(list1[0][1])
list1[0][2] = 2 * int(list1[0][2])

listmerge = []
lastblock = []

listmerge.append(list1[0])

for l in list1[1:]:
    if l == []:
        #y-double
        listmerge.append(l)
        for i in lastblock:
            listmerge.append(i)
        lastblock = []
        listmerge.append(l)
    else:
        lo = []
        for i in l:
            lo.append(i)
            lo.append(i)
        listmerge.append(lo)
        listmerge.append(lo)
        lastblock.append(lo)
        lastblock.append(lo)

writer.writerows(listmerge)

outfile.flush()
