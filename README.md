# 42-cub3d

Learning computer graphic basics and raycasting by doing a Wolfenstein3D-like game.

- macOS:

  ```
  $> git clone https://github.com/josayko/42-cub3d.git
  $> cd cub3d/
  $> make
  ```

- Debian/Ubuntu based distribution:

  - You must install the dependencies first:

  ```
  $> sudo apt update
  $> sudo apt install clang make libx11-dev libxext-dev libbsd-dev
  ```

  - Clone the repo:

  ```
  $> git clone https://github.com/josayko/42-cub3d.git
  ```

  - The graphic library for Linux version needs to be pulled from 42Paris github repo
  ```
  $> cd cub3d/
  $> git submodule update --init --recursive
  $> make
  ```
