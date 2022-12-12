"""Written in Python 3.9.2."""

from copy import copy

class Point():
    def __init__(self, field, x, y, z):
        self.field = field
        self.x = x
        if y == 'S':
            self.y = 0
        elif y == 'E':
            self.y = 25
        else:
            self.y = ord(y) - 97
        self.z = z
    
    def __repr__(self):
        return f"(X:{self.x}, Y:{self.y} ({self.ychar()}), Z:{self.z})"
    
    def ychar(self):
        return chr(self.y + 97)
    
    def adjoins(self, point, inverse=False):
        if self in point.adjoining(inverse):
            return "X"
        if point is self:
            return "@"
        return "."
    
    def adjoining(self, inverted=False):
        res = Field()
        res.append(self.field.point(self.x+1, self.z))
        res.append(self.field.point(self.x-1, self.z))
        res.append(self.field.point(self.x, self.z+1))
        res.append(self.field.point(self.x, self.z-1))
        if inverted:
            return [p for p in res if p.y >= self.y - 1]
        return [p for p in res if p.y <= self.y + 1]

class Field(list):
    def __init__(self):
        super().__init__()
        self.start = None
        self.goal = None
    
    def append(self, object, /):
        if object is None:
            pass
        else:
            super().append(object)
    
    def point(self, x, z):
        for p in self:
            if p.x == x and p.z == z:
                return p
        return None
    
    def row(self, z):
        return [p for p in self if p.z == z]
    
    def col(self, x):
        return [p for p in self if p.x == x]
    
    def view(self, attr="ychar", *args):
        i = 0
        row = self.row(i)
        while row:
            row.sort(key=lambda p: p.x)
            for p in row:
                print(f"[{getattr(p, attr)(*args)}]", end="")
            print("")
            i += 1
            row = self.row(i)

def dijkstra(field):
    path = []
    for p in field:
        setattr(p, "distance", 9999999)
        setattr(p, "previous", None)
    field.start.distance = 0
    unvisited_points = copy(field)
    while unvisited_points:
        check = min(unvisited_points, key=lambda p: p.distance)
        unvisited_points.remove(check)
        if check is field.goal:
            return get_path(check)
        for a in check.adjoining():
            alternative = check.distance + 1
            if alternative < a.distance:
                a.distance = alternative
                a.previous = check
    print("No valid path to goal was found.")
    return -1
    
def dijkstra_reverse(field):
    path = []
    for p in field:
        setattr(p, "distance", 9999999)
        setattr(p, "previous", None)
    field.goal.distance = 0
    unvisited_points = copy(field)
    while unvisited_points:
        unvisited_points.sort(key=lambda p: p.distance)
        check = unvisited_points.pop(0)
        if check.y == 0:
            return get_path(check)
        for a in check.adjoining(inverted=True):
            alternative = check.distance + 1
            if alternative < a.distance:
                a.distance = alternative
                a.previous = check
    print("No valid path to y=a(0) was found.")
    return -1

def dijkstra_reset(field):
    for p in field:
        delattr(p, "distance")
        delattr(p, "previous")

def get_path(end):
    path = []
    while end.previous:
        path.append(end)
        end = end.previous
    return path

def parse(name):
    field = Field()
    with open(name, 'r') as f:
        for z, r in enumerate(f.readlines()):
            for x, y in enumerate(r.strip('\n')):
                point = Point(field, x, y, z)
                if y == 'S':
                    field.start = point
                elif y == 'E':
                    field.goal = point
                field.append(point)
    return field

def run():
    field = parse(input("input: "))
    field.view("ychar")
    path = dijkstra(field)
    print(path)
    print(f"The shortest route to E is {len(path)} steps in length.")
    dijkstra_reset(field)
    path = dijkstra_reverse(field)
    print(path)
    print(f"The distance between E and the closest y=a point is {len(path)} steps.")