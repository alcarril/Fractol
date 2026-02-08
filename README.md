

# fract-ol

<div align="center">

**Fractal explorer for Mandelbrot and Julia sets built with MiniLibX.**

[![42 School Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://www.42madrid.com/)
[![Made with C](https://img.shields.io/badge/Made%20with-C-A8B9CC?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![MiniLibX](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square)](https://github.com/42Paris/minilibx-linux)

</div>


---


## 📖 Overview

fract-ol is a real-time fractal explorer that renders **Mandelbrot** and **Julia** sets using iterative complex-number mathematics and the **MiniLibX (MLX) API** for windowing and pixel drawing. The project focuses on interactive rendering, smooth zoom, and precise parameter control, showcasing the relationship between math and visual complexity.

## 🖥️ Demo

<table style="width: 100%;">
  <tr>
    <td style="width: 100%;"><img src="docs/img_fractals/mandeldemo.png" alt="Mandelbrot" style="width: 100%;" /></td>
  </tr>
  <tr>
    <td style="width: 100%;"><img src="docs/img_fractals/juliatornado3.png" alt="Julia" style="width: 100%;" /></td>
  </tr>
</table>

## 🛠️ Core Features and technical highlights

### Fractal Rendering
- ✅ **Mandelbrot and Julia sets** with accurate escape-time coloring
- ✅ **Configurable iteration limits** for detail vs performance
- ✅ **Smooth zoom** with mouse wheel and high precision mapping
- ✅ **Panning** to explore different regions

### Input and Interaction
- 🖱️ **Mouse zoom** centered at cursor position
- 🎯 **Keyboard movement** for precise navigation
- 🎛️ **Julia parameter control** via CLI arguments
- 🧭 **Viewport reset** to default state

### Color and Visuals
- 🎨 **Gradient-based palette** based on escape iterations
- 🌈 **Custom color treatment** to highlight detail


<br><br>

---
# Getting Started

## 📂 Project Structure

```
Fractol/
├── include/             # Third-party libraries (libft, minilibx)
├── docs/                # Documentation and images
├── color_treatment.c    # Color palettes and iteration coloring
├── create_cgi_env.c     # Fractal selection and MLX setup
├── events.c             # Keyboard and mouse handlers
├── fractol.h            # Main structs and prototypes
├── main.c               # Entry point and argument parsing
├── math_utils.c         # Math helpers
├── render.c             # Pixel rendering and iteration loops
├── set_definition.c     # Mandelbrot/Julia definitions
├── utils.c              # Utilities and parsing
└── Makefile             # Build rules
```

## 📋 Requirements

- Linux with X11 (Xlib, Xext, Xfixes) and zlib.
- `cc` and `make`.
- MiniLibX: included in this repository.
- Libft: included in this repository.

## 🔧 Installation

### Install dependencies (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev libxfixes-dev
```

### Clone the Repository

```bash
git clone https://github.com/alcarril/Fractol.git
cd Fractol
```

## ▶️ Build and run

```bash
make
```

```bash
./fractol Mandelbrot
```

```bash
./fractol Julia -0.8 0.156
```

<br>

---

# Usage

## 🎮 Controls

| Category | Key | Action |
|---|---|---|
| Navigation | `W`, `A`, `S`, `D` | Move viewport |
| Navigation | Arrow keys | Fine pan adjustment |
| Zoom | Mouse wheel | Zoom in/out |
| View | `R` | Reset view |
| Exit | `ESC` | Quit program |


## 🧩 Julia parameters

Julia requires two parameters for the constant $c$:

```
./fractol Julia <real> <imag>
```

Example:

```
./fractol Julia -0.8 0.156
```

For stable and detailed Julia sets, keep parameters roughly within $[-2, 2]$ for both real and imaginary parts.


<br><br>

---

# Fractals

## 🌌 Mandelbrot Set

The Mandelbrot set is defined by the iteration:

$$
 z_{n+1} = z_n^2 + c, \quad z_0 = 0
$$

A point $c$ belongs to the set if the sequence does not diverge. Coloring is based on the number of iterations before escape.

## 🧪 Julia Set

The Julia set fixes $c$ and iterates the sequence for each pixel mapped to $z_0$:

$$
 z_{n+1} = z_n^2 + c, \quad z_0 = x + iy
$$

If $|z_n|$ grows beyond a chosen escape radius (commonly $2$), the point is considered divergent. The color is based on the number of iterations before escape.

### Recommended $c$ values (Julia configurations)

Use these values to explore different looks. Replace the image paths with your own captures.

**c = 0.0 + 0.8i**
```
./fractol Julia 0.0 0.8
```

<table>
  <tr>
    <td><img src="docs/img_fractals/julia.png" alt="Julia" width="400" /></td>
    <td><img src="docs/img_fractals/julia1.png" alt="Julia 1" width="400" /></td>
  </tr>
</table>

**c = -0.8 + 0.156i**
```
./fractol Julia -0.8 0.156
```

<table>
  <tr>
    <td><img src="docs/img_fractals/juliadragon.png" alt="Julia Dragon" width="400" /></td>
    <td><img src="docs/img_fractals/juliadragon1.png" alt="Julia Dragon 1" width="400" /></td>
    <td><img src="docs/img_fractals/juliadragon2.png" alt="Julia Dragon 2" width="400" /></td>
  </tr>
</table>


**c = 0.37 + 0.1i**
```
./fractol Julia 0.37 0.1
```
<table>
  <tr>
    <td><img src="docs/img_fractals/juliahojas.png" alt="Julia Hojas" width="400" /></td>
    <td><img src="docs/img_fractals/juliahojas2.png" alt="Julia Hojas 2" width="400" /></td>
  </tr>
</table>

**c = 0.355 + 0.355i**
```
./fractol Julia 0.355 0.355
```
<table>
  <tr>
    <td><img src="docs/img_fractals/juliatornado.png" alt="Julia Tornado" width="400" /></td>
    <td><img src="docs/img_fractals/juliatornado2.png" alt="Julia Tornado 2" width="400" /></td>
    <td><img src="docs/img_fractals/juliatornado3.png" alt="Julia Tornado 3" width="400" /></td>
  </tr>
</table>

**c = -0.54 + 0.54i**
```
./fractol Julia -0.54 0.54
```
<table>
  <tr>
    <td><img src="docs/img_fractals/julianose.png" alt="Julia Nose" width="400" /></td>
    <td><img src="docs/img_fractals/julianose2.png" alt="Julia Nose 2" width="400" /></td>
  </tr>
</table>

**c = -0.4 - 0.59i**
```
./fractol Julia -0.4 -0.59
```
<table>
  <tr>
    <td><img src="docs/img_fractals/julia2.png" alt="Julia 2" width="400" /></td>
    <td><img src="docs/img_fractals/julia3.png" alt="Julia 3" width="400" /></td>
    <td><img src="docs/img_fractals/julia5.png" alt="Julia 5" width="400" /></td>
  </tr>
</table>

**c = 0.34 - 0.05i**
```
./fractol Julia 0.34 -0.05
```
<table>
  <tr>
    <td><img src="docs/img_fractals/juliajulian.png" alt="Julia Julian" width="400" /></td>
    <td><img src="docs/img_fractals/juliajulian2.png" alt="Julia Julian 2" width="400" /></td>
  </tr>
</table>




<br>

---

# Features

## 🧰 MLX and X11 integration


### 🌐 What is X11 (client-server model)

**X11** is a **client-server graphics system**. The **X server** owns the display, input devices, and the window tree. Applications are **X clients** that request windows, draw into buffers, and receive input events. In Linux/UNIX, the **X11 server** acts as a **graphics sub-layer** that manages communication between graphics hardware, the OS, and client processes, providing **window creation**, **input event handling** (keyboard and mouse), and **basic screen rendering**.

### What is MiniLibX

**MiniLibX** is a **graphics API** built on top of **Xlib**, the **client-side library** used by X11 clients to talk to the X server. In this context, our program is an **X11 client**, and **MiniLibX** abstracts the low-level Xlib API so we can manipulate **windows**, **image buffers**, and **events** without dealing directly with Xlib complexity.

![X11 pipeline diagram](docs/img_mlx/X11_pipelinecomplete.png)

### 🪟 Windows and images

In **X11**, a **window** is a **server-side object**. It is a rectangular region with an **event queue** and a **drawable surface**, but it does not render by itself. The client must draw and redraw when the server reports **exposure events**.

X11 offers two main image concepts:

- **🖼️ Image (XImage)**: lives in **client memory**, pixel-accessible.
- **📦 Pixmap**: lives in **server memory**, optimized for fast blits to the window.

**Fractol** renders into an **off-screen image buffer** each frame and then pushes it to the window for **flicker-free output**.

#### ⚡ MLX drawing functions and performance

**MiniLibX** offers two common ways to draw:

- **`mlx_pixel_put`**: draws a **single pixel** directly to the window.
- **`mlx_put_image_to_window`**: blits a **full image buffer** to the window.

**`mlx_pixel_put`** is **slower** because every pixel request travels through the **full client-server stack** (client → Xlib → X server → kernel/driver → GPU). When you draw thousands of pixels per frame, that overhead dominates.

**Buffering** with an **MLX image** is **faster** because you write pixels in **client memory** (image buffer), then send a **single blit** to the X server with **`mlx_put_image_to_window`**. This reduces the number of round trips and keeps most of the work on the **client side**.


### 🎯 Events detection (hooks)

Input travels from hardware to drivers, then to the kernel, into the X server (Xorg), and finally to the client through Xlib. MiniLibX exposes this event flow as **hooks**, so we attach callbacks to specific event types:

- `mlx_hook` registers generic X11 events on a window (press, release, close, expose).
- `mlx_key_hook` and `mlx_mouse_hook` provide simplified key and mouse handlers.
- `mlx_loop_hook` runs a function every frame, ideal for continuous rendering.

In practice, input events update the viewport parameters, the render loop redraws the fractal into the image buffer, and `mlx_put_image_to_window` presents the frame.


## 🖼️ Image scaling in the render pipeline


**Fractals are rendered by mapping each screen pixel** $(x, y)$ **to a point in the complex plane.** This mapping is a **linear scaling** between two spaces:

$$
 x_c = x_{min} + \frac{x}{W} (x_{max} - x_{min}), \quad y_c = y_{min} + \frac{y}{H} (y_{max} - y_{min})
$$

Where $W$ and $H$ are the **window dimensions**, and $(x_{min}, x_{max}, y_{min}, y_{max})$ define the **current viewport**. Zoom and pan update the viewport bounds, which effectively rescales the complex-plane window without changing the screen resolution.

### 🔍 Zoom transformation

The zoom operation applies an **affine transformation** centered at the cursor position:

$$
 p' = c + s \cdot (p - c)
$$

Where $c$ is the **zoom center** and $s$ is the **scale factor**. **Translation** is applied by adding a displacement vector to the viewport bounds.

### 🎯 Practical effects

- 🔎**Zoom in** : shrink the viewport range around the cursor.
- 🔭**Zoom out** : expand the viewport range around the cursor.
- ↔️**Pan** : translate the viewport range in $x$ and $y$.

### ❓ Why scale pixels to the set?

For **continuous sets** like Mandelbrot and Julia, we iterate **every pixel** and **map it to a complex point**. This **pixel-to-set approach** avoids holes and aliasing that appear when projecting sparse sets onto discrete screens. It guarantees **full coverage** and **consistent coloring** across the image.


![Scaling diagram](docs/img_mlx/ESCALAS.png)
# Notes

- If you get a blank window, reduce zoom or increase iteration limits.
- Julia parameters outside $[-2, 2]$ often diverge quickly and may produce sparse images.
