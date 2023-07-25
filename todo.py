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
                if not name in todos:
                    todos[name] = []
                todos[name].append(todo)
           if "// TODO (late) : " in line:
                toFind = "// TODO (late) : "
                todo = line[line.find(toFind) + len(toFind):]
                if not name in lateTodos:
                    lateTodos[name] = []
                lateTodos[name].append(todo)
           if "// NOTE : " in line:
                toFind = "// NOTE : "
                note = line[line.find(toFind) + len(toFind):]
                if not name in notes:
                    notes[name] = []
                notes[name].append(note)
           if "// REFACTOR : " in line:
                toFind = "// REFACTOR : "
                refact = line[line.find(toFind) + len(toFind):]
                if not name in refactor:
                    refactor[name] = []
                refactor[name].append(refact)

def WriteTodo():
    global todos
    with open("todo.txt", "w+") as f:
        f.write(f"=== TODOs ===\n\n")
        for file, todo in todos.items():
            for t in todo:
                f.write(f"{file} : {t}")
        for file, todo in lateTodos.items():
            for t in todo:
                f.write(f"{file} : * {t}")
        f.write(f"\n=== Notes ===\n\n")
        for file, note in notes.items():
            for n in note:
                f.write(f"{file} : {n}")
        f.write(f"\n\n=== Refactor code ===\n\n")
        for file, refact in refactor.items():
            for r in refact:
                f.write(f"{file} : {r}")


if __name__ == "__main__":
    for path in pathlib.Path('Build').rglob("*.cpp"):
        SearchFile(path.resolve(), path.name)
    for path in pathlib.Path('Build').rglob("*.h"):
        SearchFile(path.resolve(), path.name)
    
    WriteTodo()