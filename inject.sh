#!/bin/bash

# Creator: VPR
# Created: December 14th, 2021
# Updated: February 26th, 2024

# This script is intended to work with Pidjeon for a seamless injection process.

TARGET="splintercell3.exe"      # Change as necessary
PAYLOAD="lib/sp3.dll"           # Change as necessary

! [[ $(which vpr-pidjeon) ]] && echo 'vpr-pidjeon' not found in path && exit 1
vpr-pidjeon "${TARGET}" "${PAYLOAD}" -i ManualMap
