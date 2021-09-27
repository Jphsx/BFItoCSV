












import pandas as pd
import numpy as np

import glob
import math
import sys

import csv
#create dictionary
binmap={}
with open('bindict_b51.csv', mode='r') as infile:
#with open('bindict_b53.csv', mode='r') as infile:
    reader = csv.reader(infile, delimiter=' ')
    binmap = {rows[0]:rows[1:] for rows in reader}

del binmap['binKey']
#print(binmap)
#exit()


#/home/justin/work/research/susy/6-30-21/bindict.csv
#signal="TChiWZ"

#signal= sys.argv[1]

#all_bg_files = glob.glob("./BG_2l1j2j3j/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_5-1_16/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_5-1_17/BG_*L/*.csv")

#all_bg_files = glob.glob("./BG_5-1_18/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_5-2/BG_*L/*.csv")

#all_bg_files = glob.glob("./BG_6-1_17/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_6-2_17/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_7-2_17/BG_*L/*.csv")

#all_bg_files = glob.glob("./BG_5-3_17/BG_*L/*.csv")
#all_bg_files = glob.glob("./BG_5-5_17/BG_*L/*.csv")
all_bg_files = glob.glob("./BG_BT-1_17/BG_*L/*.csv")

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


allbgframe = allbgframe.loc[ ((allbgframe['PType'] == 'all-bkg')) ]


#study of all bg with all-bkg################################
#testbg = allbgframe[ ['RegionName','BinN','NL','NJ','Yield','Error'] ]
#testbg['Rel Error'] = testbg.Error / testbg.Yield
#testbg['Yield'] = testbg['Yield'].round(4)
#print(testbg.shape)
#print(testbg)
#print(testbg.to_csv(index=False))
#exit()

##############################################################

#print(allbgframe.shape)
#print(allbgframe)
#print(allsframe.shape)
#print(allsframe)

#allbgframe.set_index('RegionName', verify_integrity=True)
#allsframe.set_index('RegionName',verify_integreity=True)

#make special indexing rows, index on bg
allbgframe['idx']=allbgframe['BinN'].astype(str) + allbgframe.RegionName

#add binning
allbgframe['binKey'] = allbgframe['NL'].astype(int).astype(str)+"_"+allbgframe['NJ'].astype(int).astype(str)+"_"+allbgframe['BinN'].astype(int).astype(str)
allbgframe['BinEdges'] = allbgframe['binKey'].map(binmap)
#print(allbgframe[['binKey','BinEdges']])

#print(allbgframe)
#exit()
#map binedges into individual columns
allbgframe[['Rlow','Rhigh','Mplow','Mphigh']] = pd.DataFrame(allbgframe.BinEdges.tolist(), index= allbgframe.index)



allbgframe = allbgframe[ ['RegionName','BinN','NL','NJ','Yield','Error','Rlow','Rhigh','Mplow','Mphigh'] ]
allbgframe['Rel Err'] = allbgframe.Error/allbgframe.Yield
allbgframe['Yield'] = allbgframe['Yield'].round(4)

#allbgframe = allbgframe.loc[ (allbgframe['NL'] == 2) ]
#allbgframe = allbgframe.loc[ (allbgframe['NJ'] == 3) ]
#allbgframe = allbgframe.loc[ (allbgframe['NJ'] == 1) ]

#test stuff to simplify
#allbgframe = allbgframe.loc[ (allbgframe['RegionName'].str.contains("OSSHelel")) ] 

#allbgframe = allbgframe.loc[ allbgframe['RegionName'].str.contains("bS",case=True) ]
#allbgframe = allbgframe[ ['RegionName','BinN','NJ','Yield'] ]


#uncomment for removing bsplit from 1J
#allbgframe['RegionName'] = allbgframe['RegionName'].str.replace("0bS","")
#allbgframe['RegionName'] = allbgframe['RegionName'].str.replace("1bS","")

#uncomment for removing bsplit from 3J
#allbgframe['RegionName'] = allbgframe['RegionName'].str.replace("0bS", "")
#allbgframe['RegionName'] = allbgframe['RegionName'].str.replace("ge1bS","")

#allbgframe = allbgframe.groupby(['RegionName','BinN'])['Yield'].sum()
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




