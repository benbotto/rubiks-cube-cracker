#!/bin/bash

set -e

if [ "$1" = "" ]
then
  echo "Usage: $0 <tag>"
  exit 1
fi

TAG=$1
PROJECT=avejidah
IMAGE=rubiks-cube-cracker-builder

# Build and push latest.
docker build \
  --build-arg UID=$(id -u) \
  -t $PROJECT/$IMAGE:latest \
  .

docker push $PROJECT/$IMAGE:latest

# Tag and push.
docker tag \
  $PROJECT/$IMAGE:latest \
  $PROJECT/$IMAGE:${TAG}

docker push $PROJECT/$IMAGE:${TAG}
