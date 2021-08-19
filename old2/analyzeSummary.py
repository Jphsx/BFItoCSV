
import pandas as pd
import numpy as np

import glob
import math
import sys

import matplotlib.pyplot as plt


df = pd.read_csv("TChiWZ_SensitivitySummary.csv", index_col=None, header=0)
#print(df)

df["Region Desc."] = df.NL.astype(str)+df.NJ.astype(str)+df.BinN.astype(str)+"__"+ df.RegionName +"__"+ df.PType
df0 = df.loc[ df["NL"] == 0]
df1 = df.loc[ df["NL"] == 1]
df2 = df.loc[ df["NL"] == 2]
df3 = df.loc[ df["NL"] == 3]
#print(df0)
#colsb = df0["S/B"]
h=df0.plot.barh(x="Region Desc.",y='S/B')
h2=df1.plot.barh(x="Region Desc.",y='S/B')
h3=df2.plot.barh(x="Region Desc.",y='S/B')
h4=df3.plot.barh(x="Region Desc.",y='S/B')
plt.tight_layout()
plt.show()


