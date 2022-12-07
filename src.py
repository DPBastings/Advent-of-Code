"""Written in Python 3.10.8."""

class Directory(object):
    def __init__(self, name, parent, contents=[]):
        super().__init__()
        self.name = name
        self.parent = parent
        self.contents = []
    
    def __repr__(self):
        return f"dir '{self.name}' ({self.size()} B)"
    
    def view(self, layer=0):
        for _ in range(0, layer):
            print("  ", end="")
        print("- ", end="")
        print(f"{self.name} (dir, contains {self.size()} B)")
        for i in self.contents:
            i.view(layer + 1)
    
    def size(self):
        s = 0
        for i in self.contents:
            if type(i) == File:
                s += i.size
            else:
                s += i.size()
        return s

class File(object):
    def __init__(self, name, size):
        super().__init__()
        self.name = name
        self.size = size

    def view(self, layer=0):
        for _ in range(0, layer):
            print("  ",end="")
        print("- ", end="")
        print(f"{self.name} (file, size={self.size} B)")

    def extension(self):
        return self.name.split('.')[-1]


class Command(object):
    def __init__(self, cmd, target=None):
        super().__init__()
        self.cmd = cmd
        self.target = target


class Filesystem(object):
    def __init__(self):
        super().__init__()
        self.root = Directory("/", None)
        self.current = self.root
    
    def navigate(self, target):
        if target == "..":
            self.current = self.current.parent
        elif target == "/":
            pass
        else:
            for c in self.current.contents:
                if c.name == target:
                    self.current = c
                    break ;
            else:
                print(f"Error: directory {target} not found in {self.current.name}.")
                
def dirfilter_maxsize(dir, maxsize):
    res = []
    for i in dir.contents:
        if type(i) == Directory:
            if i.size() <= maxsize:
                res.append(i)
            res.extend(dirfilter_maxsize(i, maxsize))
    return res

def dirfilter_minsize(dir, minsize):
    res = []
    for i in dir.contents:
        if type(i) == Directory:
            if i.size() >= minsize:
                res.append(i)
            res.extend(dirfilter_minsize(i, minsize))
    return res

def parse_line(line, current_dir):
    tmp = line.split()
    if tmp[0] == "$":
        try:
            return Command(tmp[1], tmp[2])
        except IndexError:
            return Command(tmp[1], None)
    elif tmp[0] == "dir":
        return Directory(tmp[1], current_dir)
    else:
        return File(tmp[1], int(tmp[0]))

def build_filesystem(input):
    files = Filesystem()
    
    for l in input:
        x = parse_line(l, files.current)
        if type(x) == Command:
            if x.cmd == "ls":
                pass
            elif x.cmd == "cd":
                files.navigate(x.target)
        elif type(x) == Directory or type(x) == File:
            files.current.contents.append(x)
    return files

def run():
    data = []

    with open(input("input: "), 'r') as f:
        data.extend(f.readlines())
    files = build_filesystem(data)
    files.root.view()
    x = dirfilter_maxsize(files.root, 100000)
    print(x)
    print(sum(d.size() for d in x))
    needed_space = 30000000 - (70000000 - files.root.size())
    print(f"The device requires at least {needed_space} B more space.")
    y = sorted(dirfilter_minsize(files.root, needed_space), key=lambda d: d.size())
    print(y)