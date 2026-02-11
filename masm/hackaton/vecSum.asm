.286

PUBLIC vecSum


vec3    struc
    x   dd 0.0
    y   dd 0.0
    z   dd 0.0
vec3    ends

; float_sum:

vecSum:
    fld v1.x
    fld v2.x
    faddp
    fstp v3.x
    ret

main:
    v1      vec3    <1.0, 1.0, 0.0>
    v2      vec3    <0.0, 1.0, 1.0>
    v3      vec3    <0.0, 0.0, 0.0>
