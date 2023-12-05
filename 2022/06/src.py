"""Python version: 2.7.16"""

class Buff(list):
    def __init__(self, marker_len):
        super(list, self).__init__()
        self.marker_len = marker_len
    
    def feed(self, item):
        if not item:
            self.pop(0)
        else:
            if len(self) >= self.marker_len:
                self.pop(0)
            self.append(item)
        print(self)
    
    def check_dup(self, char):
        for i, c in enumerate(self):
            if c == char:
                for _ in range(0, i + 1):
                    self.feed(None)

def parse_file(name):
    with open(name, 'r') as f:
        return f.readlines()

def parse_stream(stream, marker_len):
    buff = Buff(marker_len)
    for i, c in enumerate(stream):
        if len(buff) == marker_len:
            print(buff)
            return (i)
        else:
            buff.check_dup(c)
            buff.feed(c)
    return (None)

def run(marker_len):
    data = parse_file(input("input: "))
    result = []
    for b in data:
        result.append(parse_stream(b, marker_len))
    print(result)
