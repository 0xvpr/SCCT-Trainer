#!/bin/bash

# Creator: VPR
# Created: December 14th, 2021
# Updated: December 24th, 2021

# This script is intended to work with Pidjeon for a seamless injection process.

TARGET="splintercell3.exe"      # Change as necessary
PAYLOAD="lib/sp3.dll"           # Change as necessary

function inject {
    vpr-pidjeon-x86.exe "${TARGET}" "${PAYLOAD}" -i ManualMap
}

inject
