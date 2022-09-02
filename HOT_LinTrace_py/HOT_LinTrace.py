# /usr/bin/python

import os, shutil, math, sys
import numpy as np
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
mut = int(sys.argv[4])
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
		
N =  1024
hier =  3
n = hier
g =  5.0


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


# Here I draw mutations for all events which happened in the cell lineage tree.



foutMut = open("mutmeres"+str(mut)+".txt","w+")

#mutrate =  0.000005*math.log((mut+1)*2)**mut

#mutrate = 5e-6*math.log(10*(mut+1))**mut

mutrate = 0.1

MaxMut =  15

fout = open("mutData"+str(treegamma)+".txt","w+")

StoreMutationsArray = [0]*MaxMut

DividedArray = [0]*(int(LinArray[-1][0].gen)+1) # set array to store cell genID-s which already divided
DividedArrayMutNum = [0]*(int(LinArray[-1][0].gen)+1)
StoreMutationsFlagArray = [0]*(MaxMut)

maxLen =  len(max(LinArray, key=len))

LinArrayMutNum = [[0]*(maxLen+1)]*len(LinArray) # store mutations

for instancia in range(int(instanciak)):
	DividedArray.clear()
	DividedArray = [0]*(int(LinArray[-1][0].gen)+1) # store cell genID-s which already divided
	DividedArrayMutNum.clear()
	DividedArrayMutNum = [0]*(int(LinArray[-1][0].gen)+1)

	LinArrayMutNum.clear()	
	LinArrayMutNum = [[0]*(maxLen+1)]*len(LinArray) # store mutations
	'''
	for a in range(len(LinArray)): # set mutation numbers to 0
		for b in reversed(range(len(LinArray[a]))):			
			LinArray[a][b].mutNum = 0
	'''
	StoreMutationsFlagArray.clear()
	StoreMutationsFlagArray = [0]*(MaxMut) # initialize vector to store mutation flags

	print (instancia)

	stemCellCounter = 0
	for i in range(len(LinArray)):
		
		for k in reversed(range(stemCellCounter,len(LinArray[i]))):

			if (i==0 and k==(len(LinArray[0])-1)): # start with first stem cell event
				if LinArrayMutNum[i][k] < MaxMut:
					randnumMut = np.random.poisson(mutrate)
					if randnumMut+LinArrayMutNum[i][k] <= MaxMut: 
						LinArrayMutNum[i][k] += randnumMut

				if LinArrayMutNum[i][k] > 0 and StoreMutationsFlagArray[int(LinArrayMutNum[i][k])]==0:
					StoreMutationsArray[LinArrayMutNum[i][k]]+=1.0
					StoreMutationsFlagArray[LinArrayMutNum[i][k]] = 1

				DividedArray[LinArray[i][k].gen]=1
				DividedArrayMutNum[LinArray[i][k].gen]=LinArrayMutNum[i][k]
				fout.write(str(LinArray[i][k].gen)+'\t'+str(LinArrayMutNum[i][k])+"\n")

			
			if DividedArray[LinArray[i][k].gen] == 1:
					LinArrayMutNum[i][k]=DividedArrayMutNum[LinArray[i][k].gen]

			if k<len(LinArray[i])-1: # inherit mutations from ancestor
				
				if DividedArray[LinArray[i][k].gen]==0: 
					LinArrayMutNum[i][k] = LinArrayMutNum[i][k+1]
				
			flagDiv = 0
			# check if event already happened
			if LinArray[i][k].level == 0:
				stemCellCounter+=1

			if DividedArray[LinArray[i][k].gen]==1:
				flagDiv = 1

			if flagDiv == 0 and int(LinArray[i][k].level)<int(n):	# if new event -> mutation can happen with cells at level k<n	
				if LinArrayMutNum[i][k] < MaxMut:
					randnumMut = np.random.poisson(mutrate)
					if randnumMut+LinArrayMutNum[i][k] < MaxMut: 
						LinArrayMutNum[i][k] += randnumMut

				if LinArrayMutNum[i][k] > 0 and StoreMutationsFlagArray[int(LinArrayMutNum[i][k])]==0:
					StoreMutationsArray[LinArrayMutNum[i][k]]+=1.0
					StoreMutationsFlagArray[LinArrayMutNum[i][k]] = 1

		
				DividedArray[LinArray[i][k].gen]=1
				DividedArrayMutNum[LinArray[i][k].gen]=LinArrayMutNum[i][k]
				fout.write(str(LinArray[i][k].gen)+'\t'+str(LinArrayMutNum[i][k])+"\n")

	
for b in range(1,MaxMut):
	foutMut.write(str(mutrate)+'\t'+str(StoreMutationsArray[b]/float(instanciak))+'\n')
foutMut.write('\n')

foutMut.close()

print("_____________________")
for b in range(1,MaxMut):
	print(b,StoreMutationsArray[b]/float(instanciak))

Pmuem = [0]*MaxMut

print("_____________________")

for m in range(1,MaxMut):
	for i in range(len(LinArray)):
		if int(LinArray[i][0].level)==n:
			Pmuem[m] += (2*mutrate**m/math.gamma(m))*(len(LinArray[i])-1.5)**(m-1)
	print(Pmuem[m])

print("N: ", len(LeafArray),len(LinArray))

Dn = [0]*len(LinArray)

for i in range(len(LinArray)):
	Dn[i] = len(LinArray[i])
	#print(Dn[i]) 
print("DLongest: ", max(Dn)," Dn: ", Dn[-1])
		
'''
RepostArray = []
for i in range(len(LeafArray)):
	for k in reversed(range(len(LinArray[i]))):

		if i==0 and k==0:
			fout.write(str(LinArray[i][k].gen)+'\t'+str(LinArrayMutNum[i][k])+"\n")
			RepostArray.append(LinArray[i][k].gen)

		flagRepost = 0
		for l in range(len(RepostArray)):
			flagRepost = 0
			if LinArray[i][k].gen == RepostArray[l]:
				flagRepost = 1
				break
		if flagRepost == 0:
			fout.write(str(LinArray[i][k].gen)+'\t'+str(LinArrayMutNum[i][k])+"\n")
			RepostArray.append(LinArray[i][k].gen)
'''
fout.close()