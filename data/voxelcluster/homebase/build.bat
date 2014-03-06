python ../../../tools/csvmergex.py backcenter.csv winginner.csv _b1.csv
python ../../../tools/csvmergex.py _b1.csv wingouter.csv _b2.csv

python ../../../tools/csvmergex.py backforward.csv empty.csv _bf1.csv
python ../../../tools/csvmergex.py _bf1.csv empty.csv _bf2.csv

python ../../../tools/csvmergez.py _bf2.csv _b2.csv _back.csv



python ../../../tools/csvmergex.py mid.csv empty.csv _m1.csv
python ../../../tools/csvmergex.py _m1.csv empty.csv _m2.csv

python ../../../tools/csvmergez.py _m2.csv _back.csv _out.csv
