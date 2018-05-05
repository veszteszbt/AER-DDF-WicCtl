#!/bin/bash

#NOTE: RUN FROM MAIN FOLDER WITH ./test/test.sh
start_time=$( date +%s.%N )
passes=0
fails=0
for a in test/*.ok
do
file=${a:0:-3}
x=`./commandline ${file}.ok`
y=`cat ${file}.txt`
if [ "$x" == "$y" ]
then
echo -e "\e[32;01mpass\e[0m on ${a}"
passes=$[ $passes+1 ]
else
echo -e "\e[31;01mfail\e[0m on ${a}"
fails=$[ $fails+1 ]
fi
done
echo "passes=$passes"
echo "fails=$fails"
end_time=$( date +%s.%N )
secs="$( echo "scale=3;$end_time-$start_time" | bc) seconds"
echo -e "$line\n\nExecution finsihed in $secs\n\e[32m$passes\e[0m test cases passed, \e[31m$fails\e[0m test cases failed"