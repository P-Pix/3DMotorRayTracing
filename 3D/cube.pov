#include "colors.inc"
#include "stones.inc"
#include "textures.inc"
#include "shapes.inc"
#include "glass.inc"
#include "metals.inc"
#include "woods.inc"

camera {
    location <0, 2, -3>
    look_at <0, 1, 2>
}

cylinder {
    <1, 1, -1>, <0, 0, 1>, 1 // center of one end, center of other end, radius
    open // remove end caps
    pigment {
        color rgb <0.5, 0.5, 0.5>
    }   
}