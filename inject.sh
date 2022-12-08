#!/bin/bash

# Creator: VPR
# Created: December 14th, 2021
# Updated: December 24th, 2021

# This script is intended to work with Pidjeon for a seamless injection process.

TARGET="splintercell3.exe"      # Change as necessary
PAYLOAD="bin/sp3.dll"           # Change as necessary
PIDJEON_PATH="${HOME}/.toolkit" # Change as necessary

export PATH=$PATH:"${PIDJEON_PATH}"

function inject {
    vpr-pidjeon "${TARGET}" "${PAYLOAD}" -i ManualMap
}

inject