exit()

#study of bg with less that 1 event##############################################################
emptybg = allbgframe.loc[ ((allbgframe['Yield'] < 1)) ]
emptybg = emptybg[ ['RegionName','BinN','NL','NJ','Yield','Error','Rlow','Rhigh','Mplow','Mphigh'] ]
emptybg = emptybg.sort_values(by=['NL', 'NJ'])
emptybg = emptybg[ ['RegionName','BinN','Yield','Error','Rlow','Rhigh','Mplow','Mphigh' ] ]
emptybg['Rel Err'] = emptybg.Error/emptybg.Yield
emptybg['Yield'] = emptybg['Yield'].round(4)
emptybg2 = emptybg.loc[ ((emptybg['Rel Err']==0))]
emptybg = emptybg.loc[ ((emptybg['Rel Err']>0.4)) ]
print("No BG detected")
print(emptybg2.shape)
print(emptybg2)
#print("Low BG detected, RelErr>0.4")
#print("High RelErr detected BG>1, RelErr>0.75")
#print(emptybg.shape)
#print(emptybg)
exit()
###special csv prints
#print(emptybg.to_csv(index=False))
###
#exit()
#########################################################################################

#test = allbgframe.loc[allbgframe['idx'] == "1Ch2L_OSSHmumu-muGmuG-1j1bS-ge1j0bISR-PTISR1-gamT0" ]
#print("test", test)
#allbgframe.set_index('idx', verify_integrity=True)

#allbgframe.index = allbgframe['idx']
allsframe['idx']=allsframe['BinN'].astype(str) + allsframe.RegionName

#XU = 300
#XL = 330
XU = int(sys.argv[2])
XL = int(sys.argv[3])
maxdm = int(sys.argv[4])
#allsframe['XU'] = allsframe.loc[ (allsframe['PType'].split("_"))[1] ]

# new data frame with split value columns
mass_str = allsframe['PType'].str.split("_", n = 1, expand = True)
#print(mass_str) 
# making separate first name column from new data frame
allsframe["XU"]= mass_str[1].astype(int)
allsframe["LSP"]= mass_str[1].astype(int)
#print(allsframe["XU"])
#allsframe["XU"]= allsframe["XU"].round(-4)
allsframe["XU"]=(allsframe['XU'] / 1000).astype(int) *1000
allsframe["LSP"] = allsframe.LSP - allsframe.XU
#print(allsframe["XU"])
allsframe["XU"]= allsframe["XU"]/10000
allsframe["DM"] = allsframe.XU - allsframe.LSP
allsframe = allsframe.loc[ ((allsframe['XU'] >= XU) & (allsframe['XU'] < XL)) ]

if maxdm != -1:
    allsframe = allsframe.loc[ ((allsframe['DM'] < maxdm)) ]
#print(allsframe["XU"]) 


#print("indexed")
#print(allbgframe['idx'])
#print(allbgframe.shape)
#print(allbgframe[0:50])
#print(allsframe.shape)
#print(allsframe[0:100])

dictdf =allbgframe[ ['idx','Yield'] ]
#print(dictdf)
dictdf = dictdf.set_index('idx').to_dict()['Yield']


dictdf2 = allbgframe[ ['idx','Error'] ]
dictdf2 = dictdf2.set_index('idx').to_dict()['Error']
#print("dict")
#print(dictdf)
#allsframe['BGYield'] = allbgframe.loc[allsframe['idx'],'Yield' ]


allsframe['BGYield'] = allsframe['idx'].map(dictdf).apply(lambda x: x)#x[0] if type(x)==list else x)
allsframe['BGError'] = allsframe['idx'].map(dictdf2).apply(lambda x: x)

allsframe['BG RelErr'] = allsframe.BGError / allsframe.BGYield
allsframe['S/B'] = allsframe.Yield/allsframe.BGYield

##test print for full summary
#testframe = allsframe[ ['idx','PType','S/B','Yield','BGYield','BG RelErr' ] ] 
#print(testframe)

#exit()
####end test print for full summary
####TEMP REMOVING CUT ON 1%
#allsframe = allsframe.loc[allsframe['S/B']>0.01 ]

