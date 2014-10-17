#!/bin/bash
# CDAMoviePlayer installation script v0.1

NAME='CDAMoviePlayer'
C='gcc'

# REQUIRMENTS
QMAKE_R='30'
QT_R='5'

# PATHS
MAKE_PATH=$(find $BIN_PATH -name make)

# LIBS
L_PATH='/usr/lib/'
L_CURL=$(find $L_PATH -name libcurl.so)
L_REGEX=$(find $L_PATH -name libboost_regex.so)

function end {
    echo ">> Ending..."
    exit 1
}

clear

echo '####################################'
echo '###  CDA Movie Player Compiler #####'
echo '############  v 0.1  ###############'
echo '####################################'




echo '>> Checking Qt path...'
if [ -z "$QTDIR" ]
then
    echo '>>> Enter Qt installation path:'
    read QT_PATH

else
        QT_PATH="$QTDIR"
fi

QMAKE_PATH=$(find "$QT_PATH/$C/bin" -name qmake)
QMAKE_VER=$($QMAKE_PATH -v | sed -e 's/\([^0-9$].\)+$/\1/p; 2d' | sed 's/QMake version //' | sed 's/\.//')
QT_VER=$($QMAKE_PATH -v | sed -e 's/\([^0-9$].\)+$/\1/p; 1d' | sed 's/Using Qt version //' | sed 's/ in*.*//' | sed 's/\([^0-9$].\)*$//')

if [ ! -d "$QT_PATH/$C/mkspecs" ]
then
    echo ".........in $QT_PATH is not found Qt!"
    end
fi

if [ -e $QMAKE_PATH ]
then
    echo ".........qmake found in $QT_PATH"

    if [ $QMAKE_VER -ge $QMAKE_R ]
    then echo ".........qmake version ok"
    else
        QMAKE_PATH=$(find "$BIN_PATH/$C/bin" -name qmake)
        QT_VER=$($QMAKE_PATH -v | sed -e 's/\([^0-9$].\)+$/\1/p; 1d' | sed 's/Using Qt version //' | sed 's/ in*.*//' | sed 's/\([^0-9$].\)*$//')
        if [ $QMAKE_VER -ge $QMAKE_R ]
        then
            echo ".........qmake version ok"
        fi
    fi

else

    if [ $QMAKE_VER -ge $QMAKE_R ]
    then echo ".........qmake version ok"
    else
        QMAKE_PATH=$(find "$BIN_PATH/$C" -name qmake)
        QT_VER=$($QMAKE_PATH -v | sed -e 's/\([^0-9$].\)+$/\1/p; 1d' | sed 's/Using Qt version //' | sed 's/ in*.*//' | sed 's/\([^0-9$].\)*$//')
        if [ $QMAKE_VER -ge $QMAKE_R ]
        then
            echo ".........qmake version ok"
        fi
    fi
fi


if [ $QT_VER -ge $QT_R ]
    then echo ".........qt version ok"
fi

echo '>> Check Curl...'
if [ -e "$L_CURL" ]
then
    echo '.........found'
else
    echo "[ERROR] libcurl not found in $L_PATH"
    end
fi


echo '>> Check Boost-regex...'
if [ -e "$L_REGEX" ]
then
    echo '.........found'
else
    echo "[ERROR] libboost-regex not found in $L_PATH"
    end
fi


echo '>> Running qmake...'
$QMAKE_PATH -r "$PWD/$NAME.pro" -spec "$QT_PATH/$C/mkspecs/linux-g++/"

echo '.........done'


echo '>> Running make'
make clean && make
