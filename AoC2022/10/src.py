CHECKS_1 = range(20, 221, 40)
CHECKS_2 = range(40, 241, 40)
WIDTH = 40

class Screen(list):
    def __init__(self, width=WIDTH):
        super().__init__()
    
    def draw(self):
        for p in self:
            print(p, end="")
        print("")
        self.clear()

class Processor():
    def __init__(self, x=1):
        self.x = x
        self.cycles = 0
        self.output = []
        self.screen = Screen()
    
    def sprite(self):
        return range(self.x - 1, self.x + 2)
    
    def cycle(self):
        if self.cycles % WIDTH in self.sprite():
            self.screen.append('#')
        else:
            self.screen.append('.')
        self.cycles += 1
        if self.cycles in CHECKS_1:
            self.output.append(self.x * self.cycles)
        if self.cycles in CHECKS_2:
            self.screen.draw()
    
    def noop(self, *args):
        self.cycle()
    
    def addx(self, v):
        for _ in range(0, 2):
            self.cycle()
        self.x += v

def parse(line):
    tmp = line.strip('\n').split()
    try:
        return (tmp[0], int(tmp[1]))
    except IndexError:
        return (tmp[0], 0)

def run():
    cpu = Processor(1)
    with open(input("input: "), 'r') as f:
        instructions = [parse(line) for line in f.readlines()]
    for i in instructions:
        getattr(cpu, i[0])(i[1])
    print(cpu.output)
    print(sum(cpu.output))