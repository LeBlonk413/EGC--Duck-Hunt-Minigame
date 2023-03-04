The project can be compiled using CMake, setting the build folder as
gfx-framework-master/build.

The duck was created using 1 type of triangle, a circle for the head and eyes
and small rectangles for the eye expressions. 

The score bar is a bigger bar, over which there are smaller bars generated a
few pixels away from each other.

======================
Rules:

- Ducks will appear randomly from the grass on the bottom of the screen.
- They will fly and collide with the screen edges until they are either killed
  or they escape.
- Clicking on a duck kills it and counts as 1 score.
- If the duck isn't killed within 5 seconds, it escapes.
- The player starts with 3 hit points and 3 bullets for each duck. When a duck
escapes or if the player runs out of bullets, he will lose 1 hp.
- After a certain amount of ducks, their flight speed will increase.
- 15 points are required to win the game.
======================