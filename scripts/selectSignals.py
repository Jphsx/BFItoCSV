

import glob
import pandas as pd

#T2bW_*L
#TChiWZ_*L

#SignalType = "T2bW" 
#SignalType = "TChiWZ"
SignalType = "TSlepSlep"


AllowedMassPoints=[]
#T2bW mass points
if(SignalType=="T2bW"):
    AllowedMassPoints= [6500550,6500560,6500570,6500580,6500590,6500600,6500610,6500620,6500630,6500640]
#TChiWZ mass points
if(SignalType=="TChiWZ"):
    AllowedMassPoints= [3000297,3000293,3000290,3000280,3000270,3000260,3000250,3000240,3000230,3000220, 3000210,3000200]
#TSlepSlep mass points
if(SignalType=="TSlepSlep"):
    AllowedMassPoints= [2000195,2000190,2000180,2000170,2000160,2000150,2000140,2000130,2000120,2000110,2000100]

for i,pts in enumerate(AllowedMassPoints):
    AllowedMassPoints[i] = SignalType+"_"+str(AllowedMassPoints[i])

print(AllowedMassPoints)

#modify *L
filelist = glob.glob(SignalType+"_*L/*.csv")

for f in filelist:
    df = pd.read_csv(f,' ')
    #print(df)
    df = df[df['PType'].isin(AllowedMassPoints)]
    df.to_csv(f, index=False)
    

