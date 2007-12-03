#!/bin/bash

error=0

#
# The environment variable zorbaRepos must be defined. It should point to a
# directory containing a zorba source repository (e.g., /home/markos/zorba/xquery) 
#
if [ ! ${zorbaRepos} ]; then
   echo "ERROR 1 lbkt.sh: zorbaRepos environment variable is not set"
   exit 1
fi


#
# The environment variable zorbaExeDir must be defined. It must be set to the
# full pathname of the directory containig all the test executables
#
if [ ! ${zorbaExecDir} ]; then
   echo "ERROR 1 lbkt.sh: zorbaExecDir environment variable is not set"
   exit 1
fi

#
# testRootDir is the root directory of the test environment. It contains the
# the scripts, the test queries and their expected results, and the source docs
# to be loaded. It is also under this directory where all output from the tests
# is stored.
#
testRootDir=${zorbaRepos}/test/rbkt

# The following dirs MUST exist under the testRootDir.
scriptsDir=${testRootDir}/Scripts
queriesDir=${testRootDir}/Queries
expQueryResultsDir=${testRootDir}/ExpQueryResults
docsDir=${testRootDir}/Documents
expLoaderResultsDir=${testRootDir}/ExpLoaderResults

# This is the dir where all query results are stored. This dir is created
# by the buildDirEnv function, if it does not exist already.
queryResultsDir=${testRootDir}/QueryResults

# This is the dir where all loader results are stored. This dir is created
# by the buildDirEnv function, if it does not exist already.
loaderResultsDir=${testRootDir}/LoaderResults


#
# sourcing of common functions
#
if [ ! -e ${scriptsDir}/functions.sh ]; then
   echo "ERROR 3 lbkt.sh: ${scriptsDir}/functions.sh does not exist"
   exit 3
fi

source ${scriptsDir}/functions.sh

trap '' 12

#
# Argument parsing
#
bucketName=""
docName=""

state=0
while [ $1 ]
do
   case $1 in
   -b)        state=1;;
   -d)        state=2;;
   -h)        usage ; exit;;
    *) case $state in
       1) bucketName="$1"; state=0 ;;
       2) docName="$1"; state=0 ;;
       *) echo "ERROR 6 lbkt.sh: Wrong parameter $1"; usage; exit 6;;
       esac ;;
    esac
    shift
done

if [ $state -ne 0 ]; then
  echo "ERROR 7 lbkt.sh: Wrong arg list"; usage; exit 7;
fi


#
# Building env directories and runtime env
#
buildDirEnv
error=$?
if [ ${error} -ne 0 ]; then
  echo "ERROR 10 lbkt.sh: buildDirEnv function failed with error code ${error}"
  exit ${error}
fi


#
# Load queries
#
#echo; echo "Loading Queries"
failedDocs=0
totalDocss=0

rm -f lbkt_summary.txt

if [ "${bucketName}" != "" ]; then

  if [ "${docName}" != "" ]; then
    load_doc_in_bucket "${bucketName}" "${docName}"
    error=$?
    if [ ${error} -ne 0 ]; then
      echo "ERROR 70 lbkt.sh: load_doc_in_bucket function failed with error code ${error}"
      exit ${error}
    fi
  else
    echo; echo "Loading bucket ${bucketName}"
    load_bucket "${bucketName}" 
    error=$?
    if [ ${error} -ne 0 ]; then
      echo "ERROR 71 lbkt.sh: run_bucket function failed with error code ${error}"
      exit ${error}
    fi
  fi

else
  #bucketList=`find "${queriesSDir}" -mindepth 1 -type d -printf "%f\n"`
  bucketList="test"

  for bucketName in ${bucketList}
  do
    echo; echo "Running bucket ${bucketName}"
    load_bucket "${bucketName}"
    error=$?
    if [ ${error} -ne 0 ]; then
      echo "ERROR 72 lbkt.sh: run_bucket function failed with error code ${error}"
      exit ${error}
    fi
  done
fi

echo
echo "lbkt.sh : total number of docs   = $totalDocs"
echo "lbkt.sh : number of failed docs  = $failedDocs"

echo >> lbkt_summary.txt
echo "lbkt.sh : total number of docs   = $totalDocs" >> lbkt_summary.txt
echo "lbkt.sh : number of failed docs  = $failedDocs" >> lbkt_summary.txt

if [ ${failedDocs} -gt 0 ]; then
  exit 1
else
   exit 0
fi
