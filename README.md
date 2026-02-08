

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

<img src="docs/img_fractals/mandeldemo.png" alt="Mandelbrot" style="width: 100%;" />

<img src="docs/img_fractals/juliatornado3.png" alt="Julia" style="width: 100%;" />

## 🛠️ Core Features and technical highlights

### Fractal Rendering
- ✅ **Mandelbrot and Julia sets** with accurate escape-time coloring
- ✅ **Configurable iteration limits** for detail vs performance
- ✅ **Smooth zoom** with mouse wheel and high precision mapping
- ✅ **Panning** to explore different regions

### Input and Interaction
- 🖱️ **Mouse zoom** centered at cursor position
- 🎨 **Iteration control** with `+` and `-` keys for dynamic detail adjustment
- 🎯 **Keyboard movement** for precise navigation
- 🎛️ **Julia parameter control** via CLI arguments

### Color and Visuals
- 🎨 **Gradient-based palette** based on escape iterations
- 🌈 **Custom color treatment** to highlight detail


<br>

---
# Getting Started

## 📂 Project Structure

```
Fractol/
├── libs/                # Libraries (libft propia, minilibx API)
├── docs/                # Documentation and images
├── src/                 # Project sources
│   ├── fractol.h         # Main structs, constants, prototypes
│   ├── main.c            # Entry point and argument parsing
│   ├── create_cgi_env.c  # Fractal selection and MLX setup
│   ├── events.c          # Keyboard and mouse handlers
│   ├── render.c          # Pixel rendering and iteration loops
│   ├── set_definition.c  # Mandelbrot/Julia definitions
│   ├── color_treatment.c # Color palettes and iteration coloring
│   ├── math_utils.c      # Math helpers
│   └── utils.c           # Utilities and parsing
├── Makefile             # Build rules
```
### Project Overview: 

You can view the complete project architecture and ask an AI about the code here: https://deepwiki.com/alcarril/Fractol

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
| Navigation | Arrow keys | Fine pan adjustment |
| Zoom | Mouse wheel | Zoom in/out |
| Color | `+` / `-` | Increase/decrease color iteration count per pixel |
| Exit | `ESC` | Quit program |

> Note: If the window is blank, try lowering the iteration count.



## 🧩 Julia parameters

Julia requires two parameters for the constant $c$:

```
./fractol Julia <real> <imag>
```

Example:

```
./fractol Julia -0.8 0.156
```

> Note: For stable and detailed Julia sets, keep parameters roughly within $[-2, 2]$ for both real and imaginary parts.


<br>

---

#  MLX and X11 integration


## 🌐 What is X11 (client-server model)

**X11** is a **client-server graphics system**. The **X server** owns the display, input devices, and the window tree. Applications are **X clients** that request windows, draw into buffers, and receive input events. In Linux/UNIX, the **X11 server** acts as a **graphics sub-layer** that manages communication between graphics hardware, the OS, and client processes, providing **window creation**, **input event handling** (keyboard and mouse), and **basic screen rendering**.

## ⚡ What is MiniLibX

**MiniLibX** is a **graphics API** built on top of **Xlib**, the **client-side library** used by X11 clients to talk to the X server. In this context, our program is an **X11 client**, and **MiniLibX** abstracts the low-level Xlib API so we can manipulate **windows**, **image buffers**, and **events** without dealing directly with Xlib complexity.

![X11 pipeline diagram](docs/img_mlx/X11_pipelinecomplete.png)

## 🪟 Windows and images

In **X11**, a **window** is a **server-side object**. It is a rectangular region with an **event queue** and a **drawable surface**, but it does not render by itself. The client must draw and redraw when the server reports **exposure events**. X11 offers two main image concepts:



| Concept | Storage | Characteristics |
|---------|---------|-----------------|
| **Image (XImage)** | Client memory | Pixel-accessible, slower for large transfers |
| **Pixmap** | Server memory | Optimized for fast blits to the window |



### 💾 Image buffering vs. direct pixel drawing


