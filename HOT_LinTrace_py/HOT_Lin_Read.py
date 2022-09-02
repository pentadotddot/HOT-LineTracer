# /usr/bin/python

import os, shutil, math, sys
import scipy.special
import scipy.integrate as integrate
import scipy.special as special
import time
from sys import *

Data = [] # raw input data
LeafArray = [] # list of leaves
StemDivArray = [] # store stem cell division numbers
EventVertices = [] # store mother-child vertices
LinArray = [] # store lineage cell data

filename = str(sys.argv[1])
treegamma = sys.argv[2]
instanciak = sys.argv[3]

# read txt into 2D array
#filename = "TreeL.txt"
with open(filename, 'r') as f:
	for line in f.readlines():
		line = line.strip()
		Data.append(line.split('\t'))

#create class for events for inheritance
class Events:

	# Initializer / Instance Attributes
	def __init__(self, level, cellNum, Type, time, timeStep, ID, gen, mutNum, childID):
		self.level = level
		self.cellNum = cellNum
		self.Type = Type
		self.time = time
		self.timeStep = timeStep
		self.ID = ID
		self.gen = gen
		self.mutNum = mutNum
		self.childID = childID

# Events properties stored in class objects
		
N =  1e5
hier =  5
n = hier
g = 5.0

idCounter = 1
stemCellArray = []

# Here events are paired together as ancestral relationships, stored in EventVertices array, via childID
# as the daughters childID is the mothers genID or childID is equal to idCounter
# cells inherit ID-s as one of the daughters get a barcode, which always increase with any division,
# and the other daughter gets the same id as the mother had. 

# Here I also create the LeafArray, which stores all leaf nodes of the cell lineage tree

for k in range(len(Data)):

	print(k)
	#scd
	if int(Data[k][0]) == n:
		LeafArray.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,len(EventVertices)))

	if int(Data[k][0]) == 0:
			stemCellArray.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,len(EventVertices)))  

	if (int(Data[k][2])==0 and int(Data[k][0])<n):

		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==int(Data[k][5]) and int(Data[m][0])==int(Data[k][0])):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==idCounter and int(Data[m][0])==int(Data[k][0])):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		if(int(Data[k][0])<n):
			idCounter+=1


	#scdd
	elif (int(Data[k][2])==1 and int(Data[k][0])<n):

		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==int(Data[k][5]) and int(Data[m][0])==int(Data[k][0])+1):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==idCounter and int(Data[m][0])==int(Data[k][0])+1):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		if(int(Data[k][0])<n):
			idCounter+=1


	#acd
	elif (int(Data[k][2])==2 and int(Data[k][0])<n):
		
		
		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==int(Data[k][5]) and int(Data[m][0])==int(Data[k][0])):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		for m in range(k+1,len(Data)):
			if(int(Data[m][5])==idCounter and int(Data[m][0])==int(Data[k][0])+1):
				EventVertices.append(Events(Data[k][0],Data[k][1],Data[k][2],Data[k][3],Data[k][4],Data[k][5],k,0,m))
				
				break

		if(int(Data[k][0])<n):
			idCounter+=1


# Here I go through all Leaf nodes and I search for corresponding ancestors until I reach the first stem cell
# thus I create a 2D array, LinArray, where I store all the lineages of the cell lineage tree by ancestral relationship via ID-s.

a = []
b = []
foutLin = open("LinArray_"+str(N)+"_"+str(n)+"_"+str(g)+".txt","w+")

for i in range(len(LeafArray)):
	print(i)
	lincounter = 0
	LinArrayin = []
	LinArrayin.append(LeafArray[i])
	for j in reversed(range(LeafArray[i].childID)):

		if int(EventVertices[j].level) == 0 and EventVertices[j].gen>0:
				for k in range(len(stemCellArray)):
					if stemCellArray[k].gen == EventVertices[j].gen:
						a = stemCellArray[:k]
						a.reverse()
						break
				
				LinArray.append(LinArrayin.copy() + a )
				break
		

		if EventVertices[j].childID==LinArrayin[lincounter].gen:
			lincounter+=1
			LinArrayin.append(EventVertices[j])

		if LinArrayin[lincounter].gen == 0:
			#print(lincounter)
			LinArray.append(LinArrayin.copy())
			LinArrayin.clear()
			break


for i in range(len(LinArray)):
	for j in range(len(LinArray[i])):
		print(i,j)
		print(int(LinArray[i][j]))
		foutLin.write(str(int(LinArray[i][j]))+'\t')
	foutLin.write('\n')

foutLin.close()

