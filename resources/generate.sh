#! /bin/bash -e

QRC=./resources.qrc
echo '<!DOCTYPE RCC>' > $QRC
echo '<RCC version="1.0">' >> $QRC
echo '  <qresource>' >> $QRC

# for each files/folder in the folder "theFokderName"
for ext in "vsh" "fsh" "gsh" "png" "glsl"
do
	for file in $(find . -type f -name "*.$ext")
	do
		# if this is not a folder
		if [ ! -d "$file" ]; then
			echo '      <file>'$file'</file>' >> $QRC
		fi
	done
done

echo '  </qresource>' >> $QRC
echo '</RCC>' >> $QRC
