# Created by:   VPR
# Created:      August 18th, 2025

# Updated by:   VPR
# Updated:      August 18th, 2025

FROM ubuntu:24.04

# Set env to avoid user input interruption during installation
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# install normal goodies
RUN apt-get update && apt upgrade -y
RUN apt-get install -y --no-install-recommends \
    vim \
    make \
    build-essential \
    mingw-w64-common \
    mingw-w64-i686-dev \
    mingw-w64-tools \
    mingw-w64 \
    nasm

# Create working environment
ENV HOME=/root
WORKDIR /var/sp3-dev/sp3
