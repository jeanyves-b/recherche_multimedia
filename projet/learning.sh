
function doTop
{
	concept=${1}
	util=${2}
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
	done < out/${util}_${concept}.out 3< "val/list.txt"
}

function learn
{
	concept=${1}
	util=${2}

	counterweight=1
	saverweight=0
	max=0

	while [[ $counterweight -lt 20 ]]
	do
		svm-train -h 0 -b 1 -w+1 $counterweight ${util}/train/svm/${util}_${concept}.svm model/${util}_${concept}.model
		svm-predict -b 1 ${util}/val/svm/${util}_${concept}.svm model/${util}_${concept}.model out/${util}_${concept}.out

		rm top/${util}_${concept}.top
		doTop $concept $util

		./trec_eval val/rel/${concept}.rel top/${util}_${concept}.top -q | grep "map" > logtrain${concept}${util}.txt
		read result < logtrain${concept}${util}.txt
		score=$(echo $result | cut -d " " -f3)
		if [[ $(echo $max'>'$score | bc -l) -eq 0 ]]
		then
			max=$score
			saverweight=$counterweight
		fi
		((counterweight ++))
	done

	svm-train -h 0 -b 1 -w+1 $saverweight ${util}/train/svm/${util}_${concept}.svm model/${util}_${concept}.model
	svm-predict -b 1 ${util}/val/svm/${util}_${concept}.svm model/${util}_${concept}.model out/${util}_${concept}.out
	rm top/${util}_${concept}.top
	doTop $concept $util
	echo -e "${util} $concept -> valeur : $saverweight -> score : $max" >> resultTrain.txt
}

while read concept
do
	learn $concept "color" &
	learn $concept "sift" &
done < concept.txt