# Vicious Tomato Password Generator
The greatest password manager known to life, the universe, and everything.  
This generator produces 4 (default) words from a given language to be used as a password. 

The principle behind the algorithm of this password generator and why it is so secure is well described here: http://security.stackexchange.com/a/6096 

(Short summary of the above link)
This password generator creates secure passwords because they are:
1. Long (brute force persistent)

2. Easy to memorize (Can be saved inside your head)

3. Completly random (Prevents dictionary optimizations)

This repo includes a python script and a c program.  

### Install:
Download repo using git clone or simply use the big ol' "Download ZIP" button.  
See language specifics for their usage.  

### Python usage:
(This script requires python version >= 2.6)  
Arguments should be a list of languages. To get the list of  
supported languages, simply use the single argument "list".  
If one would like to specify number of words produced, use  
the flag "-n" followed by an integer.  
    
    ex: ./tomatopass.py swedish english -n 5 

### C usage:
(Currently only (official) support for Linux/UNIX systems)
The C-version of this program uses the same arguments as the python version

To build the program run the following command from the root folder of this repo:

    cd/c_implementation/src/ && make

(This requires gcc)

To run the program, simply execute:

    ./tomatopass <arguments>

Where "arguments" should be excanged to the argument you wish to run the program with.
