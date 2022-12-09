"""Written in Python 2.7.16."""

XDIM = 512
YDIM = 512
START = (XDIM // 2, (YDIM - 1) // 2)
INSTRUCTIONS = {"R": (1, 0), "L": (-1, 0), "U": (0, 1), "D": (0, -1)}

class Instruction(object):
    def __init__(self, direction, dist):
        self.direction = direction
        self.dist = int(dist)
    def __repr__(self):
        return "{0} {1}".format(self.direction, self.dist)


class Knot(object):
    def __init__(self, x, y, head=None):
        self.x = x
        self.y = y
        self.head = head

    def move(self, direction, dist):
        if direction == "R":
            self.x += 1
        elif direction == "L":
            self.x -= 1
        elif direction == "U":
            self.y -= 1
        elif direction == "D":
            self.y += 1

    def follow(self):
        if self.head.x > self.x + 1:
            self.y = self.head.y
            self.x = self.head.x - 1
        elif self.head.x < self.x - 1:
            self.y = self.head.y
            self.x = self.head.x + 1
        elif self.head.y > self.y + 1:
            self.x = self.head.x
            self.y = self.head.y - 1
        elif self.head.y < self.y - 1:
            self.x = self.head.x
            self.y = self.head.y + 1

class Rope(object):
    def __init__(self, field, head, knots):
        self.field = field
        self.knots = [head]
        for n in range(0, knots):
            k = Knot(self.head().x, self.head().y, self.knots[n])
            self.knots.append(k)
    
    def head(self):
        return self.knots[0]

    def tail(self):
        return self.knots[-1]
    
    def move(self, direction, dist):
        self.head().move(direction, dist)
        for k in self.knots[1:]:
            k.follow()
        self.field[self.tail().y][self.tail().x] = '#'

class Field(list):
    def __init__(self):
        super(list, self).__init__()
        for _ in range (0, YDIM):
            self.append(["." for _ in range(0, XDIM)])

    def view(self):
        for r in self:
            for c in r:
                print c,
            print ""
    
    def export(self):
        s = ""
        for r in self:
            for c in r:
                s += c,
            s += '\n'
        return s

    def check_visited(self):
        x = 0
        for r in self:
            for c in r:
                if c == '#' or c == 's':
                    x += 1
        return x

def parse(line):
    return (Instruction(*line.split()))

def run():
    with open(input("input: "), 'r') as f:
        instructions = [parse(l) for l in f.readlines()] 
    field = Field() 
    rope = Rope(field, Knot(*START), 9)
    for n, i in enumerate(instructions):
        for _ in range(0, i.dist):
            try:
                rope.move(i.direction, 1)
            except IndexError:
                print n, i
                quit()
    field[START[1]][START[0]] = 's'
    #field.view()
    print "The tail has visited {0} positions.".format(field.check_visited()) 
    #return field.export()

run()
