

import pandas as pd
import numpy as np

import glob
import math
import sys

import csv


csvdir = sys.argv[1]
all_bg_files = glob.glob(csvdir+"/BG_*L/*.csv")


pd.set_option('display.max_colwidth',None)
pd.set_option('display.max_columns', None)
pd.set_option('expand_frame_repr', False)
pd.set_option('display.max_rows', None)


li = []
li2 = []

for filename in all_bg_files:
    df = pd.read_csv(filename, index_col=None, header=0, delimiter=" ")
    li.append(df)


allbgframe = pd.concat(li, axis=0, ignore_index=True)


allbgframe = allbgframe.loc[ ((allbgframe['PType'] == 'all-bkg')) ]




allbgframe = allbgframe[ ['RegionName','BinN','NL','NJ','Yield','Error'] ]
allbgframe['Rel Err'] = allbgframe.Error/allbgframe.Yield
allbgframe['Yield'] = allbgframe['Yield'].round(4)


print("Full shape")
print(allbgframe.shape)

#print(allbgframe)
#allbgframe = allbgframe.reset_index()
print("0.1< Yield < 1")
subframe = allbgframe.loc[((allbgframe['Yield']<1)  & (allbgframe['Yield']>0.1)) ]
subframe['Yield'] = subframe['Yield'].round(5)
print(subframe.shape)
print(subframe)

print("0.01 < Yield < 0.1")
subframe2 = allbgframe.loc[((allbgframe['Yield']<0.1)  & (allbgframe['Yield']>0.01)) ]
subframe2['Yield'] = subframe2['Yield'].round(5)
print(subframe2.shape)
print(subframe2)


print("0 < Yield < 0.01")
subframe3 = allbgframe.loc[((allbgframe['Yield']<0.01)) ]
subframe3['Yield'] = subframe3['Yield'].round(5)
print(subframe3.shape)
print(subframe3)






