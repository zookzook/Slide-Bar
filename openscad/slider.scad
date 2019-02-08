
module schieber() {
translate([-10,0,0])
rotate([90,0,0])
        linear_extrude(height = 12, center = true, convexity = 1, twist = 0, slices = 20, scale = 1.0, $fn = 80)
            import (file = "../dxf/slider.dxf", layer = "0");
            
}

module mounting() {
    translate([-2,-1,-0.5])
    cube([4,2,5]);
}

difference() {
    schieber();
    mounting();
}