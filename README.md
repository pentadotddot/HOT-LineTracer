# HOT-LineTracer
Creates graphical representation of the development and homeostasis of a Hierarchical Tissue Organization (HOT).
Using simulations, lineage trees can be created, which trees can be drawn using javascripts p5.js library.
This way division and mutation lineages can be traced.

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


