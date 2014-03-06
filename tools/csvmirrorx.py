import csv
import sys
import copy

sys.argv.append("m1.csv")
sys.argv.append("mirror.csv")

outfile = open(sys.argv[2], "w", newline="")
reader1 = csv.reader(open(sys.argv[1], "r"), delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
writer = csv.writer(outfile, delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')

list1 = list(reader1)

list1[0][0] = int(list1[0][0]) * 2

list2 = copy.deepcopy(list1)
list2[0] = []
for line in list2:
    line = line.reverse()

listmerge = [a+b for (a,b) in zip(list2, list1)]

writer.writerows(listmerge)

outfile.flush()