##print(allsframe)
#grouped_single = allsframe.groupby('idx').agg({'RegionName': 'first','BinN':'first', 'PType':'first', 'S/B': ['max'], 'Yield':'first','BGYield':'first', 'BGError':'first','BG RelErr':'first'})

#this works!
grouped_single = allsframe.loc[allsframe.groupby(["idx"])["S/B"].idxmax()]  

grouped_single = grouped_single.reset_index()
#grouped_single.drop('idx')
sensitive_regions = pd.DataFrame(grouped_single)
#sensitive_regions.drop('idx')
sensitive_regions['S RelErr'] = sensitive_regions.Error/sensitive_regions.Yield
sensitive_regions['S RelErr'] = sensitive_regions['S RelErr'].round(3)
sensitive_regions = sensitive_regions[ ['RegionName','NL','NJ', 'BinN', 'PType', 'S/B','Yield','S RelErr','BGYield','BG RelErr'] ]
sensitive_regions['S/B'] = sensitive_regions['S/B'].round(3)
sensitive_regions['Yield'] = sensitive_regions['Yield'].round(3)
sensitive_regions['BGYield'] = sensitive_regions['BGYield'].round(3)
sensitive_regions['BG RelErr'] = sensitive_regions['BG RelErr'].round(3)
sensitive_regions = sensitive_regions.loc[sensitive_regions['S RelErr'] < 0.5 ] 
sensitive_regions = sensitive_regions.sort_values(by=['NL', 'NJ','RegionName','BinN'])#,'RegionName'])
sensitive_regions = sensitive_regions.loc[sensitive_regions['BGYield'] > 0]
#print(sensitive_regions.shape)
#print(sensitive_regions)
#print(sensitive_regions.to_string(index=False))
print(sensitive_regions.to_csv(index=False))
#print(grouped_single)

#print(allsframe.shape)
#print(allsframe[0:100])
#for index, row in allsframe.iterrows():
    #print(row['c1'], row['c2'])
#    allsframe.loc[index, 'BG'] = allbgframe.loc[ ((allbgframe['RegionName'] == row['RegionName']) & (allbgframe['BinN'] == row['BinN']) )]
 #   allsframe.loc[index,'BGYield'] = allbgframe.loc[ row['idx'], 'Yield' ]

#print(allbgframe.shape)
#print(allbgframe)
#print(allsframe.shape)
#print(allsframe[0:1000])

#print(allbgframe.head)
#top = allbgframe.head()
#print(top)
#test = allbgframe['PType']
#print(test)
#for col in allbgframe.columns:
#    print(col)

#allbgframe = allbgframe.loc[ ((allbgframe['PType'] == 'all-bkg') & (allbgframe['NL'] == 2) & (allbgframe['NJ'] == 1)) ] 
#risr1 = allbgframe.loc[ allbgframe['BinN'] == 1 ]
#risr1sum = risr1['Yield'].sum()
#risr1sumErr = math.sqrt((risr1['Error']**2).sum())

#print(risr1sum,"+/-",risr1sumErr)
#print(risr1)

#print(allbgframe.shape)
##print(allbgframe)

#def getSB(njets, nleptons, bgdf, sdf):
#    allbgframe = allbgframe.loc[ ((allbgframe['PType'] == 'all-bkg') & (allbgframe['NL'] == 2) & (allbgframe['NJ'] == 1)) ]
#    risr1 = allbgframe.loc[ allbgframe['BinN'] == 1 ]
#    risr1sum = risr1['Yield'].sum()

#print(allbgframe.head)
#print(allsframe.head)


#sbThresh = 0.01
#compute s/b and add to sframe
#allframe = allsframe
#allframe['BGYield'] = allbgframe.loc[ allbgframe['RegionName'] == allsframe['RegionName'] ]

#allsframe.sort_values(by=['RegionName'])
#allbgframe.sort_values(by=['RegionName'])

#for index, row in allframe.iterrows():
    #print(row['c1'], row['c2'])

#print(allbgframe.shape)
#print(allsframe.shape)
#print(allbgframe.head)
#print(allsframe.head)
#print(allframe.head())
#allsframe['sb'] = allsframe.loc[ all
#
