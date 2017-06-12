#!/usr/bin/env python3

import os

import tptester


tests_dir = os.path.dirname(os.path.realpath(__file__))

out_file = tests_dir + '/output.txt'

tptester.tp_test(
  tests_dir + '/../bin/tp2',
  
  indexes = [ '30', '50k', '2500k', '2500k2' ],
  input_file = lambda ix: tests_dir + '/data/in' + ix + '.txt',
  answer_file = lambda ix: tests_dir + '/data/out' + ix + '.txt',
  
  args = lambda ix: [ tests_dir + '/data/in' + ix + '.txt', out_file ],
  stdin = lambda ix: None,
  output = lambda ix, stdout: open(out_file, 'rb')
)

os.remove(out_file)
