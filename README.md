# Vicious Tomato Password Generator
The greatest password manager known to life, the universe, and everything.  
This generator produces 4 (default) words from a given language to be used as a password. 

The principle behind the algorithm of this password generator and why it is so secure is well described here: http://security.stackexchange.com/a/6096 

This repo includes a python script and a c program (comming later).  

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
