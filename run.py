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

    if system == "Darwin":
        command = f"./bin/{target}-macosx-x86_64/{projectName}/{projectName} {args}"
    elif system == "Windows":
        command = f"\"bin/{target}-windows-x86_64/{projectName}/{projectName}.exe\" {args}"
    elif system == "Linux":
        print("Linux is not yet supported. Halting.")
        exit(1)
    else:
        print("Unidentified system. Halting.")
        exit(1)

    os.system(command)
