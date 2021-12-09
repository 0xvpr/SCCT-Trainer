# Creator: VPR
# Created: December 9, 2021
# Updated: December 9, 2021

# Gets the required mingw compiler

set -o pipefail
set -o errexit
set -o nounset
set -o xtrace

apt update && apt upgrade -y
apt install -y --no-install-recommends \
                                       mingw-w64 \
                                       mingw-w64-common \
                                       mingw-w64-i686-dev \
                                       mingw-w64-x86-64-dev \
