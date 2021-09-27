
SIGNAL=$1
#SIGNAL="T2tt"
#SIGNAL="T2bW"
#SIGNAL="T2bb"
#SIGNAL="T2cc"
#SIGNAL="TChiWZ"
#SIGNAL="T2SlepSlep" #bit of a typo here, just keep consistent
#SIGNAL="T1bbbb"
#SIGNAL="T1ttbb"
#SIGNAL="T5tttt"
#SIGNAL="TChipmWW"

#ROOTNAME="./B5-1_BFS/BFS_B5-1_"$SIGNAL"17.root"
ROOTNAME="./9-14-21_BFS/BFS_BT-1_"$SIGNAL"17.root"
#/home/justin/work/research/susy/6-29-21/BFItoCSV/9-14-21_BFS/BFS_BT-1_T2bW17.root

DIRNAME=$SIGNAL"_0L"
rm -rf $DIRNAME
mkdir $DIRNAME
root -l -b -q "macroS.C(\"Ch0L\",0, \"$ROOTNAME\")"
mv *.csv $DIRNAME

DIRNAME=$SIGNAL"_1L"
rm -rf $DIRNAME
mkdir $DIRNAME
root -l -b -q "macroS.C(\"Ch1L\",1, \"$ROOTNAME\")"
mv *.csv $DIRNAME

DIRNAME=$SIGNAL"_2L"
rm -rf $DIRNAME
mkdir $DIRNAME
root -l -b -q "macroS.C(\"Ch2L\",2, \"$ROOTNAME\")"
mv *.csv $DIRNAME

DIRNAME=$SIGNAL"_3L"
rm -rf $DIRNAME
mkdir $DIRNAME
root -l -b -q "macroS.C(\"Ch3L\",3, \"$ROOTNAME\")"
mv *.csv $DIRNAME

