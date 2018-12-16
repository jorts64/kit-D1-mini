rboton1=8;
rtriple=2;
rcam=2;
rjoys=2;
difference(){
union(){
    cube ([115,85,2]);
    cube ([115,2,45]);
    translate([0,83,0]) cube ([115,2,45]);
    cube ([2,85,45]);
    translate([113,0,0]) cube ([2,85,45]);
    translate([0,30,0]) cube ([100,2,30]);
    translate([100,0,0]) cube ([2,32,30]);    
    translate([95,0,28]) cube ([5,32,2]);
    translate([45,0,28]) cube ([10,32,2]);
}
union(){
    translate([15,58,0]) cube([7,12,2]);
    translate([55,83,22]) rotate([-90,0,0]) cylinder(r=rboton1, h=2);
    translate([66,83,14]) rotate([-90,0,0]) cylinder(r=rboton1, h=2);
    translate([66,83,29]) rotate([-90,0,0]) cylinder(r=rboton1, h=2);
    translate([77,83,22]) rotate([-90,0,0]) cylinder(r=rboton1, h=2);
    translate([99,83,22]) rotate([-90,0,0]) cylinder(r=rboton1, h=2);
    translate([1,1,43]) cube([113,83,2]);    
    translate([0,2,2]) cube([2,28,23]);
    translate([34,66,0]) cylinder(r=rtriple, h=2);
//    translate([54,66,0]) cylinder(r=rtriple, h=2);
    translate([61,66,0]) cylinder(r=rtriple, h=2);
//    translate([80,66,0]) cylinder(r=rtriple, h=2);
//    translate([88,66,0]) cylinder(r=rtriple, h=2);
    translate([107,66,0]) cylinder(r=rtriple, h=2);
//    translate([34,38,0]) cylinder(r=rtriple, h=2);
    translate([54,38,0]) cylinder(r=rtriple, h=2);
//    translate([61,38,0]) cylinder(r=rtriple, h=2);
//    translate([80,38,0]) cylinder(r=rtriple, h=2);
    translate([88,38,0]) cylinder(r=rtriple, h=2);
//    translate([107,38,0]) cylinder(r=rtriple, h=2);
    translate([12,68,0]) cylinder(r=rcam, h=2);
    translate([25,68,0]) cylinder(r=rcam, h=2);
    translate([46,83,10]) rotate([-90,0,0])  cylinder(r=rjoys, h=2);
    translate([46,83,36]) rotate([-90,0,0])  cylinder(r=rjoys, h=2);
    translate([107,83,10]) rotate([-90,0,0])  cylinder(r=rjoys, h=2);
    translate([107,83,36]) rotate([-90,0,0])  cylinder(r=rjoys, h=2);
    translate([113,10,20]) cube([2,10,5]);    
}
}