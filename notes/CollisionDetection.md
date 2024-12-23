A physics engine tracks collisions using a combination of techniques and data structures to efficiently detect when and where objects intersect. Here’s an overview of how collision detection works in a physics engine:

### 1. **Collision Shapes**
Each object in the physics world is represented by a collision shape, which simplifies its geometry into basic forms. Common shapes include:
- **AABBs (Axis-Aligned Bounding Boxes)**: Rectangles aligned with the coordinate axes.
- **Circles**: Represented by a center point and a radius.
- **Polygons**: More complex shapes defined by vertices.

### 2. **Broad Phase Collision Detection**
This is the first step in the collision detection process, aiming to quickly identify potential collisions among a large number of objects. It uses spatial partitioning methods, such as:
- **Bounding Volume Hierarchies (BVH)**: A tree structure that organizes objects hierarchically, allowing for efficient querying.
- **Grid-Based Systems**: Dividing the world into a grid and checking for collisions only within occupied cells.
- **Sweep and Prune**: Sorting objects along one or more axes and checking for overlapping intervals.

### 3. **Narrow Phase Collision Detection**
Once potential collisions are identified in the broad phase, the narrow phase performs more precise checks on the actual shapes of the objects. This involves:
- **Shape Overlap Tests**: Determining if two shapes intersect using mathematical techniques specific to the shapes involved. Common methods include:
  - **Separating Axis Theorem (SAT)**: For convex polygons, this theorem states that two convex shapes do not intersect if there exists a line (axis) where the projections of the two shapes do not overlap.
  - **Circle Collision Tests**: For circles, it’s simply checking if the distance between their centers is less than the sum of their radii.

### 4. **Collision Response**
When a collision is detected, the physics engine calculates the response, which includes:
- **Resolving Penetration**: Adjusting the positions of the colliding objects to prevent them from intersecting.
- **Calculating Forces**: Applying forces based on the type of collision (elastic, inelastic) and the objects' physical properties (mass, restitution).
- **Updating Velocities**: Based on the collision response, the engine updates the velocities of the involved bodies.

### 5. **Continuous Collision Detection (CCD)**
For fast-moving objects, traditional discrete collision detection might miss collisions. CCD techniques ensure that potential collisions are detected even if objects move past each other between frames. This can be done using methods like:
- **Ray Casting**: Casting a ray from the previous position of the object to its current position and checking for intersections along that path.
- **Time of Impact (ToI)**: Calculating the time at which two objects would collide based on their velocities.

### 6. **Collision Events**
Once collisions are detected and resolved, the engine can trigger events, such as:
- **Collision Callbacks**: Notifying game logic about the collision (e.g., playing sound effects, triggering animations).
- **Trigger Zones**: Detecting when an object enters or exits a specified area without necessarily colliding.

### Summary
In summary, a physics engine tracks collisions through a multi-step process that includes defining collision shapes, using broad-phase techniques to quickly identify potential collisions, performing narrow-phase checks for precise intersections, calculating responses to collisions, and managing events related to those collisions. This combination of methods ensures efficient and accurate collision handling, which is essential for realistic physics simulation in games.