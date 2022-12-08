"""Written in Python 3.10.9."""

class Tree():
    def __init__(self, x, y, field, height):
        self.x = x
        self.y = y
        self.field = field
        self.height = height
    
    def __repr__(self):
        return f"{self.height}"
    
    def checked_trees(self):
        return [self.field.row(self.y)[self.x+1:],
                self.field.row(self.y)[:self.x][::-1],
                self.field.col(self.x)[self.y+1:],
                self.field.col(self.x)[:self.y][::-1]]
    
    def in_checked(self, tree):
        return self in [t for r in tree.checked_trees() for t in r]
    
    def visible(self):
        for x in self.checked_trees():
            for t in x:
                if t.height >= self.height:
                    break
            else:
                return True
        return False
    
    def score(self):
        score = 1
        viewdist = 0
        for x in self.checked_trees():
            for t in x:
                viewdist += 1
                if t.height >= self.height:
                    break
            score *= viewdist
            viewdist = 0
        return score

class Field(list):
    def __init__(self):
        super().__init__()
    
    def view(self, attr, *args):
        for r in self:
            for t in r:
                value = getattr(t, attr)
                if isinstance(value, int):
                    print(value, end="")
                else:
                    print(int(value(*args)), end="")
            print("")
        print("")
    
    def row(self, index):
        return self[index]
    
    def col(self, index):
        return [r[index] for r in self]
    
    def best_tree(self):
        return max([max(r, key=lambda t: t.score()) for r in self], 
                    key=lambda t: t.score())

def parse(input):
    field = Field()
    for y, r in enumerate(input):
        row = []
        for x, c in enumerate(r.strip('\n')):
            row.append(Tree(x, y, field, int(c)))
        field.append(row)
    return field

def readfile():
    with open(input("input: "), 'r') as f:
        field = parse(f.readlines())
    return field

def run():
    visible_trees = 0
    field = readfile()
    for r in field:
        for t in r:
            if t.visible():
                visible_trees += 1
    field.view("visible")
    field.view("height")
    print(f"There are {visible_trees} trees visible.")
    best = field.best_tree()
    print(f"The tree at [{best.x}:{best.y}] has the highest score ({best.score()}).")
    return (field)