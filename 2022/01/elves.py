def parse(file):
    elves = []
    with open(file, 'r') as f:
        elf = []
        for line in f.readlines():
            if line[0] == '\n':
                elves.append(elf)
                elf = []
                continue
            elf.append(int(line[:-1]))
    return (elves)

def total_calories(elf):
    total = 0
    for s in elf:
        total += s
    return (total)

def fattest_elf(elves, top):
    totals = []
    
    for elf in elves:
        totals.append(total_calories(elf))
    totals.sort()
    return (sum(totals[-top:]))

elves = parse("input.txt")
with open("result.txt", 'w') as file:
    result = fattest_elf(elves, int(input("top value: ")))
    file.write(str(result))