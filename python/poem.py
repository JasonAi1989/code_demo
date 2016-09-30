#!/usr/bin/env python3

'write a poem'

import re

def translate(poem):
    ret = re.match(r'(!\s+)\s+(\s+)\s+(!\s+)', poem)
    print(ret.group(0))
    print(ret.group(1))
    print(ret.group(2))
    print(ret.group(3))





if __name__=='__main__':
    poem = "静夜思  李白   床前明月光，疑似地上霜。举头望明月，低头思故乡。"
    new_poem = translate(poem)
