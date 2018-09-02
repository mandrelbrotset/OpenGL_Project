# OpenGL_Project
A 3D graphics program made using OpenGL.

## Classes
..*Shader - used for loading and compiling shaders
..*DrawShapes - used drawing several shapes

## Class methods
..*Shader
....*getCompiledShaders() - returns a struct containing the compiled vertex and fragment shader.

..*DrawShapes
....*DrawShapes(const GLchar* vertexShader, const GLchar* fragmentShader)
....*linkProgram() - attaches the vertex and fragment shader to the program
....*use() - attaches the shader to the program
....*setupTriangle() - sets up vertices for a triangle
....*drawTriangle() - draws a triangle
....*setupTexturedRect() - sets up vertices and textures for a rectangle with texture
....*drawTexturedRect() - draws the textured ractangle
....*~DrawShapes() - deletes 