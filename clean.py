import platform
import shutil
import os

def RemoveFile(path):
    if os.path.isfile(path):
        os.remove(path)
        print(f"Cleaned {path}.")
    else:
        print(f"No file named {path} was found.")
    return

def WrapperRemoveTree(path):
    try:
        shutil.rmtree(path)
        print(f"Cleaned {path}.")
    except FileNotFoundError:
        print(f"No directory named {path} was found!")
    except PermissionError:
        print(f"{path} could not be deleted cause it is used by a process. \nTerminate it and relaunch the script to remove {path}.")
    return

def DarwinCleanMakefile():
    RemoveFile("Makefile")
    RemoveFile("build/Makefile")
    return

def DarwinCleanXCode():
    workspace = f"{projectName}.xcworkspace/"
    project = f"build/{projectName}.xcodeproj/"
    WrapperRemoveTree(workspace)
    WrapperRemoveTree(project)
    print(f"Cleaned {workspace}, {project}.")
    return

def WinCleanVS():
    solution = f"{projectName}.sln"
    project = f"build/{projectName}.vcxproj"
    user = f"build/{projectName}.vcxproj.user"
    filt = f"build/{projectName}.vcxproj.filters"
    vsfold = ".vs/"
    RemoveFile(solution)
    RemoveFile(project)
    RemoveFile(user)
    RemoveFile(filt)
    WrapperRemoveTree(vsfold)
    return

if __name__ == "__main__":
    system = platform.system()
    projectName = "Mathematica"

    if system == "Darwin":
        if os.path.exists("Makefile"):
            DarwinCleanMakefile()
        else:
            DarwinCleanXCode()

    elif system == "Windows":
        WinCleanVS()

    elif system == "Linux":
        print("Linux is not yet supported. Halting.")
        exit(1)

    else:
        print("Unidentified system. Halting.")
        exit(1)

    WrapperRemoveTree("bin/")
    print("Nothing left to clean. Halting")
    exit(0)
