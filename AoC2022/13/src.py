"""Written in Python 3.9.2."""

import ast
from itertools import zip_longest

def compare(a, b, depth=0):
    indent = "  ".join(("" for _ in range(0, depth+1)))
    print(indent, f"- Comparing {a} against {b}.")
    if isinstance(a, int) and isinstance(b, int):
        if a < b:
            print(indent, "  - Left side is smaller.")
            return 1
        if a > b:
            print(indent, "  - Left side is greater. Inputs are in the wrong order.")
            return -1
        else: return 0
    for left, right in zip_longest(a, b):
        if left == None:
            print(indent, "- Left side ran out of items.")
            return 0
        if right == None:
            print(indent, "- Right side ran out of items. Inputs are in the wrong order.")
            return -1
        if isinstance(left, list) and isinstance(right, int):
            print(indent, "  - Mixed types: convert right.")
            right = [right]
        if isinstance(right, list) and isinstance(left, int):
            print(indent, "  - Mixed types: convert left.")
            left = [left]
        result = compare(left, right, depth=depth+1)
        if result == 0:
            continue
        return result
    return 0

def _compare(a, b, depth=0):
    indent = "  ".join(("" for _ in range(0, depth+1)))
    print(indent, f"- Comparing {a} against {b}.")
    try:
        for i, x in enumerate(a):
            try: y = b[i]
            except IndexError:
                print(indent, "- Right side ran out of items. Inputs are in the wrong order.")
                return False
            if isinstance(x, list) and isinstance(y, int):
                print(indent, "  - Mixed types: convert right.")
                y = [y]
            if isinstance(x, int) and isinstance(y, list):
                print(indent, "  - Mixed types: convert left.")
                x = [x]
            comparison = compare(x, y, depth+1)
            if comparison == -1:
                continue
            return comparison
        print(indent, "- Left side ran out of items.")
        return -1
    except TypeError:
        if a < b:
            print(indent, "  - Left side is smaller.", end="")
            return True
        elif a > b:
            print(indent, "  - Left side is greater. Inputs are in the wrong order.")
            return False
        else:
            return -1

def parse(data):
    packets = []
    for line in data:
        try:
            packets.append(ast.literal_eval(line))
        except SyntaxError:
            pass
    return ((packets[i], packets[i+1]) for i in range(0, len(packets), 2))
   
def run():
    res = []
    with open(input("input: "), 'r') as f:
        pairs = parse(f.readlines())
    for n, p in enumerate(pairs, 1):
        print(f"== Pair {n} ==")
        result = compare(*p)
        if result > -1:
            print("Inputs are in the right order.")
            res.append(n)
    print(res, sum(res))