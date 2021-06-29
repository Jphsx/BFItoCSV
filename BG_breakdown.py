import glob
import math
import sys
import pandas as pd
import numpy as np
#signal="TChiWZ"
#signal= sys.argv[1]

all_bg_files = glob.glob("csv2/BG_*L/*.csv")
#all_s_files = glob.glob("csv2/"+signal+"_*L/*.csv")

pd.set_option('display.max_colwidth',None)
pd.set_option('display.max_columns', None)
pd.set_option('expand_frame_repr', False)
pd.set_option('display.max_rows', None)

#df = pd.read_csv ('csv2/BG_2L/Ch2L_OSOHmumu-muGmuG-2j0bS-ge1jge1bISR-PTISR0-gamT0.csv')
#df = pd.read_csv ('csv2/BG_2L/*.csv')

li = []
li2 = []

for filename in all_bg_files:
    df = pd.read_csv(filename, index_col=None, header=0, delimiter=" ")
    li.append(df)

#for filename in all_s_files:
#    df = pd.read_csv(filename, index_col=None, header=0, delimiter=" ")
#    li2.append(df)

allbgframe = pd.concat(li, axis=0, ignore_index=True)
#allsframe = pd.concat(li2, axis=0, ignore_index=True)


allbgframe = allbgframe.loc[ ((allbgframe['Yield'] < 1e-8)) ]
allbgframe = allbgframe.loc[ ((allbgframe['Yield'] > -999)) ]
allbgframe = allbgframe.loc[ ((allbgframe['PType'] != 'dataobs')) ]

print( allbgframe )

