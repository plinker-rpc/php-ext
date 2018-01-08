#!/bin/bash

#
# Build.sh - 
#  Helper script which monitors changes, builds then starts php 
#  inbuilt server to run test script.
#
#  Works most of the time; but sometimes throws segfault when starting php server :/
#

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root: sudo bash build.sh" 
   exit 1
fi

SRC="plinker"
TST="../../php_inbuilt/code"

function block_for_change {
    inotifywait -q -r -e modify,move,create,delete $SRC $TST
}

function stop_php_server {
    for pid in $(ps -ef | awk '/php -S 0.0.0.0/{print $2}'); do  
        echo "Killing PHP process: $pid"
        sudo kill -9 $pid
    done
}

function start_php_server {
    sudo nohup php -S 0.0.0.0:81 -t "$TST" >nohup.out 2>&1 &
}

function run_test_script {
    time php $TST/client.php
}

function build {

    clear

    echo "Stopping PHP inbuilt server"
    stop_php_server

    # build extension
    echo "Building $SRC extension"
    zephir build
    
    sleep 1
    
    echo "Starting PHP inbuilt server"
    start_php_server
    
    sleep 3

    echo "Executing test script"
    echo "---------------------"
    run_test_script
}

build

while block_for_change; do
    build
done