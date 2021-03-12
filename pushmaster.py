#!/usr/bin/python3

import os
import sys

message = "Default python script message"
if len(sys.argv) > 1:
    message = sys.argv[1]

if __name__ == '__main__':
    os.system("git add .")
    os.system(f"git commit -m \"{message}\"")
    os.system("git add .")
