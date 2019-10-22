#!/bin/sh
## fake_client.sh for  fake_client
##
## Made by  SRJanel
## Content  Excellency  Department
##

SERVER=${1-12.34.56.78}
PORT=${2-4242}
PASSWORD=${3-"epitech"}
SOURCE_PORT=54321
PHASE1_MESSAGE="client  hello"

challenge=`echo -n $PHASE1_MESSAGE | socat -t 1 - UDP:$SERVER:$PORT,sourceport=$SOURCE_PORT` || exit 84
[ -z "$challenge" ] && exit 84

challenge=$challenge$PASSWORD
challenge_response=`echo -n $challenge | sha256sum | cut -d' ' -f1`

## Adding  character 'X' after  response  to test  the  Protocol  mismatch  feature
#challenge_response ="${challenge_response}X"

authentication_response=`echo -n $challenge_response | socat -t 1 - UDP:$SERVER:$PORT,sourceport=$SOURCE_PORT`|| exit 84
[ -z "$authentication_response" ] && exit 84
if [ "$authentication_response" = "KO" ];  then
    echo $authentication_response
else
  echo "Secret: '$authentication_response'"
fi
