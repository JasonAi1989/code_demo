#!/usr/bin/env python3

'write a poem'

def is_not_empty(s):
    if s == '':
        return False
    else:
        return True


def translate(poem):
    ret = poem.split()
    t_a = ret[0] + ' ' + ret[1]  #title and auth
    content = ret[2]

    new_poem = list()
    new_poem.append(t_a)

    temp1 = list(filter(is_not_empty, content.split('。')))
    for i in temp1:
        temp2 = list(filter(is_not_empty, (i+'。').split('，')))
        for j in temp2:
            if j.find('。') == -1:
                new_poem.append(j+'，')
            else:
                new_poem.append(j)

    l=0
    for i in new_poem:
        if l<len(i):
            l=len(i)

    new_poem2=list()
    new_poem.reverse()
    for i in range(0,l):
        line = list()
        for j in new_poem:
            l2=len(j)
            if i>=l2:
                line.append('  |')
            elif j[i] == ' ':
                line.append(j[i] + ' |')
            else:
                line.append(j[i] + '|')

        new_poem2.append(''.join(line)+'\n')

    return ''.join(new_poem2)

if __name__=='__main__':
    poem = "静夜思  李白   床前明月光，疑似地上霜。举头望明月，低头思故乡。"
    poem2 = "念奴娇 黄庭坚 断虹霁雨，净秋空，山染修眉新绿。桂影扶疏，谁便道，今夕清辉不足。万里青天，姮娥何处，驾此一轮玉。寒光零乱，为谁偏照醽醁。年少从我追游，晚凉幽径，绕张园森木。共倒金荷，家万里，难得尊前相属。老子平生，江南江北，最爱临风笛。孙郎微笑，坐来声喷霜竹。"
    new_poem = translate(poem)
    print(new_poem)

