# miniRT

![Status](https://img.shields.io/badge/Status-Work_in_Progress-orange?style=flat-square)

**Authors:** Lorena and Lody (Volodymyr) Iaremko

## About the Project
miniRT is our first RayTracer written in C, built using the MLX42 library. The goal of this project is to generate computer-generated images using the Raytracing protocol. By implementing core mathematical and physical formulas, this program renders a scene as seen from a specific angle and position, complete with simple geometric objects and a lighting system.

The program is designed from the ground up to be completely leakless. All heap-allocated memory must be properly freed when necessary. Memory leaks will not be tolerated. The codebase is also written in accordance with the Norm.

## Current Progress
**Status:** Work in Progress (WIP)

*   ✅ **Done:** Parsing stage. The program can successfully read and parse `.rt` scene description files.
*   🔄 **In Progress:** Implementing ray tracing from the camera, as well as calculating ray and sphere intersections.
*   ⏳ **To Do:** Planes, cylinders, translations, rotations, and lighting (ambient and diffuse, hard shadows).

---

## Mandatory Features (Planned)
The final rendering engine will support:

*   **Window Management:** Fluid window handling (switching, minimizing) with clean exits via the ESC key or the window's red cross.
*   **Geometric Objects:** Intersections and insides handled correctly for Planes, Spheres, and Cylinders.
*   **Transformations:** Translation and rotation applied to objects, lights, and cameras.
*   **Lighting System:** Ambient lighting, diffuse lighting, spot brightness, and hard shadows.

## Scene Configuration (`.rt` files)
The program takes a scene description file with the `.rt` extension as its first argument. If any misconfiguration is encountered in the file, the program will exit properly and print `Error\n` followed by an explicit error message.

The parser currently handles the following identifiers:
*   `A`: Ambient lighting
*   `C`: Camera
*   `L`: Light
*   `sp`: Sphere
*   `pl`: Plane
*   `cy`: Cylinder

---

## Compilation and Usage
A `Makefile` is provided to compile the source files using `cc` with the flags `-Wall`, `-Wextra`, and `-Werror`.

```bash
# Compile the project
make

# Run the RayTracer with a scene file
./miniRT path/to/scene.rt
