


# Overview
Code consists of two stages
(1) C based tool that generates CSV files of yields from BFI
(2) python pandas script that operates on dataframe created from CSV files

# CSV creation
There are two scripts macroBG.C and macroS.C. Both take input of number of leptons
and create a directory which a have a csv file for every sub region for the defined
lepton multiplicity. Each csv file contains the yields and errors for every mperp and
risr bin. The signal csv files (macroS) contain all of the mass grid of the specified
process. The BG csv files (macroBG) contain the contributions from all background contributions.

The BFI input files have both "signal like" contributions and fakes muf0 elf0 ... etc
The macro automatically adds the TH1Ds for both signal-like and fakes.

The inputs files that are automatically read in are the BFI root files.
- BG input file is hardcoded on line 268
- Sig input files are passed in on call (They need to follow a naming convention)

# shell scripts to run
runBG.sh will automatically run over all lepton channels
runS.sh will run a specific signal over all lepton channels
run_runS.sh will run over all known signal processes


# Pandas scripts
These scripts pull together BG and a chosen signal and stitch together all lepton channels
into a single dataframe for analysis

much of the scripts are many little analyses that i comment in and out
do extract reasonable output to look at, there are two approaches
with both I simply pipe the python std out into a file
python script.py > output.x
(1) printing dataframe.to_csv(index=False) -- this method i reanalyze sliced down frames
(2) printing dataframe -- this method is very readable

# Old 
The main directory hosts code that operates on the latest version of BFI
The old directory can be used on the old version with the old naming convention
specifically "Ch1L-" (old) versus "CH1L_" (new)


