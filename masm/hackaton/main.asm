.286

vec3    struc
    x   dd 0.0
    y   dd 0.0
    z   dd 0.0
vec3    ends

DSEG SEGMENT para public USE16 'DATA'
    v1 dd
    v2 dd
    v3 dd
DSEG ENDS


CSEG SEGMENT para public USE16 'CODE'
    assume CS:CSEG, DS:DSEG

main:
    v1      vec3    <1.0, 1.0, 0.0>
    v2      vec3    <0.0, 1.0, 1.0>
    v3      vec3    <0.0, 0.0, 0.0> 

CSEG ENDS
END