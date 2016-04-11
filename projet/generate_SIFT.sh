folder="sift/train/"
while read Image
do
	counter=0
	for (( i = 0; i < 3; i++ ))
	do
		read siftLine < ${folder}${Image}
	done
	while read siftLine
	do
		if [[ $counter -eq 74 ]]
		then
			echo $(echo $siftLine | cut -d ";" -f 2) >> sample.txt
			counter=0
		else
			counter=$counter+1
		fi
	done < ${folder}${Image}
done < ${folder}liste_train_sift.txt