# Utility script to generate todo text file.
# TODO : Add support for multiline todos, although it is not necessary now.
import pathlib

todos = {}
lateTodos = {}
notes = {}
refactor = {}

def SearchFile(file, name):
    global todos
    with open(file, "r") as f:
       for line in f:
           if "// TODO : " in line:
                toFind = "// TODO : "
                todo = line[line.find(toFind) + len(toFind):]
                todos[name] = todo
           if "// TODO (late) : " in line:
                toFind = "// TODO (late) : "
                todo = line[line.find(toFind) + len(toFind):]
                lateTodos[name] = todo
           if "// NOTE : " in line:
                toFind = "// NOTE : "
                note = line[line.find(toFind) + len(toFind):]
                notes[name] = note
           if "// REFACTOR : " in line:
                toFind = "// REFACTOR : "
                refact = line[line.find(toFind) + len(toFind):]
                refactor[name] = refact

def WriteTodo():
    global todos
    with open("todo.txt", "w+") as f:
        f.write(f"=== TODOs ({len(todos)} + {len(lateTodos)}) ===\n\n")
        for file, todo in todos.items():
            f.write(f"{file} : {todo}")
        for file, todo in lateTodos.items():
            f.write(f"{file} : * {todo}")
        f.write(f"\n=== Notes ({len(notes)}) ===\n\n")
        for file, note in notes.items():
            f.write(f"{file} : {note}")
        f.write(f"\n\n=== Refactor code ({len(notes)}) ===\n\n")
        for file, refact in refactor.items():
            f.write(f"{file} : {refact}")


if __name__ == "__main__":
    for path in pathlib.Path('Build').rglob("*.cpp"):
        SearchFile(path.resolve(), path.name)
    for path in pathlib.Path('Build').rglob("*.h"):
        SearchFile(path.resolve(), path.name)
    
    WriteTodo()