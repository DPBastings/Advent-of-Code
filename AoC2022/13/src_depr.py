"""Written in Python 2.7.16."""

import ast

def _compare(a, b, depth=0):
    indent = "  ".join(("" for _ in range(0, depth+1)))
    if isinstance(a, int):
        if isinstance(b, int):
            if a < b:
                print indent, "  - Left side is smaller: inputs are in the right order."
                return True
            if a > b:
                print indent, "  - Left side is greater: inputs are in the wrong order."
                return False
            else: return None
        else:
            print indent, "- Mixed types: convert left."
            conv = []
            conv.append(a)
            a = conv
            compare(a, b, depth+1)
    elif isinstance(a, list):
        if isinstance(b, list):
            for i, x in enumerate(a):
                try:
                    y = b[i]
                except IndexError:
                    print indent, "- Right side ran out of items."
                    return False
                comparison = compare(x, y)
                if not comparison:
                    continue
                return comparison
        elif isinstance(b, int):
            print indent, "- Mixed types: convert right."
            conv = []
            conv.append(b)
            b = conv
            compare(a, b, depth+1)
        print indent, "- Left side ran out of items."
        return True
    raise TypeError

def compare(a, b, depth=0):
    indent = "  ".join(("" for _ in range(0, depth+1)))
    print indent, "- Comparing {0} against {1}.".format(a, b)
    try:
        for i, x in enumerate(a):
            try: y = b[i]
            except IndexError:
                print indent, "- Right side ran out of items. Inputs are in the wrong order."
                return False
            if isinstance(x, list) and isinstance(y, int):
                print indent, "  - Mixed types: convert right."
                y = [y]
            if isinstance(x, int) and isinstance(y, list):
                print indent, "  - Mixed types: convert left."
                x = [x]
            comparison = compare(x, y, depth+1)
            if comparison == -1:
                continue
            return comparison
        print indent, "- Left side ran out of items."
        return -1
    except TypeError:
        if a < b:
            print indent, "  - Left side is smaller.",
            return True
        elif a > b:
            print indent, "  - Left side is greater. Inputs are in the wrong order."
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
        print "== Pair {0} ==".format(n)
        if compare(*p):
            print "Inputs are in the right order."
            res.append(n)
    print res, sum(res)
