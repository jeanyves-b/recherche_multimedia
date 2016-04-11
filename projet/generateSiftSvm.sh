#!/bin/sh

function treatval
{
	util="${2}"
	folder="sift/${util}"
	destination="sift/${util}/svm"
	counter=0
	while read Image && read valueline <&3 
	do
		if [[ $counter -eq 50 ]]; then
			counter=0
			echo "${concept} ${util}-> treat image : ${Image}"
		else
			((counter++))
		fi
		line=$(echo "$valueline" | cut -d " " -f 2)
		if [[ $line -eq " " ]]; then
			line="1"
		fi
		echo $line $(./createSiftSvm ${folder}/1nn/${Image}) >> ${destination}/sift_${1}.svm
	done < ${folder}/liste_${util}_sift.txt 3< train/ann/${1}.ann
}

while read concept
do
	treat ${concept} train &
	treat ${concept} val &
done < concept.txt
while [ 1 ]; do fg 2> /dev/null; [ $? == 1 ] && break; done