def readfile(name):
    contents = []
    rucksacks = []
    with open(name, 'r') as f:
        contents = f.readlines()
    #for r in contents:
    #    r = r[:-1]
    #    rucksacks.append(compartmentalize(r))
    return (contents)

def compartmentalize(rucksack):
    half = int(len(rucksack) / 2)
    return (rucksack[0:half], rucksack[half:])

def find_duplicate(rucksack):
    for i in rucksack[0]:
        if i in rucksack[1]:
            return (i)
    return (None)

def find_groups(contents):
    groups = []
    group = []
    for e, r in enumerate(contents):
        group.append(r)
        if (e % 3 == 2):
            groups.append(group)
            group = []
    return (groups)

def find_badge(group):
    for i in (group[0]):
        if (i in group[1] and i in group[2]):
            return (i)
    return (None)

def get_priority(item):
    ascii = (ord(item))
    if (96 < ascii < 123):
        return (ascii - 96)
    else:
        return (ascii - 38)

def run_1():
    priority_total = 0
    contents = readfile(input("input: "))
    for r in contents:
        priority_total += get_priority(find_duplicate(r))
    print(contents)
    print(priority_total)

def run_2():
    priority_total = 0
    contents = readfile(input("input: "))
    groups = find_groups(contents)
    for g in groups:
        priority_total += get_priority(find_badge(g))
    print(priority_total)