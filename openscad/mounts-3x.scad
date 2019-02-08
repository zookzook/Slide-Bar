width = 50;
height = 90;
dx_1 = 5.5;
dy_1 = 5.5;
st_1 = 2.6;
h = 2.6;

module screw_holder(pos = [0,0,2] ) {
    
    translate(pos)    
    difference() {
        rotate_extrude($fn=50)
            import (file = "../dxf/screw-holder.dxf", layer = "0");
        cylinder(h = 30, r1 = 1.5, r2 = 1.5, $fn = 30, center = true);
    }
}

module mounting() {
    
    difference() {
        union() {
            linear_extrude(height = h, center = false, convexity = 1, twist = 0, slices = 20, scale = 1.0, $fn = 50)
                import (file = "../dxf/mounting-3x.dxf", layer = "0");
            
            for(i = [0 : 1 : 2]) {
                xoffset = i * 50.5;
                xpos = xoffset + 4.5;
                ypos = 5.0;                
                screw_holder([xpos, ypos, 0]);
                screw_holder([xpos + 40, ypos, 0]);
                screw_holder([xpos + 40, ypos + 80, 0]);
                screw_holder([xpos, ypos + 80, 0]);                
            }
        }
        linear_extrude(height = 10, center = true, convexity = 0, twist = 0, slices = 20, scale = 1.0, $fn = 50)
            import (file = "../dxf/mounting-3x.dxf", layer = "out");
        linear_extrude(height = 10, center = true, convexity = 0, twist = 0, slices = 20, scale = 1.0, $fn = 50)
            import (file = "../dxf/mounting-3x.dxf", layer = "out-2");

        rotate([0,0,90])
        translate([0,0,-1])
                cube([90,10,3]);

        rotate([0,0,90])
        translate([0,-(3*50+10),-1])
                cube([90,10,3]);

    }

}


mounting();

