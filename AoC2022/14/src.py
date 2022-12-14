"""Written in Python 3.9.2."""

class Point():
    def __init__(self, field, x, y):
        self.field = field
        self.x = x
        self.y = y
        self.content = []
    def __repr__(self):
        return f"(X:{self.x}, Y:{self.y})"
    def __str__(self):
        if self.content == None:
            return '.'
        return str(self.content)

   
class Field(list):
    def __init__(self, minx, miny, maxx, maxy):
        super().__init__()
        for x in range(minx, maxx + 1):
            for y in range(miny, maxy + 1):
                self.append(Point(self, x, y))
        self.origin = (minx, miny)
    
    def place(self, x, y, object, overwrite=False):
        try:
            point = self.point(x, y)
            move(object, point)
        except ValueError:
            if not overwrite:
                print(f"Coordinate {x}, {y}) is already occupied by {point.content})")
            else:
                del point.content
                move(object, point)
    
    def point(self, x, y):
        for point in self:
            if point.x == x and point.y == y:
                return point
        print(f"Point ({x}, {y}) is out of bounds.")
        raise IndexError
    
    def row(self, y):
        return [point for point in self if point.y == y]
    
    def col(self, x):
        return [point for point in self if point.x == x]

    def view(self):
        i = self.origin[1]
        row = self.row(i)
        while row:
            row.sort(key=lambda p: p.x)
            for point in row:
                print(point, end="")
            print("")
            i += 1
            row = self.row(i)
    
class Material():
    def __init__(self, point=None):
        self.point = point
    
    def field(self):
        return self.point.field
    
    def x(self):
        return self.point.x
    
    def y(self):
        return self.point.y


class Rock(Material):
    solid = True
    def __init__(self, point=None):
        super().__init__(point)
    
    def __str__(self):
        return '#'
    

class Sand(Material):
    solid = True
    def __init__(self, point=None):
        super().__init__(point)
        
    def __str__(self):
        return 'o'
    
    def fall(self):
        try: move(self, self.field().point(self.x(), self.y()+1))
        except ValueError:
            try: move(self, self.field().point(self.x()-1, self.y()+1))
            except ValueError:
                try: move(self, self.field().point(self.x()+1, self.y()+1))
                except ValueError: return
        except IndexError:
            print(f"Error: sand would fall off the grid. The simulation is probably over.")
            raise IndexError
        self.fall()


class Source(Material):
    solid = False
    def __init__(self, type, point=None):
        super().__init__(point)
        self.type = type
    
    def __str__(self):
        return '+'
    
    def generate(self):
        product = self.type()
        self.field().place(self.x(), self.y()+1, product)
        if self.type == Sand:
            product.fall()

def move(object, dest):
    if dest.content == None or object.solid == False:
        if object.point is not None:
            object.point.content.remove(object)
        object.point = dest
        object.point.content.append(object)
    else:
        raise ValueError

def populate(field, type, instructions):
    for i in instructions:
        for start, end in zip(i, i[1:]):
            for x in ft_range(start[0], end[0], inclusive=True):
                for y in ft_range(start[1], end[1], inclusive=True):
                    field.place(x, y, type())

def ft_range(start, stop, inclusive=False):
    if start <= stop:
        return range(start, stop + inclusive)
    else:
        return range(stop, start + inclusive)

def get_bounds(instructions):
    tmp = list(zip(*[c for i in instructions for c in i]))
    minx = min(tmp[0]) - 1
    miny = 0
    maxx = max(tmp[0]) + 1
    maxy = max(tmp[1]) + 3
    return (minx, miny, maxx, maxy)

def parse(lines):
    instructions = []
    for l in lines:
        instructions.append([(int(c[0]), int(c[1])) for c in [i.split(',') for i in l.strip('\n').split()[::2]]])
    return instructions

def simulate(source):
    cycles = 0
    while True:
        try:
            source.generate()
        except IndexError:
            break
        cycles += 1
    return cycles

def run(input_file):
    with open(input_file, 'r') as f:
        instructions = parse(f.readlines())
    field = Field(*get_bounds(instructions))
    populate(field, Rock, instructions)
    source = Source(Sand)
    field.place(500, 0, source)
    result = simulate(source)
    field.view()
    print(f"The simulation lasted for {result} cycles.")