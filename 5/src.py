class Data(object):
    def __init__(self, stacks, instructions):
        super().__init__()
        self.stacks = Stacks(stacks)
        self.instructions = instructions

class Stacks(list):
    def __init__(self, stacks):
        super().__init__()
        for s in stacks:
            self.append(s)
        
    def move(self, amount, src, dst):
        tmp = []
        for _ in range(0, amount):
            tmp.append(self[src - 1].pop())
        tmp.reverse()
        self[dst - 1].extend(tmp)
        del tmp

def parse_file(name):
    data = []
    instructions = []
    with open(f"{name}.txt", 'r') as f:
        rawdata = []
        while (True):
            tmp = f.readline()
            if (tmp[0] == '\n'):
                break
            rawdata.append(tmp)
        rawinstructions = []
        while (True):
            tmp = f.readline()
            if not tmp:
                break
            rawinstructions.append(tmp)
    data = parse_data(rawdata)
    for i in rawinstructions:
        instructions.append(parse_instruction(i))
    return (data, instructions)

def parse_data(raw_data):
    stacks = [[] for _ in range(0, 9)]
    
    for l in raw_data:
        for i, c in enumerate(l):
            if ((i - 1) % 4 == 0 and c.isalpha()):
                stacks[i // 4].append(c)
    for s in stacks:
        s.reverse()
    return (stacks)

def parse_instruction(instruction):
    tmp = instruction.split()
    return (int(tmp[1]), int(tmp[3]), int(tmp[5]))

def run():
    data = Data(*parse_file(input("input: ")))
    print(data.stacks)
    print(data.instructions)
    for i in data.instructions:
        data.stacks.move(*i)
    print(data.stacks)
    return (data)