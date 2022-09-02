
var lineLenght = 15000;

var data = []


function readFile1(file) {
  var f = new XMLHttpRequest();
  f.open("GET", file, false);
  f.onreadystatechange = function() {
    if (f.readyState === 4) {
      if (f.status === 200 || f.status === 0) {
        var res = f.responseText;
        res = res.trim();
        data = res.split(/\r?\n/);
        alert(res); //to see if contents are read
      }
    }
  }
  f.send(null);
}

readFile1('TreeS.txt');

var j = 0;
var dataM = new Array(data.length);
for (var i = 0; i < data.length; i++) {
  dataM[i] = new Array(6);
}

var d;

for (var i = 0; i < data.length; i++) {
  d = data[i].split(/\s+/);
  for (var j = 0; j < 6; j++) {
    dataM[i][j] = d[j];
  }
}

var data2 = []

function readFile2(file) {
  var f = new XMLHttpRequest();
  f.open("GET", file, false);
  f.onreadystatechange = function() {
    if (f.readyState === 4) {
      if (f.status === 200 || f.status === 0) {
        var res = f.responseText;
        res = res.trim();
        data2 = res.split(/\r?\n/);
        alert(res); //to see if contents are read
      }
    }
  }
  f.send(null);
}

readFile2('TreeL.txt');


var j = 0;
var dataM2 = new Array(data2.length);
for (var i = 0; i < data2.length; i++) {
  dataM2[i] = new Array(6);
}


for (var i = 0; i < data2.length; i++) {
  d = data2[i].split(/\s+/);
  for (var j = 0; j < 6; j++) {
    dataM2[i][j] = d[j];
  }
}

var linkage1 = new Array(2*data.length);
for (var i = 0; i < 2*data.length; i++) {
  linkage1[i] = new Array(4);
}

for (var i = 0; i < 2*data.length; i++) {
  for (var j = 0; j < 4; j++) {
    linkage1[i][j] = 0;
  }
}

var linkage2 = new Array(2*data2.length);
for (var i = 0; i < 2*data2.length; i++) {
  linkage2[i] = new Array(4);
}

for (var i = 0; i < 2*data2.length; i++) {
  for (var j = 0; j < 4; j++) {
    linkage2[i][j] = 0;
  }
}


var mutDataL = []


function readFile3(file) {
  var f = new XMLHttpRequest();
  f.open("GET", file, false);
  f.onreadystatechange = function() {
    if (f.readyState === 4) {
      if (f.status === 200 || f.status === 0) {
        var res = f.responseText;
        res = res.trim();
        mutDataL = res.split(/\r?\n/);
        alert(res); //to see if contents are read
      }
    }
  }
  f.send(null);
}

readFile3('mutDataL.txt');

var mutDataS = []
function readFile4(file) {
  var f = new XMLHttpRequest();
  f.open("GET", file, false);
  f.onreadystatechange = function() {
    if (f.readyState === 4) {
      if (f.status === 200 || f.status === 0) {
        var res = f.responseText;
        res = res.trim();
        mutDataS = res.split(/\r?\n/);
        alert(res); //to see if contents are read
      }
    }
  }
  f.send(null);
}


readFile4('mutDataS.txt');

var j = 0;
var dataMutL = new Array(mutDataL.length);
for (var i = 0; i < mutDataL.length; i++) {
  dataMutL[i] = new Array(6);
}


for (var i = 0; i < mutDataL.length; i++) {
  d = mutDataL[i].split(/\s+/);
  for (var j = 0; j < 2; j++) {
    dataMutL[i][j] = d[j];
  }
}

var j = 0;
var dataMutS = new Array(mutDataS.length);
for (var i = 0; i < mutDataS.length; i++) {
  dataMutS[i] = new Array(6);
}


for (var i = 0; i < mutDataS.length; i++) {
  d = mutDataS[i].split(/\s+/);
  for (var j = 0; j < 2; j++) {
    dataMutS[i][j] = d[j];
  }
}

var font,
  fontsize = 20

function preload() {
  // Ensure the .ttf or .otf font stored in the assets directory
  // is loaded before setup() and draw() are called
  font = loadFont('LemonMilklight.otf');
}

var Start = 0;
var Stop = data.length;
var Stop2 = data2.length;
var timedelay =10;
var level =200;
var nStep = 2*level;
var n =  3;
var canvasSize = 2*(n+1)*nStep;
var N =  1024;


