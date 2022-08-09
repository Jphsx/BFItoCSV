
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
#ROOTNAME="./9-14-21_BFS/BFS_BT-1_"$SIGNAL"17.root"
#ROOTNAME="../../7-12-22/BFI_ForAlice_ttbar17_t4bd.root"
#ROOTNAME="../../7-12-22/BFI_ttbar17_t4bdcp5.root"
#ROOTNAME="../../7-19-22/BFI_pt5.root"
#ROOTNAME="../../7-19-22/BFI_pt5_10.root"
#ROOTNAME="../../7-19-22/BFI_pt10_20.root"
#ROOTNAME="../../7-19-22/BFI_pt20.root"
#ROOTNAME="../../7-22-22/t4bd_UL/BFI_0.root"
#ROOTNAME="../../7-26-22/BFI_ttbar17_t4bd17_UL.root"
ROOTNAME=$2

AGGDIR=$3

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

rm -rf $AGGDIR
mkdir $AGGDIR
mv $SIGNAL"_0L" ${AGGDIR}/
mv $SIGNAL"_1L" ${AGGDIR}/
mv $SIGNAL"_2L" ${AGGDIR}/
mv $SIGNAL"_3L" ${AGGDIR}/

