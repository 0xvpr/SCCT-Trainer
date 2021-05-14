import os
import sys
import shutil
import subprocess

cmake_args  = [ "cmake" ]
cmake_args += [ "-G", "Visual Studio 16 2019" ]
cmake_args += [ "-A", "Win32" ]
cmake_args += [ "-B", "build" ]

build_args  = [ "cmake" ] 
build_args += [ "--build", "build" ]
build_args += [ "--config", "Release" ]

plus  = lambda x: print(f"[\x1B[0;32m+\x1B[0;0m] {x}") # Green plus
minus = lambda x: print(f"[\x1B[0;31m-\x1B[0;0m] {x}") # Red minus

if __name__ == "__main__":
    if 'bin' not in os.listdir("."):
        os.mkdir("bin")

    if 'build' not in os.listdir("."):
        os.mkdir("build")

    assert "bin" in os.listdir(".")
    assert "build" in os.listdir(".")
    minus("Attempting to clean './build'")
    for f in os.listdir(f"./build"):
        minus(f"Attempting to remove './build/{f}'")
        try:
            os.remove(f"./build/{f}")
        except PermissionError:
            shutil.rmtree(f"./build/{f}")
        except:
            print("Could not remove contents from './build/'")
            sys.exit(1)

    assert len(os.listdir('./build')) == 0
    p_gen = subprocess.run(cmake_args,
                           stdout=sys.stdout.buffer,
                           stderr=sys.stdout.buffer)

    assert p_gen.returncode == 0
    p_build = subprocess.run(build_args,
                             stdout=sys.stdout.buffer,
                             stderr=sys.stdout.buffer)

    assert p_build.returncode == 0
    minus("Attempting to remove './bin'")
    shutil.rmtree("./bin")

    plus("Moving './bin/Release' './bin'")
    shutil.move("./build/Release", "./bin")

    plus("Build successful")
    plus(f"File: './bin/{os.listdir('./bin')[0]}'")
