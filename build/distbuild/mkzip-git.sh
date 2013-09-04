#################################################################
# create openGLCD distribution zip image.
#
# This is a bash shell script to check out a openGLCD tree and build
# a distribution zip image.
#
# build process overview:
#
# - checkout a library from VCS
# - create the buildinfo files
# - update/create any needed documenation in the working directory
# - remove any uneeded/unwanted subdirectories from the working directory
# - remove the VCS tracking stuff from the working directory
# - create a zip file of the working directory.
#
# It is a bit complicated/messy because it has to capabable of running in
# multiple environments on multiple OSs.
# Becasue of the different OS's you can't force the shell processor using
# something like #!/bin/bash because the locations are not all the same and
# the windows bash shell is not even called bash.exe
#
# other uglies:
#
# Windoze uses @#!@# spaces in many directory names.
# Plus Windows has problems when the full path/filename exceeds 254 characters.
# So there are a few change directory commands used as well lots of
# quoted strings and also using some full
# paths when relative would have worked to get around stupid Windoze issues.
# Also, the windows svn has some code internally to work aound long 
# paths but it only works if you use full paths vs relative paths.
#
# Not only are there issues with Windoze but there issues whith linux too,
# especially when running this script from the nautilus GUI shell. 
# nautilus does not always properly set the $PWD variable to reflect the location
# where script is launched from.
# Also Nautilus not use $SHELL to determine which shell intrpreter to launch;
# It uses /bin/sh 
# This creates an issues as the Ubuntu boys in their
# infinite wisdom as have changed the default shell in /bin to be dash
# instead of bash but use bash for the login shells (which Nautilus does use
# when starting a terminal. So this means that when using Nautilus the script
# may start with bash or dash.
# The biggest issue is with the built in echo command in dash.
# The brilliant boys that wrote dash have broken decades of compability with 
# the echo command by not supporting # options like -e to process escape characters. 
# They support escape character processing by default, which
# is good, but but then they don't swallow a -e option to maintain compatibilty with
# the echo command (VERY stupid). This is why the printf command must be used
# instead of echo when wanting escaped character processing
#
# bottom line is that while written assuming bash, it is a goal to make
# it work on  bash,  dash, sh so that it can run without having to set
# the shell processor at the top since this will not work across platforms.
# *nix uses that use ksh may have to run it by typing 'bash xxx'
#
#
#
# Needed Tools:
# -------------
# you must have a commandline VCS tool:
#   VCS:
#	http://www.open.collab.net/downloads/subversion/
#	debian package: subversion
#   GIT
#	debian package: git
#
#
# you must have 7zip installed.
#	http://www.7-zip.org/
#	debian package: p7zip-full
#
# you must have doxygen/doxywizard installed.
#	http://www.doxygen.nl/download.html#latestsrc
#	(Make sure to have version 1.6.3 or later)
#	debian package: doxygen
#
##################################################################

#
# use TMPDIR if set otherwise assume right here for temp stuff
#

if [ "$TMPDIR" ] 
then
	PROGTEMP=$TMPDIR
else
	PROGTEMP=$(pwd)
	PROGTEMP=/tmp
fi

#
# Setup some date variable strings
#

MYDATE=`date +%Y%m%d`
MYDATETIME=`date`

# grab short name of script

PROGNAME=`basename $0`

#
# set PROGWD (program working directory) variable (grab it from current directory)
#

PROGWD=$(pwd)

#
# LOG file name (create based on baename of script file)
#

LOGFILE="$PROGWD/$PROGNAME.log"

##################################################################
#
# Define working variables
#
##################################################################

#
# name of library
# This name will be used for the name of the distribution
# directory inside the zip file.
# it is the name of the directory that will be in the
# "libraries" directory
#

GLCDLIBNAME=openGLCD

#
# location of repository
#

#GLCDREPO=http://glcd-arduino.googlecode.com/svn/trunk/glcd

# cheat and use local repo
GLCDREPO="$PROGWD/../.."

#
# VCS commands
#

#SVN
#VCSCMD="svn checkout"
# for SVN get the svn version# returned by svnversion
#VCSBUILDSTR=svnversion

#GIT
# cheat for now and simpy copy the local git repo
VCSCMD="cp -r"
#VCSBUILDSTR="git log --oneline |wc -l"
VCSBUILDSTR="git describe --dirty"

#
# zip command
#
ZIPCMD="7z a"


#
# Name of working directory for distibution tree
#  note/warning the path needs to be full vs relative
#  as svn has special code to deal with the @#@$@! 
#  windows long path issue but it only kicks in on absolute paths.
#
GLCDDISTDIR="$PROGTEMP/$GLCDLIBNAME"


#
# Doxygen command and config file stuff
#  note: doxygen must be started in the directory
#  where the config file is since all paths in the config file
#  are relative to that point.
#

DOXYGEN=doxygen
DOXYGENDIR="$GLCDDISTDIR/build/doc/doxygen"
DOXYGENCFG=Doxyfile.doxcfg

#
# name of Build Information file
#
GLCDBUILDINFO="$GLCDDISTDIR/Buildinfo.txt"
GLCDBUILDINFO_HDR="$GLCDDISTDIR/openGLCD_Buildinfo.h"
# create header file guard define name from header file name
GLCDBUILDINFO_HDR_GUARD=__$(basename "$GLCDBUILDINFO_HDR" .h)_h__ 

