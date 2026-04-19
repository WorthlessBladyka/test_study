#!/bin/bash

ARCH="amd64"
VERSION="v1.35.0"

curl -LO "https://dl.k8s.io/release/${VERSION}/bin/linux/${ARCH}/kubectl"
sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl