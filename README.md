# cub3d – A Minimal 3D Raycasting Engine (42 Project)

cub3d is a lightweight 3D engine inspired by *Wolfenstein 3D*, built entirely in C as part of the 42 curriculum.  
It renders a 3D world using **raycasting**, allowing the player to navigate a maze-like environment with textures, collisions, and smooth camera rotation.

The objective of the project is to understand the fundamentals of 3D rendering without OpenGL, using only math, vectors, and pixel manipulation inside an image buffer.

---

## 🚀 Features

### ✔ 3D Raycasting Renderer
- Digital Differential Analysis (DDA) implementation  
- Per-column ray projection  
- Wall distance correction (fish-eye fix)  
- Support for north/south/east/west textures  
- Adjustable FOV

### ✔ Player System
- Smooth movement forward/backward  
- Strafing (left/right)  
- Camera rotation using angles or vectors  
- Real collision detection with walls  

### ✔ Map Parsing
- Reads `.cub` configuration files  
- Validates the map as closed (no leaks)  
- Loads textures, colors, and spawn position  
- Handles invalid characters and bad formatting

### ✔ Texturing Engine
- X/Y texture coordinate mapping  
- Wall height scaling  
- Pixel-perfect texture sampling  
- RGB floor/ceiling coloring  

### ✔ Minimap (if implemented)
- Top-down view of the world  
- Real-time player position  
- Rays drawn for debugging  

### ✔ Event Handling (MLX)
- Smooth keyboard input  
- ESC → clean exit  
- Window closing event  
- Continuous render loop  

---

## 🧠 Architecture Overview

### **1. Map / Config Parser**
Reads `.cub` file and extracts:

- Texture paths  
- Floor & ceiling RGB colors  
- Map layout  
- Player initial rotation and position  

Ensures the map is valid, surrounded by walls, and well-structured.

---

### **2. Raycasting Engine**
Implements the full DDA algorithm:

1. Cast one ray per vertical screen column  
2. Detect wall intersection  
3. Compute perpendicular distance  
4. Calculate projected wall height  
5. Choose correct texture  
6. Render pixel column into the framebuffer  

---

### **3. Rendering Pipeline**
- Framebuffer cleared each frame  
- Floor & ceiling drawn  
- Wall projection per column  
- Final image pushed using `mlx_put_image_to_window()`  

---

### **4. Input System**
Handled using MiniLibX events:

- `W / S` → forward / backward  
- `A / D` → strafing  
- `← / →` → camera rotation  
- ESC → exit cleanly  

Movement is based on direction vectors to support smooth rotation and walking.

---

### **5. Collision Detection**
The engine checks the next player position against the map grid and prevents walking through walls for an authentic FPS feel.

---

## 🔧 Compilation

```bash
make
