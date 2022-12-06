def readfile(name):
    contents = []
    
    with open(f"{name}.txt", 'r') as f:
        while (True):
            tmp = f.readline()
            if not tmp:
                break
            contents.append(tuple(tmp.rstrip('\n').split(',')))
    return (contents)

def smallest(assignment):
    return (int(assignment.split('-')[0]))

def greatest(assignment):
    return (int(assignment.split('-')[-1]))

def check_full_overlap(one, other):
    if (smallest(one) >= smallest(other) and greatest(one) <= greatest(other)):
        return (True)
    return (False)

def check_overlap(one, other):
    if (smallest(one) in range(smallest(other), greatest(other) + 1)
      or greatest(one) in range(smallest(other), greatest(other) + 1)):
        return (True)
    return (False)

def run(name=None):
    overlaps = 0
    full_overlaps = 0
    
    if not name:
        name = input("file: ")
    contents = readfile(name)
    for e, i in enumerate(contents):
        if (check_overlap(i[0], i[1]) or check_overlap(i[1], i[0])):
            overlaps += 1
        if (check_full_overlap(i[0], i[1]) or check_full_overlap(i[1], i[0])):
            full_overlaps += 1
    print(f"There are {overlaps} overlaps, {full_overlaps} of which are full.")