#
# names of build string defines
#
GLCD_GLCDLIB_DATESTR_NAME=GLCD_GLCDLIB_DATESTR
GLCD_GLCDLIB_BUILDSTR_NAME=GLCD_GLCDLIB_BUILDSTR

#
# list of unwanted directories
# these are all relative the top level library directory
# i.e. "openGLCD"
# put a space between each desired directory
#
GLCDUNWANTED="debug build .git"

#
# files/directories that no matter where they are,
# remove them from the GLCD dist directory
# be careful with this.
#
GLCDTRASH=".svn"

#
# Name of ZIP file
# has date as part of file name
#

GLCDZIPNAME="$GLCDLIBNAME-$MYDATE.zip"

##################################################################
# Now start to actually do something

echo Starting build $MYDATETIME >"$LOGFILE"

rm -rf "$GLCDDISTDIR"
echo Checking out VCS working tree to: $GLCDDISTDIR
echo ======== Checkout VCS tree to $GLCDDISTDIR >> "$LOGFILE"
echo $VCSCMD $GLCDREPO "$GLCDDISTDIR" >>"$LOGFILE"
$VCSCMD $GLCDREPO "$GLCDDISTDIR" >>"$LOGFILE"

if [ $? != 0 ]; then
	echo $PROGNAME: Fatal Error: could not checkout VCS tree
	exit 1
fi

echo Working tree is ready for processing

# 
# Must deal with and grab svn build number string before we do any mucking around with tree
#
cd "$GLCDDISTDIR"
GLCDBUILDVERSION=$($VCSBUILDSTR)
cd "$PROGWD"


#
# Create BuildInfo file(s)
# NOTE: The text file is created in DOS format for the Windoze users
#
echo Creating BuildInfo Text File "$GLCDBUILDINFO" in DOS format
echo ======== Creating BuildInfo Text File "$GLCDBUILDINFO" in DOS format >> "$LOGFILE"
printf "Distribution files created $MYDATETIME\r\n" > "$GLCDBUILDINFO"
printf "=====================================================================\r\n" >> "$GLCDBUILDINFO"
printf "BuildVersion $GLCDBUILDVERSION \r\n">> "$GLCDBUILDINFO"
printf "=====================================================================\r\n" >> "$GLCDBUILDINFO"

echo Creating BuildInfo Header file
echo ======== Creating BuildInfo Header File "$GLCDBUILDINFO_HDR" >> "$LOGFILE"
echo "//" > "$GLCDBUILDINFO_HDR"
echo "// $GLCDLIBNAME build information" >> "$GLCDBUILDINFO_HDR"
echo "// This headerfile is automatically generated" >> "$GLCDBUILDINFO_HDR"
echo "//" >> "$GLCDBUILDINFO_HDR"
echo >> "$GLCDBUILDINFO_HDR"
echo "#ifndef $GLCDBUILDINFO_HDR_GUARD"  >> "$GLCDBUILDINFO_HDR"
echo "#define $GLCDBUILDINFO_HDR_GUARD"  >> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
printf "#define $GLCD_GLCDLIB_DATESTR_NAME\\t\"$MYDATETIME\"">> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
printf "#define $GLCD_GLCDLIB_BUILDSTR_NAME\\t\"$GLCDBUILDVERSION\"" >> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
echo "#endif" >> "$GLCDBUILDINFO_HDR"

#
# Must build doxygen docs before build directory is removed
#
echo Building Doxygen Documents
echo ======== Building Doxygen Documents >> "$LOGFILE"
cd "$DOXYGENDIR"
$DOXYGEN $DOXYGENCFG  >> "$LOGFILE" 2>&1
cd "$PROGWD"

#
# Remove the unwanted directories from the distribution like "build" and "debug"
#
echo Removing unwanted directories "($GLCDUNWANTED)" from VCS working tree
echo ======== Removing unwanted directories "($GLCDUNWANTED)" from $GLCDDISTDIR >> "$LOGFILE"
cd "$GLCDDISTDIR"
for unwanted in $GLCDUNWANTED; do\
	rm -rf $unwanted ;\
done
#
# Remove the VCS control/trash directories from the distribution like "build" and "debug"
#
echo Removing VCS control files/directories "($GLCDTRASH)" from VCS working tree
echo ======== Removing trash directories "($GLCDTRASH)" from $GLCDDISTDIR >> "$LOGFILE"
for trash in $GLCDTRASH; do\
	find . -depth -name $trash -exec rm -rf '{}' ';' ;\
done

cd "$PROGWD"


echo Creating Zip file
echo ======== Creating Zip file from $GLCDDISTDIR >> "$LOGFILE"
rm -f $GLCDZIPNAME
$ZIPCMD $GLCDZIPNAME "$GLCDDISTDIR" >> "$LOGFILE"

echo Zip file $GLCDZIPNAME created
echo ======== Zip file $GLCDZIPNAME created >> "$LOGFILE"

echo Removing VCS working tree $GLCDDISTDIR
rm -rf "$GLCDDISTDIR"
echo ======== Removed VCS working tree $GLCDDISTDIR >> "$LOGFILE"

echo ======== $PROGNAME completed normally >> "$LOGFILE"

echo $PROGNAME Finished
exit 0
