#!/bin/bash
start_time=$( date +%s.%N )
passes=0
fails=0
for a in *.ok
do
x=${a:0:-3}
if [ "$(./$a)" = "${x}ok" ]
then
echo -e "\e[32;01mpass\e[0m on ${a:0:-3}"
passes=$[ $passes+1 ]
else
echo -e "\e[31;01mfail\e[0m on ${a:0:-3}"
fails=$[ $fails+1 ]
fi
done
x=`cat lexicalresult.txt`
y="$(./command_line_temp lexical.txt)"
if [ $y = $x ]
then
echo -e "\e[32;01mpass\e[0m on lexical"
passes=$[ $passes+1 ]
else
echo -e "\e[31;01mfail\e[0m on lexical"
fails=$[ $fails+1 ]
fi
echo "passes=$passes"
echo "fails=$fails"
end_time=$( date +%s.%N )
secs="$( echo "scale=3;$end_time-$start_time" | bc) seconds"
echo -e "$line\n\nExecution finsihed in $secs\n\e[32m$passes\e[0m test cases passed, \e[31m$fails\e[0m test cases failed"
