SCORE_VALUES = {'A': 1, 'B': 2, 'C': 3}

def readfile(name):
    data = []
    
    with open(name, 'r') as file:
        data = file.readlines()
    return (data)

def is_draw(opponent, me):
    if (opponent == me):
        return (True)
    else:
        return (False)

def opponent_wins(opponent, me):
    if ((opponent == 1 and me == 3)
      or (opponent == 2 and me == 1)
      or (opponent == 3 and me == 2)):
        return (True)
    else:
        return (False)

def i_win(opponent, me):
    if ((me == 1 and opponent == 3)
      or (me == 2 and opponent == 1)
      or (me == 3 and opponent == 2)):
        return (True)
    else:
        return (False)

def get_score(match):
    opponent = SCORE_VALUES[match[0]]
    
    if (match[2] == "X"):
        me = opponent - 1
        if (me == 0):
            me = 3
        opponent += 6
    elif (match[2] == "Y"):
        opponent += 3
        me = opponent
    else:
        me = opponent + 1
        if (me == 4):
            me = 1
        me += 6
    return (opponent, me)

def run(file=None):
    if not file:
        data = readfile(input("choose input: "))
    else:
        data = readfile(file)
    my_total_score = 0
    for m in data:
        result = get_score(m)
        print(result)
        my_total_score += result[1]
    print(my_total_score)

#11725 is fout