**Direct pixel drawing** sends each pixel request through the **client-server pipeline**, creating significant overhead when rendering thousands of pixels per frame.

**Buffering with an off-screen image** is more efficient: pixels are written to **client-side memory**, then a **single blit operation** transfers the completed frame to the X server. This approach minimizes network round trips and keeps computation local to the client.


> Note: **Fractol** renders into an **off-screen image buffer** each frame and then pushes it to the window for **flicker-free output**.


### 🖍️ MLX drawing functions


| Function | Target | Method |
|----------|--------|--------|
| **`mlx_pixel_put`** | Window | Single pixel at a time |
| **`mlx_put_image_to_window`** | Window | Full image buffer blit |




## 🪝 Events detection (hooks)

Input travels from hardware to drivers, then to the kernel, into the X server (Xorg), and finally to the client through Xlib. MiniLibX exposes this event flow as **hooks**, so we attach callbacks to specific event types:

| Hook | Purpose |
|------|---------|
| `mlx_hook` | Registers generic X11 events on a window (press, release, close, expose) |
| `mlx_key_hook` | Provides simplified keyboard event handlers |
| `mlx_mouse_hook` | Provides simplified mouse event handlers |
| `mlx_loop_hook` | Runs a function every frame, ideal for continuous rendering |


In practice, input events update the viewport parameters, the render loop redraws the fractal into the image buffer, and `mlx_put_image_to_window` presents the frame.


<br>

---

# Fractals

Fractals are geometric shapes built from simple rules repeated at many scales. Their defining principles are **self-similarity** (patterns that look alike when zoomed), **iteration** (repeated mathematical steps), and **sensitivity to initial conditions**, which produces rich detail from compact formulas. Sets like Mandelbrot and Julia come from iterating complex-number functions on the complex plane, classifying each point by whether the sequence stays bounded or escapes.

These patterns are not just mathematical curiosities: fractal-like structures appear in nature, such as coastlines, mountain ranges, clouds, river networks, snowflakes, ferns, and even branching in trees and lightning. This project visualizes that same idea of repeating structure and infinite detail through interactive zooming.


## 🧮 How do we calculate fractals?


For each pixel on the screen, we convert it to a point on the **complex plane**. We apply an **iterative formula** to that point (for example $z_{n+1} = z_n^2 + c$) and repeat the process a **fixed number of times**. If at any step the value of $|z_n|$ exceeds an **escape radius** (typically $2$), we consider the point **divergent**.

The **color** of each pixel is based on **how many iterations it takes to escape**. If it escapes quickly, it is painted with a different color than if it takes longer or doesn't escape within the limit. This is why the **maximum iteration count** affects **detail** and **palette**: with `+` and `-` you can increase or decrease those iterations to see more detail or gain performance.


## 🎨 How do we select the color?

To colorize, you can use a **color palette** and scale it to the number of iterations used to decide whether the point escapes or not. Another option is to apply a **mathematical gradient**, modifying a base color based on the number of operations before escape. In this project, I chose to use the palette approach.

## 🔎 What about infinite zoom?

These sets are described as having **infinite depth** because they are perfectly imperfect: if the perfect path between two points is a straight line, the less perfect one can have infinite detail. That's why you can zoom frame after frame and keep finding new structures. In practice, the only limits are resolution, precision, and your computer's performance.


## 1️⃣ Mandelbrot Set

The Mandelbrot set is defined by the iteration:

$$
 z_{n+1} = z_n^2 + c, \quad z_0 = 0
$$

A point $c$ belongs to the set if the sequence does not diverge. Coloring is based on the number of iterations before escape.

<table>
  <tr>
    <td><img src="docs/img_fractals/mandeldemo.png" alt="Mandelbrot Demo" width="400" /></td>
    <td><img src="docs/img_fractals/mandeldemo2.png" alt="Mandelbrot 3" width="400" /></td>
  </tr>
  <tr>
    <td><img src="docs/img_fractals/mandeldemo4.png" alt="Mandelbrot Demo 4" width="400" /></td>
    <td><img src="docs/img_fractals/mandel.png" alt="Mandelbrot" width="400" /></td>
  </tr>
