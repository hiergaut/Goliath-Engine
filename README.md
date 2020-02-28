# Goliath-Engine_standalone
My first experimental engine (C++, OpenGL, Qt) for rendering, modelisation and animation

Gui (clone Blender)

Release date :  February 2020

Code is in a private repo (Precompiled library)

Source is coming soon

---

## Dependencies
* Assimp (no submodule, system library, compiled with latest version on Arch Linux)
* glm (no submodule, system library, compiled with latest version on Arch Linux)

---

##  Building on Linux (command line instruction)
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```
---

## Rendering
### Shadow and light
<!-- [![](https://img.youtube.com/vi/gDdghUDYpok/0.jpg)](https://youtu.be/gDdghUDYpok "view on youtube") -->
[![](shadow.png)](https://youtu.be/gDdghUDYpok "view on youtube")
<!-- https://youtu.be/gDdghUDYpok -->

### Frustum culling
[![](https://img.youtube.com/vi/xsooSpulDy8/0.jpg)](https://youtu.be/xsooSpulDy8 "view on youtube")
<!-- https://youtu.be/xsooSpulDy8 -->

### Real time shadow point light map calculation
[![](https://img.youtube.com/vi/IASGQYvVZYA/0.jpg)](https://youtu.be/IASGQYvVZYA "view on youtube")

---

## Modelisation
### BSpline
<!-- [![bspline](bSpline.png)](https://youtu.be/0qHZ_LvAo_0 "wiew on youtube") -->
[![bspline](bSpline.png)](https://youtu.be/Ms513wlBTy4 "wiew on youtube")

additional video : https://youtu.be/0qHZ_LvAo_0

### Nurbs (BSpline with weights)
example of perfect circle :

![nurbs](nurbs.png)

### PN Triangles Tessellation
[![](pnTriangles.png)](https://youtu.be/Ck42FhEDYWU "view on youtube")

## Animation
### Editor
[![](https://img.youtube.com/vi/z9rkk2G78Mk/0.jpg)](https://youtu.be/z9rkk2G78Mk "view on youtube")

### LBS and DQS
[![](https://img.youtube.com/vi/A9o_65bn68Y/0.jpg)](https://youtu.be/A9o_65bn68Y "view on youtube")


---

## Bonus
### Multiple view camera (Sponza)
![sponza](sponza.png)
