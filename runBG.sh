

BFI=${1-test.root}
DIR=${2-CSVFiles}


rm -rf $DIR
mkdir $DIR

#rm -rf BG_0L
mkdir BG_0L
root -l -b -q "macroBG.C(\"Ch0L\",0, \"${BFI}\" )"
#root -l -b -q "${ARG1}"
mv *.csv BG_0L/

#rm -rf BG_1L
mkdir BG_1L
root -l -b -q "macroBG.C(\"Ch1L\",1, \"${BFI}\" )"
mv *.csv BG_1L/

#rm -rf BG_2L
mkdir BG_2L
root -l -b -q "macroBG.C(\"Ch2L\",2, \"${BFI}\" )"
mv *.csv BG_2L/

#rm -rf BG_3L
mkdir BG_3L
root -l -b -q "macroBG.C(\"Ch3L\",3, \"${BFI}\" )"
mv *.csv BG_3L/


mv BG_*L ${DIR}/
