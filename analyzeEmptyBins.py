
import pandas as pd
import numpy as np
pd.set_option('display.max_colwidth',None)
pd.set_option('display.max_columns', None)
pd.set_option('expand_frame_repr', False)
pd.set_option('display.max_rows', None)



#df1 = pd.read_csv('Emptybin_noSmooth.csv') 
#df2 = pd.read_csv('EmptyBin_smooth.csv')

#low bin lines
df1 = pd.read_csv('LowBG_noSmooth.csv')
df2 = pd.read_csv('LowBG_smooth.csv')
df1 = df1[ ['RegionName','BinN'] ]
df2 = df2[ ['RegionName','BinN'] ]


    
df = df1.merge(df2, how = 'outer' ,indicator=True).loc[lambda x : x['_merge']=='left_only']
print("unsmoothed elements not in smoothed set")
print(df.shape)
print(df)


df = df1.merge(df2, how = 'outer' ,indicator=True).loc[lambda x : x['_merge']=='right_only']
print("smoothed elements not in unsmoothed set")
print(df.shape)
print(df)
