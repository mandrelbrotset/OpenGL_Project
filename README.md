# OpenGL_Project
A 3D graphics program made using OpenGL.

![gl](https://user-images.githubusercontent.com/24194821/47626118-80f33580-daf7-11e8-9f02-2aea399c451e.png)

## Classes
+ __Shader__ - used for loading and compiling shaders
+ __DrawShapes__ - used drawing several shapes

## Class methods
+ __Shader__
  + getCompiledShaders() - returns a struct containing the compiled vertex and fragment shader.

+ __DrawShapes__
  + DrawShapes(const GLchar* vertexShader, const GLchar* fragmentShader)
  + linkProgram() - attaches the vertex and fragment shader to the program
  + use() - attaches the shader to the program
  + setupTriangle() - sets up vertices for a triangle
  + drawTriangle() - draws a triangle
  + setupTexturedRect() - sets up vertices and textures for a rectangle with texture
  + drawTexturedRect() - draws the textured ractangle
  + ~DrawShapes() - deletes
