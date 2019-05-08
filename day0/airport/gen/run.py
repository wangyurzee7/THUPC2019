# encoding utf-8

import os, sys, re

extra = True

def run(index, T, maxn, maxab, maxx, maxst, seed):
    print 'run', index

    input = ''
    output = ''

    if index < 0:
        input = '../down/airport%d.in' % (-index)
        output = '../down/airport%d.ans' % (-index)
    else:
        input = '../data/airport%d.in' % (index)
        output = '../data/airport%d.ans' % (index)
    
    args = []
    args.append('-T %d' % T)
    args.append('-maxn %d' % maxn)
    args.append('-maxab %d' % maxab)
    args.append('-maxx %d' % maxx)
    args.append('-maxst %d' % maxst)
    cmd = './random.exe ' + ' '.join(args) + (' --seed %s' % seed) + ' > airport.in'
    print cmd
    assert os.system(cmd) == 0

    if extra:
        assert os.system('../cy/std.exe --extra_info') == 0
    else:
        assert os.system('../cy/std.exe') == 0
    print '========================'
    
    assert os.system('cp airport.in %s' % input) == 0
    assert os.system('cp airport.out %s' % output) == 0

if __name__ == '__main__':
    T = 8
    MAXN = 200
    MAXAB = 30

    extra = len(sys.argv) == 1

    run(1, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = '12edw2d312')
    run(2, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = '89u898u9')

    run(3, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = '3r12f2')
    run(4, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = 'c342f3cd23f23')
    run(5, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = 'f23cwf43g3')
    run(6, T = T, maxn = 50, maxab = 10, maxx = 50, maxst = 100, seed = 'fg432f32f23f')

    run(7, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'f32c2d32')
    run(8, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'df23c23f23')
    run(9, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'f23c2d32')
    run(10, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'v45g45v34')
    run(11, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'g34v3f43')
    run(12, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = '43rt32cf43fg')
    run(13, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = '43gvcv324f3')
    run(14, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'f324v3f43')
    run(15, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = '43tg3v34')
    run(16, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'bv54bv4bg564')
    run(17, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'g543gb455g43')
    run(18, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = '453g534g45t')
    run(19, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = '43g43g34tg')
    run(20, T = T, maxn = MAXN, maxab = MAXAB, maxx = 100000, maxst = 1000000000, seed = 'g34g453y54g54334')
