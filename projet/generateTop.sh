
util=${1}

while read concept
do
	counter=0
	while read scoreline && read imageline <&3
	do
		if [ $counter -eq 0 ]
		then
			tester=$(echo "$scoreline" | cut -d " " -f 2)
			if [ $tester -eq 1 ]
			then
				column=2
			else
				column=3
			fi
		else
			score=$(echo "$scoreline" | cut -d " " -f $column)
			image=$(echo "$imageline" | cut -d "." -f 1)
			line="$concept Q0 $image 0 $score R"
			echo $line >> top/${util}_${concept}.top
		fi
		((counter++))
	done < out/${util}_${concept}.out 3< "eval/list.txt"
done < concept.txt