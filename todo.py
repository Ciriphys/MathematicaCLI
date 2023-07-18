# Utility script to generate todo text file.
# TODO : Add support for multiline todos, although it is not necessary now.
import pathlib

todos = {}

def SearchFile(file, name):
    global todos
    with open(file, "r") as f:
       for line in f:
           if "// TODO : " in line:
                toFind = "// TODO : "
                todo = line[line.find(toFind) + len(toFind):]
                todos[name] = todo

def WriteTodo():
    global todos
    with open("todo.txt", "w+") as f:
        f.write("=== TODOs (file : todo) ===\n\n")
        for file, todo in todos.items():
            f.write(f"{file} : {todo}")

if __name__ == "__main__":
    for path in pathlib.Path('Build').rglob("*.cpp"):
        SearchFile(path.resolve(), path.name)
    for path in pathlib.Path('Build').rglob("*.h"):
        SearchFile(path.resolve(), path.name)
    
    WriteTodo()