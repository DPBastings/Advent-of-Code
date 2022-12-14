"""Written in Python 3.9.2."""

STAGE = 2

class Point():
    def __init__(self, field, x, y):
        self.field = field
        self.x = x
        self.y = y
        self.content = []
        
    def __repr__(self):
        return f"(X:{self.x}, Y:{self.y})"
        
    def __str__(self):
        try:
            return str(self.content[-1])
        except IndexError:
            return '.'
            
    def is_full(self):
        for o in self.content:
            if o.solid:
                return True
        return False

   
class Field(list):
    def __init__(self, minx, miny, maxx, maxy):
        super().__init__()
        for y in range(miny, maxy + 1):
            row = []
            for x in range(minx, maxx + 1):
                row.append(Point(self, x, y))
            self.append(row)
        self.minx = minx
        self.miny = miny
        self.maxx = maxx
        self.maxy = maxy
    
    def place(self, x, y, object, replace=True):
        try:
            point = self.point(x, y)
        except IndexError:
            raise IndexError
        if replace:
            point.content.clear()
        elif object.solid == True and point.is_full():
            print(f"There is already a solid object at location {point}.")
            raise ValueError
        point.content.append(object)
        object.point = point
    
    def point(self, x, y):
        return self[y-self.miny][x-self.minx]
    
    def row(self, y):
        return self[y-self.miny]
    
    def col(self, x):
        return [row[x-self.minx] for row in self]
    
    def view(self):
        for r in self:
            for point in r:
                print(point, end="")
            print("")
    
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
        try:
            move(self, self.field().point(self.x(), self.y()+1))
        except ValueError:
            try:
                move(self, self.field().point(self.x()-1, self.y()+1))
            except ValueError:
                try:
                    move(self, self.field().point(self.x()+1, self.y()+1))
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
        try:
            self.field().place(self.x(), self.y(), product, replace=False)
        except ValueError:
            raise ValueError
        if self.type == Sand:
            product.fall()

def move(object, dest):
    if object.solid == False or dest.content == [] or dest.is_full() == False:
        if object.point is not None:
            object.point.content.remove(object)
        dest.content.append(object)
        object.point = dest
    else:
        raise ValueError

def populate(field, type, instructions):
    for i in instructions:
        for start, end in zip(i, i[1:]):
            for x in ft_range(start[0], end[0], inclusive=True):
                for y in ft_range(start[1], end[1], inclusive=True):
                    field.place(x, y, type(), replace=True)
    if STAGE == 2:
        for x in range(field.minx, field.maxx + 1):
            field.place(x, field.maxy, type())

def ft_range(start, stop, inclusive=False):
    if start <= stop:
        return range(start, stop + inclusive)
    else:
        return range(stop, start + inclusive)

def get_bounds(instructions):
    tmp = list(zip(*[c for i in instructions for c in i]))
    maxy = max(tmp[1]) + 2
    minx = min(tmp[0]) - round(maxy*1,5) - 1
    miny = 0
    maxx = max(tmp[0]) + round(maxy*1,5) + 1
    return (minx, miny, maxx, maxy)

def parse(lines):
    instructions = []
    for l in lines:
        instructions.append([(int(c[0]), int(c[1])) for c in [i.split(',') for i in l.strip('\n').split()[::2]]])
    return instructions

def simulate_1(source):
    cycles = 0
    while True:
        try:
            source.generate()
        except IndexError:
            break
        cycles += 1
    return cycles

def simulate_2(source):
    cycles = 0
    while True:
        try:
            source.generate()
        except:
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
    field.view()
    if STAGE == 1:
        result = simulate_1(source)
    elif STAGE == 2:
        result = simulate_2(source)
    field.view()
    print(f"The simulation lasted for {result} cycles.")