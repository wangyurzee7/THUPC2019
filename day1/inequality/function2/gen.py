from sys import stderr
import yaml
from random import randint
from os import system

def gen_data(conf):
    a = conf['args']['a']
    for subtask in conf['data']:
        n = subtask['args']['n']
        for case_id in subtask['cases']:
            stderr.write('generating case %d\n' % case_id)
            input_file = '../data/%d.in' % case_id
            output_file = '../data/%d.ans' % case_id
            with open(input_file, 'w') as f:
                f.write('%d\n' % n)
                f.write('%s\n' % ' '.join([str(randint(-a, a)) for _ in range(n)]))
                f.write('%s\n' % ' '.join([str(randint(-a, a)) for _ in range(n)]))

            system('./std < %s > %s' % (input_file, output_file))

def compile_std(conf):
    system('g++ %s std.cpp -o std' % conf['compile']['cpp'])

if __name__ == "__main__":
    with open('../conf.yaml', 'r') as conf:
        conf = yaml.load(conf)
        compile_std(conf)
        gen_data(conf)