#!/bin/bash 

rm *~
rm TreeL.txt
rm TreeS.txt
rm mutDataL.txt
rm mutDataS.txt


g++ -std=c++11 -O3 main.cpp -o szimu

sed -i '/gamma_manual= 4.0/c\gamma_manual= 2.2' ./adatok.txt


./szimu sleep 2 

sed -i '/gamma_manual= 2.2/c\gamma_manual= 5.0' ./adatok.txt


STRING=$(head -n 14 adatok.txt | tail -n 1 | cut -f 2 -d '=')

STRING2=$(head -n 6 adatok.txt | tail -n 1 | cut -f 2 -d '=')

STRING3=$(head -n 26 adatok.txt | tail -n 1 | cut -f 2 -d '=')


./szimu sleep 2 


sed -i "/var n = /c var n = $STRING;" ./sketch.js

sed -i "/var N = /c var N = $STRING2;" ./sketch.js

sed -i "/hier = /c hier = $STRING" ./HOT_LinTrace.py

sed -i "/N = /c N = $STRING2" ./HOT_LinTrace.py

sed -i "/MaxMut = /c MaxMut = $STRING3" ./HOT_LinTrace.py

#STRING2= $((3000+RANDOM/100))

#echo $STRING2

sed -i '/gamma_manual= 5.0/c\gamma_manual= 4.0' ./adatok.txt

nohup python3 HOT_LinTrace.py TreeL.txt L 1 1 &

wait

nohup python3 HOT_LinTrace.py TreeS.txt S 1 1 &

wait

nohup python -m SimpleHTTPServer 8182 &

nohup google-chrome http://localhost:8182 &




#gnuplot -e "p 'TreeZSS.txt' u 4:7 w l lw 2, 'TreeZLL.txt' u 4:7 w l lw 2, 4 lw 4; pause -1"

#gnuplot -e "p 'TreeSS.txt' u 4:8 w l lw 2, 'TreeLL.txt' u 4:8 w l lw 2, 4 lw 4; pause -1"



