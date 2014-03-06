import csv
import sys

sys.argv.append("m1.csv")
sys.argv.append("m2.csv")
sys.argv.append("merge.csv")

outfile = open(sys.argv[3], "w", newline="")
reader1 = csv.reader(open(sys.argv[1], "r"), delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
reader2 = csv.reader(open(sys.argv[2], "r"), delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')
writer = csv.writer(outfile, delimiter=',', quoting=csv.QUOTE_NONE, lineterminator='\r\n')

list1 = list(reader1)
list2 = list(reader2)

#this is y-merge
if (list1[0][0] != list2[0][0] or list1[0][2] != list2[0][2]): 
    print("Inputs must be of equal size along merge axes!")
    quit()
list1[0][1] = int(list1[0][1]) + int(list2[0][1])

#remove empty header to avoid double-empty-line
list2 = list2[1:]

listmerge = list1 + list2

writer.writerows(listmerge)

outfile.flush()
