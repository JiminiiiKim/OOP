ReadMe of Project3 - 20202850 Kim jimin

how to compile (including OS type, compiler type/version, compilation method)
OS type : Windows 10
Using Visual Studio 2019 Community
Compiler : Visual C++ 2019

how to execute
1. Turn on Visual Studio 2019.
2. Press Ctrl + F5 or 로컬 Windows 디버거.
3. If you press SPACE bar, the red ball pops out.
4. If you press the left button of the mouse and move the mouse left and right, the white ball moves according to the movement of the mouse.
5. The red ball must hit the yellow ball, and the game is reset when the ball protrudes out.

Summary of my modification
CSphere::hasIntersected(CSphere& ball)
Compare of the distance between 'this' ball and the ball passed by a functional argument and the sum of the radius of two balls

CSphere::hitBy(CSphere& ball)
When a ball passed by a functional argument hits the 'this' ball, the direction is changed by the mathematical formula.
Multiply the current position by the root value of x-velocity*x-velocity/z-velocity*z-velocity.

CWall::hasIntersected(CSphere& ball)
Give additional space for a ball passed by a functional argument.
Check the x-coordinates of the ball are between the top and bottom walls and that the z-coordinates of the ball are between the left and right walls.

CWall::hitBy(CSphere& ball)
When a ball passed by a functional argument crosses between the top and bottom walls, reverse the speed of x to change direction.
And if you cross between left and right walls, reverse the speed of z to change direction.

bool Display(float timeDelta)
It is implemented so that the moving ball moves regardless of the type of PC by using the 'timeDelta' parameter.
Update the target ball and hitBy check if it hit the red ball.
If it hit, send the ball out of the screen.
Check HitBy if the wall hit the red ball.
Update the white ball and Check HitBy if it hit the red ball.
If the ball goes out of the plane, reset the game.
Draw each ball.

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
SPACE : 
Set the position of the red ball and the white ball
Set the isReset variable to false to allow the two balls to move together
MOUSE :
Fix the x and y coordinates and update the new z coordinates to the setCenter as the mouse moves.




