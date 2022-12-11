RELIEF = False
g_superdivisor = 1

from types import MethodType
import copy

class Monkey:
    def __init__(self, name):
        self.name = name
        self.inventory = []
        self.items_handled = 0
    
    def __repr__(self):
        return f"Monkey {self.name}: {self.inventory}"
    
    def inspect(self):
        #print(f"  Monkey inspects an item with a worry level of {self.inventory[0]}.")
        self.calculate()
        if RELIEF:
            self.inventory[0] //= 3
            print(f"    Monkey gets bored with item. Worry level is divided by 3 to {self.inventory[0]}.")
        else:
            self.inventory[0] %= g_superdivisor
        self.items_handled += 1
    
    def calculate(self):
        pass
    
    def test(self):
        pass
    
    def throw(self, monkey):
        monkey.inventory.append(self.inventory.pop(0))

def cycle(monkeys):
    for m in monkeys:
        #print(f"Monkey {m.name}:")
        for i in range(0, len(m.inventory)):
            m.inspect()
            recipient = m.test()
            #print(f"    Item with worry level {m.inventory[0]} is thrown to monkey {recipient}.")
            m.throw(monkeys[recipient])

def set_calculate(monkey, operator, operand):
    if operand == "old":
        if operator == '*':
            def calculate(self=None):
                self.inventory[0] *= self.inventory[0]
                #print(f"    Worry level is squared and is now {self.inventory[0]}.")
        elif operator == '+':
            def calculate(self=None):
                self.inventory[0] += self.inventory[0]  
                #print(f"    Worry level is doubled and is now {self.inventory[0]}.")
    else:
        if operator == '*':
            def calculate(self=None):
                self.inventory[0] *= operand
                #print(f"    Worry level is multiplied by {operand} to {self.inventory[0]}.")
        elif operator == '+':
            def calculate(self=None):
                self.inventory[0] += operand
                #print(f"    Worry level is increased by {operand} to {self.inventory[0]}.")
    monkey.calculate = MethodType(calculate, monkey)

def set_test(monkey, divisor, monkey_a, monkey_b):
    def test(self=None):
        if self.inventory[0] % divisor == 0:
            #print(f"    Current worry level is divisible by {divisor}.")
            return monkey_a
        #print(f"    Current worry level is not divisible by {divisor}.")
        return monkey_b
    monkey.test = MethodType(test, monkey)

def parse(block):
    global g_superdivisor
    
    monkey = Monkey(int(block[0][1].strip(':')))
    
    for i in block[1][2:]:
        monkey.inventory.append(int(i.strip(',')))
    try:
        args = (block[2][-2], int(block[2][-1]))
    except ValueError:
        args = (block[2][-2], "old")
    set_calculate(monkey, *args)
    g_superdivisor *= int(block[3][-1])
    args = (int(block[3][-1]), int(block[4][-1]), int(block[5][-1]))
    set_test(monkey, *args)
    return monkey

def calculate_business(monkeys):
    monkeys.sort(key=lambda m: m.items_handled)
    return (monkeys[-1].items_handled * monkeys[-2].items_handled)

def run(cycles=20):
    monkeys = []
    
    with open(input("input: "), 'r') as f:
        data = f.readlines()
        block = []
        for l in data:
            if l == "\n":
                monkeys.append(parse(block))
                block = []
            else:
                block.append(l.strip('\n').split())
        monkeys.append(parse(block))
    for c in range(1, cycles + 1):
        cycle(monkeys)
        if c == 1 or c == 20 or c % 1000 == 0:
            print(f"== After round {c} ==")
            for m in monkeys:
                print(f"Monkey {m.name} inspected items {m.items_handled} times.")
    print(f"Monkey business after {cycles} cycles: {calculate_business(copy.copy(monkeys))}")