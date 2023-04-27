import time
import os


#this feature will be used for first time users/register account
print("\nWelcome to the MKDIR Creation\n\n")

#Define/Init Variables
currentDir = os.getcwd()            
parentDir = os.path.expanduser("~")
#macDir = "Documents/CS180_ProjectDB"
#winDir =  "Documents\CS180_ProjectDB"
directory= "Documents/CS180_ProjectDB"

#Process Inputs -->
#macPath = os.path.join(parentDir, macDir)
#winPath = os.path.join(parentDir, winDir)
path = os.path.join(parentDir, directory)

#Make the Path
#os.mkdir(macPath)
#os.mkdir(winPath)
os.mkdir(path)

#Display Outputs
print("\nCurrent Directory = %s" % currentDir)
print("\nParent Directory = %s" % parentDir)
#print("\nMac Path = %s" % macPath)
#print("\nWindows Path = %s" % winPath)
print("\nDirectory = %s" % path)