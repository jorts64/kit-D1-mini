camColors = [0x480F,
0x400F,0x400F,0x400F,0x4010,0x3810,0x3810,0x3810,0x3810,0x3010,0x3010,
0x3010,0x2810,0x2810,0x2810,0x2810,0x2010,0x2010,0x2010,0x1810,0x1810,
0x1811,0x1811,0x1011,0x1011,0x1011,0x0811,0x0811,0x0811,0x0011,0x0011,
0x0011,0x0011,0x0011,0x0031,0x0031,0x0051,0x0072,0x0072,0x0092,0x00B2,
0x00B2,0x00D2,0x00F2,0x00F2,0x0112,0x0132,0x0152,0x0152,0x0172,0x0192,
0x0192,0x01B2,0x01D2,0x01F3,0x01F3,0x0213,0x0233,0x0253,0x0253,0x0273,
0x0293,0x02B3,0x02D3,0x02D3,0x02F3,0x0313,0x0333,0x0333,0x0353,0x0373,
0x0394,0x03B4,0x03D4,0x03D4,0x03F4,0x0414,0x0434,0x0454,0x0474,0x0474,
0x0494,0x04B4,0x04D4,0x04F4,0x0514,0x0534,0x0534,0x0554,0x0554,0x0574,
0x0574,0x0573,0x0573,0x0573,0x0572,0x0572,0x0572,0x0571,0x0591,0x0591,
0x0590,0x0590,0x058F,0x058F,0x058F,0x058E,0x05AE,0x05AE,0x05AD,0x05AD,
0x05AD,0x05AC,0x05AC,0x05AB,0x05CB,0x05CB,0x05CA,0x05CA,0x05CA,0x05C9,
0x05C9,0x05C8,0x05E8,0x05E8,0x05E7,0x05E7,0x05E6,0x05E6,0x05E6,0x05E5,
0x05E5,0x0604,0x0604,0x0604,0x0603,0x0603,0x0602,0x0602,0x0601,0x0621,
0x0621,0x0620,0x0620,0x0620,0x0620,0x0E20,0x0E20,0x0E40,0x1640,0x1640,
0x1E40,0x1E40,0x2640,0x2640,0x2E40,0x2E60,0x3660,0x3660,0x3E60,0x3E60,
0x3E60,0x4660,0x4660,0x4E60,0x4E80,0x5680,0x5680,0x5E80,0x5E80,0x6680,
0x6680,0x6E80,0x6EA0,0x76A0,0x76A0,0x7EA0,0x7EA0,0x86A0,0x86A0,0x8EA0,
0x8EC0,0x96C0,0x96C0,0x9EC0,0x9EC0,0xA6C0,0xAEC0,0xAEC0,0xB6E0,0xB6E0,
0xBEE0,0xBEE0,0xC6E0,0xC6E0,0xCEE0,0xCEE0,0xD6E0,0xD700,0xDF00,0xDEE0,
0xDEC0,0xDEA0,0xDE80,0xDE80,0xE660,0xE640,0xE620,0xE600,0xE5E0,0xE5C0,
0xE5A0,0xE580,0xE560,0xE540,0xE520,0xE500,0xE4E0,0xE4C0,0xE4A0,0xE480,
0xE460,0xEC40,0xEC20,0xEC00,0xEBE0,0xEBC0,0xEBA0,0xEB80,0xEB60,0xEB40,
0xEB20,0xEB00,0xEAE0,0xEAC0,0xEAA0,0xEA80,0xEA60,0xEA40,0xF220,0xF200,
0xF1E0,0xF1C0,0xF1A0,0xF180,0xF160,0xF140,0xF100,0xF0E0,0xF0C0,0xF0A0,
0xF080,0xF060,0xF040,0xF020,0xF800];

pixels = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];



function readDir() {
      var xhttp = new XMLHttpRequest();
      var dadesAJAX = "buit";
      xhttp.open('GET', 'ajaxdir', false);
      xhttp.send();
      dadesAJAX = xhttp.responseText;
      return (dadesAJAX);
}

function readArray(fname) {
      var xhttp = new XMLHttpRequest();
      var dadesAJAX = "buit";
      xhttp.open('GET', fname, false);
      xhttp.send();
      dadesAJAX = xhttp.responseText;
      return (dadesAJAX);
} 

function filterFile(value, index, array) {
  return value.endsWith(".dat");
}

function getDir() {
   var dirstr = readDir();
   var dirarr = dirstr.split(",");
   var dirdat = dirarr.filter(filterFile);
   nfotos = dirdat.length;
   return dirdat;
}

function seguent() {
   if (fotonum < nfotos-1) fotonum++;
   var myVar = loadArray(arxius[fotonum]);
}

function anterior() {
   if (fotonum > 0) fotonum--;
   var myVar = loadArray(arxius[fotonum]);
}

