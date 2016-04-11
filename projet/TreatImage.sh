#!/bin/sh

NBCONCEPT=20
NAME=${1}
NAMEColor=$(echo ${NAME}Color.svm)
NAMESift=$(echo ${NAME}Sift.svm)
resultSift=0
resultColor=0

./createHisto $NAME > $NAMEColor
./colorDescriptor $NAME --output $(echo ${NAME}Sift.svm)

while read concept
do
	#traitement Color

	#traitement Sift

	siftresult=$(echo )
	svm-train -h 0 -b 1 -w+1 $weight sift/train/svm/sift_${concept}.svm model/sift_${concept}.model
	svm-predict -b 1 sift/val/svm/sift_${concept}.svm model/sift_${concept}.model out/sift_${concept}.out
	
	if [[ $resultSift -eq 0 ]]; then
		resultSift=$resultColor;
	fi
	echo ${concept} : "score Color :" ${resultColor} "score Sift : " ${resultSift} "-> score final = " $(echo "($resultSift+$resultColor)/2" | bc -l)
done < concept.txt