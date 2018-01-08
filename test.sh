#!/bin/bash

OBSERVE="plinker"

function block_for_change {
  inotifywait -r -e modify,move,create,delete $OBSERVE
}

function run {
    time php ~/php_inbuilt/code/client.php
}

run

while block_for_change; do
    run
done