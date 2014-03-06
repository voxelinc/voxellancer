python ../../../tools/csvmergex.py backcenter.csv winginner.csv _b1.csv
python ../../../tools/csvmergex.py _b1.csv wingouter.csv _b2.csv

python ../../../tools/csvmergex.py backforward.csv empty.csv _bf1.csv
python ../../../tools/csvmergex.py _bf1.csv empty.csv _bf2.csv

python ../../../tools/csvmergez.py _bf2.csv _b2.csv _back.csv



python ../../../tools/csvmergex.py mid.csv empty.csv _m1.csv
python ../../../tools/csvmergex.py _m1.csv empty.csv _mid.csv



python ../../../tools/csvmergex.py frontbackward.csv empty.csv _fb1.csv
python ../../../tools/csvmergex.py _fb1.csv empty.csv _fb2.csv

python ../../../tools/csvmergex.py frontcenter.csv empty.csv _f1.csv
python ../../../tools/csvmergex.py _f1.csv empty.csv _f2.csv

python ../../../tools/csvmergex.py frontforward.csv empty.csv _ff1.csv
python ../../../tools/csvmergex.py _ff1.csv empty.csv _ff2.csv

python ../../../tools/csvmergez.py _f2.csv _fb2.csv _fr1.csv
python ../../../tools/csvmergez.py _ff2.csv _fr1.csv _front.csv



python ../../../tools/csvmergez.py _mid.csv _back.csv _rear.csv
python ../../../tools/csvmergez.py _front.csv _rear.csv _right.csv
python ../../../tools/csvmirrorx.py _right.csv _out.csv