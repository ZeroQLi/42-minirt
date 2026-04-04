# Minirt

A raytracer implemented in C from scratch, utilizing the `minilibx` library for graphics rendering.

## Description

**Minirt** is a computer graphics project that renders 3D scenes using ray tracing techniques. The raytracer parses scene description files (`.rt` format) and generates 2D renders by simulating light ray interactions with geometric objects (spheres, planes, cylinders, etc.).

### Features

- **Ray Tracing Engine**: Core ray-object intersection calculations and scene rendering
- **Lighting Model**: Basic multicolored lighting and Phong lighting with ambient, diffuse, and specular components.
- **Transformations**: Matrix-based transformations for object positioning and rotation
- **Shadows**: Real-time shadow computation
- **Bonus Features**: Advanced lighting models, shadows

## Instructions

### Prerequisites
- GCC or Clang compiler
- Make
- THe minilibx library (to be added in a '/minilibx-linux' directory)

### Building the Project

To build the project, run:

```bash
make
```

For the bonus version with extended features:

```bash
make bonus
```

### Running the Raytracer

Execute the raytracer with a scene file:

```bash
./minirt scenes/spheres.rt
```
```bash
./minirt_bonus scenes/bonus/subject_bonus.rt
```

### Scene File Format

Scene files use the `.rt` format and and require the following:
- **Camera (`C`)**: Position, viewing direction, and field of view
- **Ambient Light (`A`)**: Global illumination intensity and color
- **Light Source (`l`)**: Position, brightness, and color
- **Objects**: Spheres (`sp`), planes (`pl`), cylinders (`cy`)

Example:
```
C -50,0,20  0,0,1  70
A 0.2 255,255,255
l -40,0,30  0.7 255,255,255
sp 0,0,20  20  255,0,0
pl 0,0,0  0,0,1  0,255,0
```

## Resources

The main theory behind minirt is **Ray Tracing**. The graphical method of modeling the transport of light in a physical space in a digital enviroment. It involves the use of several rendering alghorithms to draw a visual digital image on the screen.
In addition. We incorprate the phong lighting model to incoporate specular lighting to mimic real life specular lighting as close as possible.

The main source for our project was the excellent book, *Ray tracing Challenge* by Jamis Buck. Highly recommend the book to everyone looking to embark on their project.

All references and resources have been provided below:
- **Ray Tracing challenge by Jamis Buck**: http://raytracerchallenge.com/
- **Ray Tracing Theory**: https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
- **Phong Lighting Model**: https://en.wikipedia.org/wiki/Phong_reflection_model
- **minilibx**: https://harm-smits.github.io/42docs/libs/minilibx

# Gallery
![A row of balls in uv lighting](https://github.com/ZeroQLi/42-minirt/blob/airport/images/infinityballs.png)
![3 spheres in a plane](https://github.com/ZeroQLi/42-minirt/blob/airport/images/spheres.png)
![Spheres running from a really big cylinder](https://github.com/ZeroQLi/42-minirt/blob/airport/images/suhaib.png)