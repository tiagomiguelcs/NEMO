#!/bin/bash 
PWD_DIR="$(pwd)"
BF=$1
if [ -z "$BF" ];  then
  echo "Usage: $0 frontend|backend"
  exit 1
fi
if [[ "$BF" == "frontend" ]]; then
    cd $PWD_DIR/nemo-frontend/ && npm start
else
    cd $PWD_DIR/nemo-backend/nodejs && npm start
fi

