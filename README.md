# Birdoids
Unreal Engine 5 plugin for implementing boids.

This project was heavily inspired by Sebastian Lague's project. (mentioned in the references)

This implementation of boids uses the basic 3 rules of flocking:
- Coherence
- Alignment
- Separation

as described by Craig W. Reynolds.

A "Steer to Avoid" behavior has also been implemented to allow the simulation to fly naturally in the huge landscapes that Unreal Engine allows.

The project contains RayCaster and BoidHelper which were implemented in Sebastian's video to correctly find an unobstructed direction.
However I decided to use Sphere Trace and the normal of the impact point to change the direction of the boid, which was easier performance wise.
These helpers are kept there for future reference. (And also it's a pretty cool simulation)

The Boid Manager keeps reference of the boids.

Rules can be added easily by adding to the boid's current velocity and the plan is to add as much behavior rules as possible.

Performance still needs to be improved as 100 boids already have a big impact on FPS. A simple solution for this would be to add spatial partitioning.

## Demo
*Coming soon*

## Installation
Add the contents of this project to your project's Plugins folder: ***YOUR_PROJECT_NAME\Plugins\Birdoids***

or your Engine's Plugins folder: ***PATH_TO_ENGINE\Engine\Plugins\Birdoids***

Open the editor and enable the plugin through the Plugins menu (Edit -> Plugins)

## References
[Seabstian Lague's video](https://www.youtube.com/watch?v=bqtqltqcQhw&ab_channel=SebastianLague)

[Paper by Craig W. Reynolds](http://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/)

[Reynold's website](http://www.red3d.com/cwr/)

[Boids Pseudocode](https://vergenet.net/~conrad/boids/pseudocode.html)

## TODO
- Add spatial partitioning
- Add a way to easily add rules (?)
- Adde more rules:
  - Perching
  - Wind
  - Scattering
- Add control over attraction point
- Add preset flock types
