#!/usr/bin/env python
"""
Intense Tomato Password Generator 1.0
  This generator produces 4 (default) words from a given
  language to be used as a password.

  Usage:
    Arguments should be a list of languages. To get the list of
    supported languages, simply use the single argument "list".
    If one would like to specify number of words produced, use
    the flag "-n" followed by an integer.

    ex: ./tomatopass swedish english -n 5

Written by Fredrik Johansson
"""

from __future__ import print_function
import sys
from os import path
from os import listdir
from random import SystemRandom


readme = __doc__
num_of_words = 4
dictionaries_path = 'dictionaries'


def get_language(lang):
    with open(path.join(dictionaries_path, lang+'.dict'), 'r') as  f:
        words = f.readlines()
        f.close()
    return words

def print_error(error):
    print(error)
    print()
    print(readme)
    sys.exit()

def print_languages():
    print('Available languages:')
    for lang in listdir(dictionaries_path): 
        if lang.endswith('.dict'):
            print('  '+lang[:-len('.dict')])


if len(sys.argv) < 2:
    print(readme)

elif '-h' in sys.argv or '--help' in sys.argv or '-help' in sys.argv:
    print(readme)

elif 'list' in sys.argv:
    print_languages()

else:
    langs = []
    n_flag_set = False

    # go through the arguments:
    for arg in sys.argv[1:]:
        if arg == '-n':
            n_flag_set = True
        elif n_flag_set:
            try:
                num_of_words = int(arg)
                n_flag_set = False
            except:
                print_error('Error: argument after flag -n must be a number')

        elif path.isfile(path.join(dictionaries_path, arg+'.dict')):
            langs.append(arg)
        else:
            print_error('Error: Language was not found')

    # randomize password from word list:
    generator = SystemRandom()
    words = []
    for lang in langs:
        words.extend(get_language(lang))
    password = [words[generator.randint(0, len(words))][:-1]
                  for x in range(num_of_words)]
    # [:-1] to remove '\n' from words

    for word in password:
        print(word, end=' ')
    print()

