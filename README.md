# HOT-LineTracer
Creates graphical representation of the development and homeostasis of a Hierarchical Tissue Organization (HOT).
Using simulations, lineage trees can be created, which trees can be drawn using javascripts p5.js library. 
I also implemented the merging process (mathematical background by Imre Derényi), detailed below, which is a very powerful method to create many instances fast for different mutation distributions alongside cell lineage trees by varying the mutation rate on a priori generated tree topologies.


## Installation
Tested on ubuntu 18.

### Installing node package manager:
`sudo apt install nodejs`
### If necessary, install `npm` the following way:
```
sudo apt install libssl1.0-dev
sudo apt install nodejs-dev
sudo apt install node-gyp
sudo apt install npm
```
### Install p5.js
`npm i --s node-p5`

## Usage

Simply run `bash javaShell.sh` from a terminal.

Inside `javaShell.sh`, you can set different parameters,
most importantly the amplification factor value ("gamma_manual" in the code).

For more detail about the theoretical background:
 
https://www.nature.com/articles/ncomms14545

https://www.nature.com/articles/s41467-022-29004-1

With `HOT_LinTrace.py`, using previously generated cell lineage trees,
I implemented the merging process detailed here: 
https://www.biorxiv.org/content/10.1101/2020.07.13.201004v1.

Using this merging method mutations can be "placed" on the tree with different mutations rates implied.

The powerful thing about this approach, is that you only need to generate a tree topology once,
which can be a very time sensitive process, then by varying the mutation rate one can create different instances for mutation accumulation, which changes the distribution of mutations alongside the tree.

This merging process can be many orders of magnitude faster than re-simulating the whole tree, especially when `N` is large (see in theoretical papers).

## Some background info
Horizontal lines represent hierarchical levels.
Green lines correspond to asymmetric division,
red lines correspond to symmetric differentiation,
blue lines correspond to symmetric division.

Circles represent cells at time "t", smaller circles around cells represent mutations.

As the tree develops in time, one can see the lineages forming,
if you hover your mouse over a cell, it also highlights its ancestor.

https://imgur.com/a/bGMVpX1
