import platform
import os

if __name__ == "__main__":
    system = platform.system()
    command = ""

    if system == "Darwin":
        selection = input("Enter the action (gmake2 ~ Makefile | xcode4 ~ XCode): ")
        command = f"./Vendor/premake5/macOS/premake5 {selection}"
    elif system == "Windows":
        command = str("\"Vendor\\premake5\\Windows\\premake5.exe\" vs2022")
    elif system == "Linux":
        print("Linux is not yet supported. Halting.")
        exit(1)
    else:
        print("Unidentified system. Halting.")
        exit(1)

    print(command)
    os.system(command)
