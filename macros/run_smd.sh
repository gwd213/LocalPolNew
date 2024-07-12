#!/bin/bash
#
# condor executes runana.cmd 0, runana.cmd 1, etc.
# where $1 = 0, 1, etc...
#

source /sphenix/u/jaein213/.bashrc

#print the environment - needed for debugging
#printenv


condor=true
condorrun=0
condorjobs=500
fullrun=true
fname="DST_TRIGGERED_EVENT_run2pp_new_2024p003-00045495-%04d.root"
ofname1="/sphenix/tg/tg01/coldqcd/ZDCLocalPol/test/45495/zdcneutronlocpol_45495_%04d.root"
ofname2="/sphenix/tg/tg01/coldqcd/ZDCLocalPol/test/45495/zdcneutronlocpol_45495_%04d_%04d.root"

# Extract directory paths from the filenames
dir1=$(dirname "$ofname1")

# Check if directory exists, if not, create it
if [ ! -d "$dir1" ]; then
echo "Directory $dir1 does not exist. Creating..."
mkdir -p "$dir1"
fi

if [ "$condor" = false ]; then    
    #=================== Run standalone =========================#
    startevent=100000
    index=0
    filename=$(printf "$fname" $index)

    if [ "$fullrun" = true ]; then	
	outname=$(printf "$ofname1" $index)
	root -l -q "Fun4All_ZDCNeutronLocPol.C(\"$filename\",\"$outname\")"
    else
	outname=$(printf "$ofname2" $index $startevent)
	root -l -q "Fun4All_ZDCNeutronLocPol.C(\"$filename\",\"$outname\", $startevent)"
    fi
    #=========================================================#

else
    #=================== Run with condor =========================#
    startevent=$(( ${1}*100000))
    filename=$(printf "$fname" $(( ${1} + condorrun * condorjobs )))

    if [ "$fullrun" = true ]; then
	outname=$(printf "$ofname1" $(( ${1} + condorrun * condorjobs )))
	root -l -q "Fun4All_ZDCNeutronLocPol.C(\"$filename\",\"$outname\")"
    else
	outname=$(printf "$ofname2" ${1} ${1})
	root -l -q "Fun4All_ZDCNeutronLocPol.C(\"$filename\",\"$outname\", $startevent)"
    fi
    #=========================================================#
fi
