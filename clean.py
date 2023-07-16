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
    RemoveFile("Build/Makefile")
    WrapperRemoveTree(".vscode/")
    return

def DarwinCleanXCode():
    workspace = f"{projectName}.xcworkspace/"
    project = f"Build/{projectName}.xcodeproj/"
    WrapperRemoveTree(workspace)
    WrapperRemoveTree(project)
    print(f"Cleaned {workspace}, {project}.")
    return

def WinCleanVS():
    solution = f"{projectName}.sln"
    project = f"Build/{projectName}.vcxproj"
    user = f"Build/{projectName}.vcxproj.user"
    filt = f"Build/{projectName}.vcxproj.filters"
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
        if os.path.exists("Makefile") or os.path.exists(".vscode/"):
            DarwinCleanMakefile()
        else:
            DarwinCleanXCode()

    elif system == "Windows":
        WinCleanVS()

    elif system == "Linux":
        DarwinCleanMakefile()

    else:
        print("Unidentified system. Halting.")
        exit(1)

    WrapperRemoveTree("Binaries/")
    print("Nothing left to clean. Halting")
    exit(0)
