# encoding: utf-8

import os, sys, re, json

def run(index, T, maxn, maxab, minp, maxp, maxx, maxst):
    print 'run', index

    input = ''
    output = ''
    if index < 0:
        input = '../down/%d.in' % (-index)
        output = '../down/%d.ans' % (-index)
    else:
        input = '../data/airport%d.in' % (index)
        output = '../data/airport%d.ans' % (index)
    
    args = []
    args.append('-T %d' % T)
    args.append('-maxn %d' % maxn)
    args.append('-maxab %d' % maxab)
    args.append('-minp %d' % minp)
    args.append('-maxp %d' % maxp)
    args.append('-maxx %d' % maxx)
    args.append('-maxst %d' % maxst)
    cmd = './val.exe ' + ' '.join(args) + (' < %s' % input)
    print cmd
    assert os.system(cmd) == 0

    assert os.system('cp %s airport.in' % input) == 0
    assert os.system('./std.exe') == 0
    assert os.system('diff airport.out %s' % output) == 0

if __name__ == '__main__':
    args = json.loads(open('../conf.json').read())['args']
    T = args["T"]
    maxn = args["n"]
    maxab = args["ab"]
    minp = args["p"][0]
    maxp = args["p"][1]
    maxx = args["x"]
    maxst = args["st"]

    run(-1, T, maxn, maxab, minp, maxp, maxx, maxst)

    for i in range(1, 21, 1):
        run(i, T, maxn, maxab, minp, maxp, maxx, maxst)