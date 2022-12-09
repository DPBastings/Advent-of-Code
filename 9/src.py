"""Written in Python 3.9.2."""

XDIM = 256
YDIM = 256
START = (XDIM // 2, (YDIM - 1) // 2)

class Instruction(object):
    def __init__(self, direction, dist):
        self.direction = direction
        self.dist = int(dist)
    def __repr__(self):
        return f"{self.direction}, {self.dist}"


class Knot(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def follow(self, prev):
        if prev.x > self.x + 1:
            self.x = prev.x - 1
            if prev.y > self.y:
                self.y += 1
            elif prev.y < self.y:
                self.y -= 1
        elif prev.x < self.x - 1:
            self.x = prev.x + 1
            if prev.y > self.y:
                self.y += 1
            elif prev.y < self.y:
                self.y -= 1
        elif prev.y > self.y + 1:
            self.y = prev.y - 1
            if prev.x > self.x:
                self.x += 1
            elif prev.x < self.x:
                self.x -= 1
        elif prev.y < self.y - 1:
            self.y = prev.y + 1
            if prev.x > self.x:
                self.x += 1
            elif prev.x < self.x:
                self.x -= 1

class Rope(object):
    def __init__(self, knots, field, start=START):
        self.field = field
        self.knots = [Knot(*start) for _ in range(0, knots)]

    def head(self):
        return self.knots[0]
    
    def tail(self):
        return self.knots[-1]
    
    def move(self, direction):
        if "R" in direction:
            self.head().x += 1
        if "L" in direction:
            self.head().x -= 1
        if "U" in direction:
            self.head().y -= 1
        if "D" in direction:
            self.head().y += 1
        for n, k in enumerate(self.knots[1:]):
            k.follow(self.knots[n])
    
    def display(self):
        self.field[self.head().y][self.head().x].value = 'H'
        for n, k in enumerate(self.knots[1:]):
            self.field[k.y][k.x].value = n + 1


class Cell():
    def __init__(self, value):
        self.value = value
    
    def __repr__(self):
        return f"{self.value}"

class Field(list):
    def __init__(self):
        super(list, self).__init__()
        for _ in range (0, YDIM):
            self.append([Cell(".") for _ in range(0, XDIM)])
        self[START[1]][START[0]].value = 's'
    
    def reset(self):
        for r in self:
            for c in r:
                c.value = "."
        self[START[1]][START[0]].value = 's'
    
    def view(self):
        for r in self:
            for c in r:
                print(c, end="")
            print("")
    
    def check_visited(self):
        x = 0
        for r in self:
            for c in r:
                if c.value == '#' or c.value == 's':
                    x += 1
        return x

def parse(line):
    return (Instruction(*line.split()))

def run(knots):
    with open(input("input: "), 'r') as f:
        instructions = [parse(l) for l in f.readlines()] 
    field = Field() 
    rope = Rope(knots, field)
    for n, i in enumerate(instructions):
        for _ in range(0, i.dist):
            rope.move(i.direction)
            field[rope.tail().y][rope.tail().x].value = '#'
        #rope.display()
        #field.view()
        #print("")
        #field.reset()
    #field.view()
    print(f"The tail has visited {field.check_visited()} positions.")
    #return field.export()