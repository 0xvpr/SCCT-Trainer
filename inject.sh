#!/bin/bash

# Creator:    VPR
# Created:    December 14th, 2021
# Updated:    March 16th, 2021

# Description:
#     This script is intended to work with Pidjeon for a seamless injection process.

TARGET="splintercell3.exe"      # Change as necessary
PAYLOAD="Lib/sp3.dll"           # Change as necessary
PIDJEON_PATH="${HOME}/.toolkit" # Change as necessary

function inject {
    if [[ $(type vpr-pidjeon_x86) ]]
    then
        vpr-pidjeon_x86 "${TARGET}" "${PAYLOAD}" -i ManualMap
        exit
    else
        echo "vpr-pidjeon_x86 not installed globally."
    fi

    if ! [ -d ${PIDJEON_PATH} ]
    then
        ${PIDJEON_PATH}/vpr-pidjeon_x86.exe ${TARGET} ${PAYLOAD} -i ManualMap
    else
        echo "${PIDJEON_PATH} does not exist."
    fi
}

inject
