#!/usr/bin/python
import os
import sys
textToSearch = ""
youtube = "https://www.youtube.com/results?search_query="
for cuvant in sys.argv[1:]:
	textToSearch+=cuvant+ " "
	
youtube += textToSearch
execute = "xdg-open" + " '"+youtube+"'"
print "Searching on youtube ", textToSearch
os.system(execute)