</table>


## 2️⃣ Julia Set

The Julia set fixes $c$ and iterates the sequence for each pixel mapped to $z_0$:

$$
 z_{n+1} = z_n^2 + c, \quad z_0 = x + iy
$$

If $|z_n|$ grows beyond a chosen escape radius (commonly $2$), the point is considered divergent. The color is based on the number of iterations before escape.

### Recommended $c$ values (Julia configurations)

Use these values to explore different looks. Replace the image paths with your own captures.

<div align="center"><strong>c = 0.0 + 0.8i</strong></div>

```
./fractol Julia 0.0 0.8
```

<table>
  <tr>
    <td><img src="docs/img_fractals/julia.png" alt="Julia" width="400" /></td>
    <td><img src="docs/img_fractals/julia1.png" alt="Julia 1" width="400" /></td>
  </tr>
</table>

<div align="center"><strong>c = -0.8 + 0.156i</strong></div>

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


<div align="center"><strong>c = 0.37 + 0.1i</strong></div>

```
./fractol Julia 0.37 0.1
```
<table>
  <tr>
    <td><img src="docs/img_fractals/juliahojas.png" alt="Julia Hojas" width="400" /></td>
    <td><img src="docs/img_fractals/juliahojas2.png" alt="Julia Hojas 2" width="400" /></td>
  </tr>
</table>

<div align="center"><strong>c = 0.355 + 0.355i</strong></div>

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

<div align="center"><strong>c = -0.54 + 0.54i</strong></div>

```
./fractol Julia -0.54 0.54
```

<table>
  <tr>
    <td><img src="docs/img_fractals/julianose.png" alt="Julia Nose" width="400" /></td>
    <td><img src="docs/img_fractals/julianose2.png" alt="Julia Nose 2" width="400" /></td>
  </tr>
</table>

<div align="center"><strong>c = -0.4 - 0.59i</strong></div>

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

<div align="center"><strong>c = 0.34 - 0.05i</strong></div>

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

- **Zoom in** : shrink the viewport range around the cursor.
- **Zoom out** : expand the viewport range around the cursor.
- **Pan** : translate the viewport range in $x$ and $y$.

### ❓ Why scale pixels to the set?

For **continuous sets** like Mandelbrot and Julia, we iterate **every pixel** and **map it to a complex point**. This **pixel-to-set approach** avoids holes and aliasing that appear when projecting sparse sets onto discrete screens. It guarantees **full coverage** and **consistent coloring** across the image.

> **Note:** 📝 More: [My article on Notion](https://broken-snowdrop-f03.notion.site/Renderizado-de-imegenes-y-escalas-2fbb80eb3d8880d69491dbec05c804ae).


<br>

---

# ℹ️​ Resources

### Mathematics

#### Complex numbers

- https://www.youtube.com/watch?v=LqyBrrgmIro&ab_channel=Derivando
- https://www.youtube.com/watch?v=hWbwBGPLvk4

#### Fractal 

- https://www.youtube.com/watch?v=Wea_1L-C9Xo
- https://www.youtube.com/watch?v=Tt-jjxjTHTQ
- https://www.youtube.com/watch?v=EOvLhZPevm0&t=16s
- https://www.youtube.com/watch?v=gB9n2gHsHN4
- https://complex-analysis.com/contenido/conjunto_de_mandelbrot.html
- https://www.geogebra.org/m/shfghkn7
- https://en.wikipedia.org/wiki/Mandelbrot_set
- https://en.wikipedia.org/wiki/Julia_set

#### Math library

- https://platzi.com/blog/todas-las-funciones-de-la-biblioteca-mathh-en-c/

### Mlx and X11

- https://github.com/42Paris/minilibx-linux
- https://harm-smits.github.io/42docs/libs/minilibx

<br>

---

# 👨‍💻 Author

**Alejandro Carrillo** [@alcarril](https://github.com/alcarril)


---

## 📜 License

This project does not include a license file in the repository.


