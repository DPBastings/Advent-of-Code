"""Written in Python 2.7.16."""

class Point(object):
    is_pos = False
    is_goal = False
    path = '.'

    def __init__(self, field, x, y, z):
        #super(object, self).__init__()
        self.field = field
        self.x = x
        self.z = z
        if y == 'S':
            self.is_pos = True
            self.y = 'a'
        elif y == 'E':
            self.is_goal = True
            self.path = 'E'
            self.y = 'z'
        else:
            self.y = y

    def __repr__(self):
        return "(X:{0}, Y:{1}, Z:{2})".format(self.x, self.y, self.z)
    
    def __str__(self):
        if self.is_pos:
            return 'S'
        if self.is_goal:
            return 'E'
        return str(self.y)
    
    def adjoining(self):
        tmp = []
        res = []
        if self.x > 0:
            tmp.append(self.field.row(self.z)[self.x-1])
        try:
            tmp.append(self.field.row(self.z)[self.x+1])
        except IndexError:
            pass
        if self.z > 0:
            tmp.append(self.field.col(self.x)[self.z-1])
        try:
            tmp.append(self.field.col(self.x)[self.z+1])
        except IndexError:
            pass
        for p in tmp:
            if ord(p.y) <= ord(self.y) + 1:
                res.append(p)
        return res

class Field(list):
    def __init__(self, data):
        super(list, self).__init__()
        for z, r in enumerate(data):
            self.append([Point(self, x, y, z) for x, y in enumerate(list(r))])

    def row(self, x):
        return self[x]
    
    def col(self, z):
        return [r[z] for r in self]
    
    def points(self):
        return (p for r in self for p in r)
    
    def start(self):
        for p in self.points():
            return p
    
    def goal(self):
        for p in self.points():
            if p.is_goal:
                return p
   
    def view(self):
        for r in self:
            for p in r:
                print str(p),
            print ""

    def view_path(self):
        for r in self:
            for p in r:
                print p.path,
            print ""

    def path_reset(self):
        for p in self.points():
            if p.path != 'E':
                p.path = '.'
    

class PathfindCheck(object):
    def __init__(self, dist, prev=None):
        self.dist = dist
        self.prev = prev
    def __repr__(self):
        return "dist: {0}, prev: {1}".format(self.dist, self.prev.__repr__())


def dijkstra(field):
    start = field.start()
    unvisited = {p: PathfindCheck(9999999) for p in field.points()}
    unvisited[start].dist = 0
    visited = {}
    while unvisited: 
        path = []
        tmp = unvisited.items()
        tmp.sort(key=lambda p: p[1].dist)
        checkpoint = tmp[0]
        unvisited.pop(checkpoint[0])
        print "Checking point {0}.".format(checkpoint)
        if checkpoint[0] == field.goal():
            return checkpoint[1].dist
        current_len = checkpoint[1].dist + 1
        for a in checkpoint[0].adjoining():
            try:
                if current_len < unvisited[a].dist:
                    unvisited[a].dist = current_len
                    unvisited[a].prev = checkpoint[0]
                else:
                    print "backtracking..."
            except KeyError:
                pass
    print "No valid path was found."
    return -1

def run():
    with open(input("input: "), 'r') as f:
        field = Field([l.strip('\n') for l in f.readlines()])
    field.view()
    path = dijkstra(field)
    print path
    #field.view_path()
    #return field
