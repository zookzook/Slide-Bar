d = 7;
h = 1.5;

linear_extrude(height = h, center = true, convexity = 0, twist = 0, slices = 20, scale = 1.0, $fn = 50)
    import (file = "../dxf/washer.dxf", layer = "washer");
