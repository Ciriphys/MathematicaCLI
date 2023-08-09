# Run script used to launch the program.

import platform
import os

if __name__ == "__main__":
    system = platform.system()
    args = input("Arguments: ")
    target = input("*Debug or Release?: ")
    projectName = "Mathematica"
    command = ""

    if target.lower() == "release":
        target = "Release"
    else:
        target = "Debug"

    if system == "Darwin" or system == "Linux":
        print(f"If the command fails, please use chmod +x on path : ./Binaries/{target}-macosx-x86_64/{projectName}/{projectName}.")
        command = f"./Binaries/{target}-macosx-x86_64/{projectName}/{projectName} {args}"
    elif system == "Windows":
        command = f"\"Binaries\\{target}-windows-x86_64\\{projectName}\\{projectName}.exe\" {args}"
    else:
        print("Unidentified system. Halting.")
        exit(1)

    os.system(command)