function setup() {
  createCanvas(lineLenght, canvasSize);
  fill(10, 10, 10);
  textFont(font);
  textSize(fontsize);
  stroke("black");
  textAlign(CENTER, CENTER);

}

function scdd(x, y, diax, diay) {
  fill(255, 0, 0)
  ellipse(x, y, diax, diay)
}


function acd(x, y, diax, diay) {

  fill(0, 255, 0)
  ellipse(x, y, diax, diay)
}


function scd(x, y, diax, diay) {

  fill(0, 0, color);
  ellipse(x, y, diax, diay)
}


var cell = {
  x: 0,
  y: canvasSize-2*nStep,
  dia: 20
};


var cell2 = {
  x: 0,
  y: (canvasSize/2.0)-2*nStep,
  dia: 20
};

function draw() {
  
background(255);
  
 // division event line drawing
 

  var al;
  var idCounter = 1;
  for (var k = 0; k < Stop; k++) { 
    al = 1.0; 
    if (Number(dataM[k][2]) === 0) {  //scd
      strokeWeight(1);  
      stroke(0);
      scd(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level , cell.dia, cell.dia);
      fill(10, 10, 10);
      text(dataM[k][5].toString(), cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level);
      
      Nmut = 0;
      for(a=0;a<dataMutS.length;a++){

        if(k==dataMutS[a][0]){
          Nmut = dataMutS[a][1];
        }

      }
      var color = 10;
      for(var i = 0; i<Nmut; i++){
         
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell.x - dataM[Start][3] * timedelay + timedelay * dataM[k][3]+(cell.dia+1)*cos(-i*PI/Nmut),cell.y - dataM[k][0] * level+(cell.dia+1)*sin(-i*PI/Nmut),cell.dia/3.0,cell.dia/3.0);  
        strokeWeight(1);      

      }


      for (var m = k+1; m < Stop; m++) {
        if ((Number(dataM[m][5]) === Number(dataM[k][5])) && (Number(dataM[m][0]) === Number(dataM[k][0]))) {
          stroke('rgba(0,0,255,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level-3 , cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level-3);
          linkage1[2*k][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][3] = cell.y - dataM[m][0] * level;
          break;
        }
      }
      
      for (var m = k+1; m < Stop; m++) {
        if ((Number(dataM[m][5]) === idCounter) && (Number(dataM[m][0]) === Number(dataM[k][0]))) {
          stroke('rgba(0,0,255,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level -7, cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level -7);
          linkage1[2*k+1][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k+1][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][3] = cell.y - dataM[m][0] * level;
          
          break;
        }
      }
      if(Number(dataM[k][0])<n){
        idCounter++;  
      }
      
    }

    else if (Number(dataM[k][2]) === 1) { // scdd
      strokeWeight(1);
      stroke(0);  
      scdd(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level , cell.dia, cell.dia);
      fill(10, 10, 10);
      text(dataM[k][5].toString(), cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level);

      Nmut = 0;
      for(a=0;a<dataMutS.length;a++){

        if(k==dataMutS[a][0]){
          Nmut = dataMutS[a][1];
        }

      }
      var color = 100;
      for(var i = 0; i<Nmut; i++){
         
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell.x - dataM[Start][3] * timedelay + timedelay * dataM[k][3]+(cell.dia+1)*cos(-i*PI/Nmut),cell.y - dataM[k][0] * level+(cell.dia+1)*sin(-i*PI/Nmut),cell.dia/3.0,cell.dia/3.0);    
        strokeWeight(1);      

      }


      for ( var m = k+1; m < Stop; m++) {

        if ((Number(dataM[m][5]) === Number(dataM[k][5])) && (Number(dataM[m][0]) === Number(dataM[k][0])+1)) {

          stroke('rgba(255,0,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level, cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level );
          linkage1[2*k][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][3] = cell.y - dataM[m][0] * level;
          break;
        }
      }

      for ( var m = k+1; m < Stop; m++) {
        if ((Number(dataM[m][5]) === idCounter)  && (Number(dataM[m][0]) === Number(dataM[k][0])+1)) {

          stroke('rgba(255,0,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level , cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level );
          linkage1[2*k+1][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k+1][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][3] = cell.y - dataM[m][0] * level;
          
           break;
        }

      }

      if(dataM[k][0]<Number(n)){
          idCounter++;  
        }
      } 

    else if (Number(dataM[k][2]) === 2) {
      strokeWeight(1);
      stroke(0); 
    	acd(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level , cell.dia, cell.dia);
      fill(10, 10, 10);
      text(dataM[k][5].toString(), cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level);

      Nmut = 0;
      for(a=0;a<dataMutS.length;a++){

        if(k==dataMutS[a][0]){
          Nmut = dataMutS[a][1];
        }

      }
      var color = 200;
      for(var i = 0; i<Nmut; i++){
         
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell.x - dataM[Start][3] * timedelay + timedelay * dataM[k][3]+(cell.dia+1)*cos(-i*PI/Nmut),cell.y - dataM[k][0] * level+(cell.dia+1)*sin(-i*PI/Nmut),cell.dia/3.0,cell.dia/3.0);    
        strokeWeight(1);      

      }

      for (var m = k+1; m < Stop; m++) {
        
        if ((Number(dataM[m][5]) === Number(dataM[k][5])) && (Number(dataM[m][0]) === Number(dataM[k][0]))) {
          stroke('rgba(0,255,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level, cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level);
          linkage1[2*k][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k][3] = cell.y - dataM[m][0] * level;
          break;
        }

      }
      
      for (var m = k+1; m < Stop; m++) {
        
        if ((Number(dataM[m][5]) ===idCounter) && (Number(dataM[m][0]) === Number(dataM[k][0])+1)) {
          stroke('rgba(0,255,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay, cell.y - dataM[k][0] * level, cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay, cell.y - dataM[m][0] * level);
          linkage1[2*k+1][0] = cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][1] = cell.y - dataM[k][0] * level;
          linkage1[2*k+1][2] = cell.x + timedelay * dataM[m][3] - dataM[Start][3] * timedelay;
          linkage1[2*k+1][3] = cell.y - dataM[m][0] * level;
         
          break;
        }
        
      }
      if(Number(dataM[k][0])<n){
          idCounter++;  
        }        
    }

  } // drawing data2

  idCounter = 1;
  for (var k = 0; k < Stop2; k++) { //scd
    al = 1.0; 
    if (Number(dataM2[k][2]) === 0) {
      strokeWeight(1);
      stroke(0);
      scd(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.dia, cell2.dia);
      fill(10, 10, 10);
      text(dataM2[k][5].toString(), cell2.x - dataM2[Start][3] * timedelay + timedelay * dataM2[k][3], cell2.y - dataM2[k][0] * level );
      
      Nmut = 0;
      for(a=0;a<dataMutL.length;a++){

        if(k==dataMutL[a][0]){
          Nmut = dataMutL[a][1];
        }

      }
      var color = 10;
      for(var i = 0; i<Nmut; i++){
         
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell2.x - dataM2[Start][3] * timedelay + timedelay * dataM2[k][3]+(cell2.dia+1)*cos(-i*PI/Nmut),cell2.y - dataM2[k][0] * level+(cell2.dia+1)*sin(-i*PI/Nmut),cell2.dia/3.0,cell2.dia/3.0);  
        strokeWeight(1);      

      }

      for (var m = k+1; m < Stop2; m++) {

        if ((Number(dataM2[m][5]) === Number(dataM2[k][5])) && (Number(dataM2[m][0]) === Number(dataM2[k][0]))) {
          
          stroke('rgba(0,0,255,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level-3 , cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level-3 );
          linkage2[2*k][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][3] = cell2.y - dataM2[m][0] * level;
          break;
        }
      }
      
      for (var m = k+1; m < Stop2; m++) {

        if ((Number(dataM2[m][5]) === idCounter) && (Number(dataM2[m][0]) === Number(dataM2[k][0]))) {

          stroke('rgba(0,0,255,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level -7, cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level -7);
          linkage2[2*k+1][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k+1][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][3] = cell2.y - dataM2[m][0] * level;
          
          break;
        }

      }
      if(Number(dataM2[k][0])<n){
          idCounter++;  
        }


    }

    else if (Number(dataM2[k][2]) === 1) {
    
      strokeWeight(1);
      stroke(0);
      scdd(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level, cell2.dia, cell2.dia);
      fill(10, 10, 10);
      text(dataM2[k][5].toString(), cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level);

      Nmut = 0;
      for(a=0;a<dataMutL.length;a++){

        if(k==dataMutL[a][0]){
          Nmut = dataMutL[a][1];
        }

      }

      var color = 100;

      for(var i = 0; i<Nmut; i++){
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell2.x - dataM2[Start][3] * timedelay + timedelay * dataM2[k][3]+(cell2.dia+1)*cos(-i*PI/Nmut),cell2.y - dataM2[k][0] * level+(cell2.dia+1)*sin(-i*PI/Nmut),cell2.dia/3.0,cell2.dia/3.0);  
        strokeWeight(1);      

      }

      for ( var m = k+1; m < Stop2; m++) {

        if ((Number(dataM2[m][5]) === Number(dataM2[k][5])) && (Number(dataM2[m][0]) === Number(dataM2[k][0])+1)) {

          stroke('rgba(255,0,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level );
          linkage2[2*k][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][3] = cell2.y - dataM2[m][0] * level;
          break;
        }
      }

      for ( var m = k+1; m < Stop2; m++) {
        if ((Number(dataM2[m][5]) === idCounter)  && (Number(dataM2[m][0]) === Number(dataM2[k][0])+1)) {

          stroke('rgba(255,0,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level );
          linkage2[2*k+1][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k+1][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][3] = cell2.y - dataM2[m][0] * level;
          
          break;
        }

      }
      if(dataM2[k][0]<Number(n)){
          idCounter++;  
      }


      } 

    else if (Number(dataM2[k][2]) === 2) {
      strokeWeight(1);
      stroke(0);
      acd(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.dia, cell2.dia);
      fill(10, 10, 10);
      text(dataM2[k][5].toString(), cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level);

      Nmut = 0;
      for(a=0;a<dataMutL.length;a++){

        if(k==dataMutL[a][0]){
          Nmut = dataMutL[a][1];
        }

      }

      var color = 200;

      for(var i = 0; i<Nmut; i++){
        fill(color, 255*k/(2*N+1), color-10*k);
        ellipse(cell2.x - dataM2[Start][3] * timedelay + timedelay * dataM2[k][3]+(cell2.dia+1)*cos(-i*PI/Nmut),cell2.y - dataM2[k][0] * level+(cell2.dia+1)*sin(-i*PI/Nmut),cell2.dia/3.0,cell2.dia/3.0);  
        strokeWeight(1);      

      }

      for (var m = k+1; m < Stop2; m++) {
        
        if ((Number(dataM2[m][5]) === Number(dataM2[k][5])) && (Number(dataM2[m][0]) === Number(dataM2[k][0]))) {
          stroke('rgba(0,255,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level);
          linkage2[2*k][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k][3] = cell2.y - dataM2[m][0] * level;
          break;
        }

      }
      
      for (var m = k+1; m < Stop2; m++) {
        
        if ((Number(dataM2[m][5]) ===idCounter) && (Number(dataM2[m][0]) === Number(dataM2[k][0])+1)) {
          stroke('rgba(0,255,0,'+al.toString()+')');
          strokeWeight(3);
          line(cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[k][0] * level , cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay, cell2.y - dataM2[m][0] * level );
          linkage2[2*k+1][0] = cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][1] = cell2.y - dataM2[k][0] * level;
          linkage2[2*k+1][2] = cell2.x + timedelay * dataM2[m][3] - dataM2[Start][3] * timedelay;
          linkage2[2*k+1][3] = cell2.y - dataM2[m][0] * level;
          
          break;
        }
        
      }
      if(Number(dataM2[k][0])<n){
          idCounter++;  
        }

             
    }

  } // drawing data2 


//drawing hierarchical levels and cells and stuff


  for(var k=0;k<2*Stop;k++){
    if (mouseX>linkage1[k][2]-cell.dia/2.0 && mouseX < linkage1[k][2]+cell.dia/2.0 && mouseY>linkage1[k][3]-cell.dia/2.0 && mouseY < linkage1[k][3]+cell.dia/2.0){
      fill(255);
      stroke(0)
      strokeWeight(4);
      cursor(HAND);
      
    }
    else{
      fill('rgba(255,100,200,0)')
      cursor(ARROW);
    }
    ellipse(linkage1[k][2],linkage1[k][3],cell.dia,cell.dia);
    ellipse(linkage1[k][0],linkage1[k][1],cell.dia,cell.dia);
    strokeWeight(1);

  }

  
  for(var k=0;k<2*Stop2;k++){
    if (mouseX>linkage2[k][2]-cell.dia/2.0 && mouseX < linkage2[k][2]+cell2.dia/2.0 && mouseY>linkage2[k][3]-cell.dia/2.0 && mouseY < linkage2[k][3]+cell2.dia/2.0){
      
      fill(255);
      stroke(0)
      strokeWeight(4);
      cursor(HAND);

    }

    else{

      fill('rgba(255,0,0,0)')
      cursor(ARROW);
    }
    

  
   
    ellipse(linkage2[k][2],linkage2[k][3],cell2.dia,cell2.dia);
    ellipse(linkage2[k][0],linkage2[k][1],cell2.dia,cell2.dia);

    strokeWeight(1);
    
  }

  for(var k=0;k<2*Stop2;k++){
    try{
      if (mouseX>cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay-cell.dia/2.0 && mouseX < cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay+cell2.dia/2.0 && mouseY>cell2.y - dataM2[k][0] * level-cell.dia/2.0 && mouseY < cell2.y - dataM2[k][0] * level+cell2.dia/2.0){
        
        stroke(10);
        fill(random(0,255),random(0,255),random(0,255),100);
        strokeWeight(1);
        textSize(30);
        
      }


      else{

        stroke(0);
        fill(0,0,0,0);
        strokeWeight(0);
        

      }
    }

    catch(error){}

    
    var Nmut = 0;
    for(a=0;a<dataMutL.length;a++){

      if(k===Number(dataMutL[a][0])){
        Nmut = a;
        break;
      }

    }
    //text(dataMut[Nmut][1].toString(),linkage2[k][2]-25,linkage2[k][3]-25);
    try{
      text(dataMutL[Nmut][1].toString(), cell2.x + timedelay * dataM2[k][3] - dataM2[Start][3] * timedelay -25, cell2.y - dataM2[k][0] * level - 25);  
    }

    catch(error){

    }   
        

  

    strokeWeight(1);
    
  }


    for(var k=0;k<2*Stop;k++){
    try{
      if (mouseX>cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay-cell.dia/2.0 && mouseX < cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay+cell.dia/2.0 && mouseY>cell.y - dataM[k][0] * level-cell.dia/2.0 && mouseY < cell.y - dataM[k][0] * level+cell.dia/2.0){
        
        stroke(10);
        fill(random(0,255),random(0,255),random(0,255),100);
        strokeWeight(1);
        textSize(30);
        
      }


      else{

        stroke(0);
        fill(0,0,0,0);
        strokeWeight(0);
        

      }
    }

    catch(error){}

    
    var Nmut = 0;
    for(a=0;a<dataMutS.length;a++){

      if(k===Number(dataMutS[a][0])){
        Nmut = a;
        break;
      }

    }
    //text(dataMut[Nmut][1].toString(),linkage2[k][2]-25,linkage2[k][3]-25);
    try{
      text(dataMutS[Nmut][1].toString(), cell.x + timedelay * dataM[k][3] - dataM[Start][3] * timedelay -25, cell.y - dataM[k][0] * level - 25);  
    }

    catch(error){

    }   
        

  

    strokeWeight(1);
    
  }
    
  strokeWeight(2);
  stroke(0,0,255);
  line(0, cell.y, lineLenght, cell.y);
  stroke(255,0,0);
  for(var i = 1; i<n+1;i++){
 	 line(0, cell.y-i*level, lineLenght, cell.y-i*level); 	
  }
 stroke(0,0,0);
  strokeWeight(1);



  strokeWeight(2);
  stroke(0,0,255);
  line(0, cell2.y,   lineLenght, cell2.y);
  stroke(255,0,0);
  for(var i = 1; i<n+1;i++){

 	 line(0, cell2.y-i*level,   lineLenght, cell2.y-i*level); 	
  }
 
  stroke(0,0,0);
  strokeWeight(3);
  line(0, cell.y+nStep,   lineLenght, cell.y+nStep);
  fill(0);
  triangle(lineLenght,cell.y+nStep,lineLenght-nStep,cell.y+nStep+5,lineLenght-nStep,cell.y+nStep-5);
  fontsize = 25;
  for (var l= Start;l<Stop;l++){
    if(l%20===0){
      text(dataM[l][3].toString(),dataM[l][3]*timedelay-dataM[Start][3]*timedelay,cell.y+nStep);  
    }
      
  }
  
  stroke(0,0,0);
  strokeWeight(3);
  line(0, cell2.y+nStep,   lineLenght, cell2.y+nStep);
  fill(0);
  triangle(lineLenght,cell2.y+nStep,lineLenght-nStep,cell2.y+nStep+5,lineLenght-nStep,cell2.y+nStep-5);
  fontsize = 25;
  for (var l= Start;l<Stop2;l++){
    if(l%20===0){
      text(dataM2[l][3].toString(),dataM2[l][3]*timedelay-dataM2[Start][3]*timedelay,cell2.y+nStep);  
    }
      
  }


}


