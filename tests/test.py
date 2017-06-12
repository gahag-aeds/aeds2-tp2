#!/usr/bin/env python3

from os import remove

import tptester

tptester.tp_test(
  'bin/tp2',
  
  indexes = [ '30', '50k', '2500k', '2500k2' ],
  input_file = lambda ix: 'tests/data/in' + ix + '.txt',
  answer_file = lambda ix: 'tests/data/out' + ix + '.txt',
  
  args = lambda ix: [ 'tests/data/in' + ix + '.txt', 'tests/output.txt' ],
  stdin = lambda ix: None,
  output = lambda ix, stdout: open('tests/output.txt', 'rb')
)

remove('tests/output.txt')
