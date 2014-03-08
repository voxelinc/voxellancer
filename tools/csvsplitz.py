import csv
import sys

sys.argv.append("double.csv")
sys.argv.append("split1.csv")
sys.argv.append("split2.csv")

outfile1 = open(sys.argv[2], "w", newline="")
outfile2 = open(sys.argv[3], "w", newline="")
reader = csv.reader(open(sys.argv[1], "r"), delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
writer1 = csv.writer(outfile1, delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
writer2 = csv.writer(outfile2, delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')

listin = list(reader)
list1 = []
list2 = []

size = int(listin[0][2])
interval = round(size / 2)
listin[0][2] = interval

list1.append(listin[0])
list2.append(listin[0])

i = 0;
for l in listin[1:]:
    if l == []:
        i = 0
        list1.append(l)
        list2.append(l)
    else:
        if i < interval:
            list1.append(l)
        else:
            list2.append(l)
        i += 1
           
writer1.writerows(list1)
writer2.writerows(list2)

outfile1.flush()
outfile2.flush()