function pescala(ctx){
  for (i=0; i<12;i++) {
    x=10*i;
    y=0;
    var tempi=(maxtemp - mintemp)/12*(i+0.5)+mintemp;
    var colorindexi= arduino_map(tempi, mintemp, maxtemp, 0, 255);
    var colori=camColors[colorindexi];    ctx.fillStyle = "#0000FF";
    ctx.fillStyle = colorRGBhex(colori);
    ctx.fillRect(x, y, 15, 20)
    }
}

function pfoto(ctx, boxSize) {
  var colorTemp;
  for (y=0; y<8; y++) {
    for (x=0; x<8; x++) {
      var val = pixels[(7-y)*8+x];
      colorTemp = val;
      if(val >= maxtemp) colorTemp = maxtemp;
      if(val <= mintemp) colorTemp = mintemp;
      var colorIndex = arduino_map(colorTemp, mintemp, maxtemp, 0, 255);
      colorIndex = arduino_constrain(colorIndex, 0, 255);
      //draw the pixels!
      var color = camColors[colorIndex];
      ctx.fillStyle = colorRGBhex(color);
      ctx.fillRect(boxSize * x, boxSize * y, boxSize, boxSize);
    } 
  }
}

function loadArray(fotarx) {
  document.getElementById('nomf').innerHTML = fotarx;
  var txt= readArray(fotarx);
//  document.getElementById('crues').innerHTML = txt;
  var r = 0; var s = 0;
  r = txt.indexOf("\n");
  var fecha = txt.substring(0,r);
  document.getElementById('fecha').innerHTML = "Data: " + fecha;
  s = r+1;
  r = txt.indexOf("\n",s+1);
  var hora = txt.substring(s,r);
  document.getElementById('hora').innerHTML = "Hora: " + hora;
  s = r+1;
  r = txt.indexOf("\n",s+1);
  var tth = txt.substring(s,r);
  document.getElementById('tth').innerHTML = tth;
  s = r+1;
  r = txt.indexOf("\n",s+1);
  var rangt = txt.substring(s,r);
  document.getElementById('rangt').innerHTML = "Rang temperatures: " + rangt;
  s = r+1;
  r = txt.indexOf("\n",s+1);
  var tmin = txt.substring(s,r);
  document.getElementById('tmin').innerHTML = tmin;
  s = r+1;
  r = txt.indexOf("\n",s+1);
  var tmax = txt.substring(s,r);
  document.getElementById('tmax').innerHTML = tmax;
  for (i=0;i<64;i++) {
    s = r+1;
    r = txt.indexOf(",",s+1);
    pixels[i]= parseFloat(txt.substring(s,r));
    } 
  r = rangt.indexOf("-");
  mintemp = parseFloat(rangt.substring(0,r));  
  maxtemp = parseFloat(rangt.substring(r+1));  
//  document.getElementById('mintemp').innerHTML = mintemp;
//  document.getElementById('maxtemp').innerHTML = maxtemp;
  var valors = "";
  for (i=0;i<8;i++) {
    for (j=0;j<8;j++) {
      valors = " " + valors + pixels[i*8+j] + ", ";
      }
    valors = valors + "<br/>";
    } 
  document.getElementById('array').innerHTML = valors;



  var c = document.getElementById("escala");
  var ctx1 = c.getContext("2d");
  var esc1 = pescala(ctx1);

  var c = document.getElementById("foto");
  var ctx2 = c.getContext("2d");
  var pf1 = pfoto(ctx2, 15);
}


function arduino_map(valinp, mininp, maxinp, minout, maxout) {
    var valout = (valinp - mininp) * (maxout - minout) / (maxinp - mininp) + minout;
    valout = Math.round(valout);
    return valout;
}

function arduino_constrain(valinp, minout, maxout) {
    var valout = valinp;
    if (valinp < minout) valout = minout;
    if (valinp > maxout) valout = maxout;
    return valout;
}

function colorRGB (col565) {
   var colout = (col565 & 0xF800) * 256;
   colout = colout + (col565 & 0x07E0) * 32;
   colout = colout + (col565 & 0x001F) * 8;
   return colout;
}

function componentToHex(c) {
    var hex = c.toString(16);
    return hex.length == 1 ? "0" + hex : hex;
}

function rgbToHex(r, g, b) {
    return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
}

function colorR (col565) {
   var colout = (col565 & 0xF800) / 256;
   return colout;
}
function colorG (col565) {
   var colout = (col565 & 0x07E0) / 8;
   return colout;
}
function colorB (col565) {
   var colout = (col565 & 0x001F)*8;
   return colout;
}
function colorRGBhex (col565) {
   return rgbToHex(colorR(col565), colorG(col565), colorB(col565));
   return colout;
}

