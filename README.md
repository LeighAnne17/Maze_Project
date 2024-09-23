Maze Project


Introduction

The Maze Project is a 3D game built using raycasting and SDL2. The goal is to create an immersive 3D maze experience, where the player navigates through a maze using keyboard controls. The project simulates a first-person view, similar to classic games like Wolfenstein 3D, and implements core features such as wall rendering, camera rotation, movement, and collision detection.


Author's LinkedIn Profile:
https://www.linkedin.com/in/nonkanyiso-ndimande

Installation
To run the project on your local machine, follow these instructions.

Prerequisites
Ubuntu 14.04 LTS (or similar Linux distro)
gcc 4.8.4 or later
SDL2 (Ensure SDL2 is installed using this guide)


Steps
Clone the repository:
git clone https://github.com/LeighAnne17/Maze_Project.git

Navigate to the project directory:
cd maze-project

Install SDL2 (if not already installed):
sudo apt-get install libsdl2-dev

Compile the project:
gcc -Wall -Werror -Wextra -pedantic src/*.c -o maze -lSDL2

Run the game:
./maze [path-to-map-file]


Usage
Use WASD keys to move the player.
Use arrow keys to rotate the camera.
Collisions with walls are handled so the player cannot pass through them.
The map is customizable via an input file.


Related Projects
Wolfenstein 3D
Raycasting Tutorial
License
This project is licensed under the MIT License - see the LICENSE file for details.


Technical Details
This project uses raycasting to simulate 3D graphics in a 2D environment. Raycasting works by casting rays from the player's viewpoint to detect walls and render them in perspective, creating a 3D illusion.


Challenges
The most challenging aspect was implementing collision detection and ensuring smooth player movement. Another challenge was handling multiple events (such as moving and rotating at the same time).


Next Iteration
In future iterations, I plan to:


Add enemies with basic AI behavior.
Implement weapon textures and shooting mechanics.
Introduce weather effects like rain and lighting for added immersion.
Story & Inspiration
This project was inspired by classic first-person shooters like Wolfenstein 3D, where players navigate mazes filled with enemies and obstacles. The technical challenge of learning raycasting and SDL2 was a great opportunity to push my understanding of graphics programming. I faced many struggles, particularly with map parsing and player collision, but those challenges have deepened my understanding of game development.


Additional Resources
SDL2 Documentation
Raycasting Tutorial
