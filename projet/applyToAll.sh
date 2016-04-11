while read concept
do
	./createsvm $concept
	counter=1
	saver=0
	max=0
	while [[ $counter -lt 20 ]]
	do
		svm-train -h 0 -b 1 -w+1 $counter train/svm/color_${concept}.svm model/color_${concept}.model
		svm-predict -b 1 eval/svm/color_${concept}.svm model/color_${concept}.model out/color_${concept}.out > logtrain.txt
		#faire la prediction avec trec_eval
		read result < logtrain.txt
		score=$(echo $(echo $result | cut -d " " -f 3) | cut -d "%" -f 1)
		echo $score
		if [[ $(echo $max'>'$score | bc -l) -eq 0 ]]
		then
			max=$score
			saver=$counter
		fi
		((counter ++))
	done
	echo -e $concept "-> valeur d'entraiement :" "'$saver'" "score :" "'$max'" >> resultTrain.txt
done < concept.txt