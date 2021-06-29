
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

ROOTNAME="BFI_CR_"$SIGNAL".root"

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

