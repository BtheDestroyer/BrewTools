/******************************************************************************/
/*!
\file graphics.cpp
\author Bryce Dixon
\par email: realbthedestroyer\@gmail.com
\par BrewTools
\date 12/11/2017
\par Created: v1.0
\par Updated: v1.0

\brief
Graphics management and implementation.
*/
/******************************************************************************/
#include "brewtools/distillery.h"
#include "brewtools/trace.h"
#include "brewtools/graphics.h"
#include "brewtools/window.h"
#include "brewtools/macros.h"

#include <iostream>

#ifdef _3DS //The following only exists in a 3DS build
#include <3ds.h>
#elif _WIN32  //The following only exists in a Windows build
static const char *DefaultVSSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in uint aCol;\n"
//"out vec3 color;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"   color = vec4((aCol >> 6 % 256) / 255.0f, (aCol >> 4 % 256) / 255.0f, (aCol >> 2 % 256) / 255.0f, (aCol % 256) / 255.0f);\n"
"}\0";
static const char *DefaultFSSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"in vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"   FragColor = color;\n"
"}\n\0";
#endif

#ifdef _WIN32 //The following only exists in a Windows build
/*****************************************/
/*!
\brief
Framebuffer size callback for GLFW.

\param window
Window pointer.

\param width
Width of viewport.

\param height
Height of viewport.
*/
/*****************************************/
void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  UNREFERENCED_PARAMETER(window);
  glViewport(0, 0, width, height);
}
#endif //_WIN32

/*****************************************/
/*!
\brief
Brewtools namespace.
*/
/*****************************************/
namespace BrewTools
{
  /****************************************************************************/
  /*
  BASIC GEOMETRY
  */
  /****************************************************************************/
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_2d& Graphics::pos_2d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_2d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      default:
      return y;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_3d& Graphics::pos_3d::operator=(pos_3d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_3d& Graphics::pos_3d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_3d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      return y;
      
      case 2:
      default:
      return z;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_4d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_3d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::pos_4d::operator=(pos_2d rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float& Graphics::pos_4d::operator[](unsigned rhs)
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      return y;
      
      case 2:
      return z;
      
      case 3:
      default:
      return w;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  float Graphics::pos_4d::operator[](unsigned rhs) const
  {
    switch (rhs)
    {
      case 0:
      return x;
      
      case 1:
      return y;
      
      case 2:
      return z;
      
      case 3:
      default:
      return w;
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Default constructor (Identity Matrix)
  
  \param scalar
  What to scale the matrix by
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(float scalar)
  {
    for (unsigned i = 0; i < 3; ++i) index[i][i] = scalar;
  }
  
  /*****************************************/
  /*!
  \brief
  Copy constructor
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(const mat_3d& mat)
  {
    for (unsigned i = 0; i < 3; ++i)
    index[i] = mat[i];
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor
  
  \param x1
  Column 1 row 1
  
  \param x2
  Column 1 row 2
  
  \param x3
  Column 1 row 3
  
  \param y1
  Column 2 row 1
  
  \param y2
  Column 2 row 2
  
  \param y3
  Column 2 row 3
  
  \param z1
  Column 3 row 1
  
  \param z2
  Column 3 row 2
  
  \param z3
  Column 3 row 3
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3
  )
  {
    index[0][0] = x1;
    index[0][1] = x2;
    index[0][2] = x3;
    
    index[1][0] = y1;
    index[1][1] = y2;
    index[1][2] = y3;
    
    index[2][0] = z1;
    index[2][1] = z2;
    index[2][2] = z3;
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor
  
  \param c1
  Column 1
  
  \param c2
  Column 2
  
  \param c3
  Column 3
  */
  /*****************************************/
  Graphics::mat_3d::mat_3d(pos_3d c1, pos_3d c2, pos_3d c3)
  {
    index[0] = c1;
    index[1] = c2;
    index[2] = c3;
  }
  
  /*****************************************/
  /*!
  \brief
  Multiplication operator
  
  \param lhs
  Point to multiply
  
  \param rhs
  Matrix to multiply with
  
  \return
  Newly created position
  */
  /*****************************************/
  Graphics::pos_2d operator*(Graphics::pos_2d lhs, Graphics::mat_3d rhs)
  {
    Graphics::pos_2d newpos(rhs[2][0], rhs[2][1]);
    for (unsigned i = 0; i < 2; ++i)
    {
      for (unsigned j = 0; j < 2; ++j)
      {
        newpos[i] += lhs[j] * rhs[j][i];
      }
    }
    return newpos;
  }
  
  /*****************************************/
  /*!
  \brief
  Multiplication operator
  
  \param rhs
  Matrix to multiply with
  
  \return
  Newly created matrix
  */
  /*****************************************/
  Graphics::mat_3d Graphics::mat_3d::operator*(mat_3d rhs)
  {
    mat_3d newmat(0);
    for(unsigned i = 0; i < 3; ++i)
    {
      for (unsigned j = 0; j < 3; ++j)
      {
        for (unsigned k = 0; k < 3; ++k)
        {
          newmat[i][j] += index[i][k] * rhs[k][j];
        }
      }
    }
    return newmat;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Index to retrieve
  
  \return
  Reference to indexed column
  */
  /*****************************************/
  Graphics::pos_3d& Graphics::mat_3d::operator[](unsigned rhs)
  {
    return index[rhs];
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Index to retrieve
  
  \return
  Indexed column
  */
  /*****************************************/
  Graphics::pos_3d Graphics::mat_3d::operator[](unsigned rhs) const
  {
    return index[rhs];
  }
  
  /*****************************************/
  /*!
  \brief
  Default constructor (Identity matrix)
  
  \param scalar
  What to scale the matrix by
  */
  /*****************************************/
  Graphics::mat_4d::mat_4d(float scalar)
  {
    for (unsigned i = 0; i < 4; ++i) index[i][i] = scalar;
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor
  
  \param x1
  Column 1 row 1
  
  \param x2
  Column 1 row 2
  
  \param x3
  Column 1 row 3
  
  \param x4
  Column 1 row 4
  
  \param y1
  Column 2 row 1
  
  \param y2
  Column 2 row 2
  
  \param y3
  Column 2 row 3
  
  \param y4
  Column 2 row 4
  
  \param z1
  Column 3 row 1
  
  \param z2
  Column 3 row 2
  
  \param z3
  Column 3 row 3
  
  \param z4
  Column 3 row 4
  
  \param w1
  Column 4 row 1
  
  \param w2
  Column 4 row 2
  
  \param w3
  Column 4 row 3
  
  \param w4
  Column 4 row 4
  */
  /*****************************************/
  Graphics::mat_4d::mat_4d(
    float x1, float y1, float z1, float w1,
    float x2, float y2, float z2, float w2,
    float x3, float y3, float z3, float w3,
    float x4, float y4, float z4, float w4
  )
  {
    index[0][0] = x1;
    index[0][1] = x2;
    index[0][2] = x3;
    index[0][3] = x4;
    
    index[1][0] = y1;
    index[1][1] = y2;
    index[1][2] = y3;
    index[1][3] = y4;
    
    index[2][0] = z1;
    index[2][1] = z2;
    index[2][2] = z3;
    index[2][3] = z4;
    
    index[3][0] = w1;
    index[3][1] = w2;
    index[3][2] = w3;
    index[3][3] = w4;
  }
  
  /*****************************************/
  /*!
  \brief
  Copy constructor
  
  \param mat
  Matrix to copy from
  */
  /*****************************************/
  Graphics::mat_4d::mat_4d(const mat_4d& mat)
  {
    for (unsigned i = 0; i < 4; ++i)
    for (unsigned j = 0; j < 4; ++j)
    index[i][j] = mat[i][j];
  }
  
  /*****************************************/
  /*!
  \brief
  Constructor
  
  \param c1
  Column 1
  
  \param c2
  Column 2
  
  \param c3
  Column 3
  
  \param c4
  Column 4
  */
  /*****************************************/
  Graphics::mat_4d::mat_4d(pos_4d c1, pos_4d c2, pos_4d c3, pos_4d c4)
  {
    index[0] = c1;
    index[1] = c2;
    index[2] = c3;
    index[3] = c4;
  }
  
  /*****************************************/
  /*!
  \brief
  Multiplication operator
  
  \param lhs
  Point to multiply
  
  \param rhs
  Matrix to multiply with
  
  \return
  Newly created position
  */
  /*****************************************/
  Graphics::pos_2d operator*(Graphics::pos_2d lhs, Graphics::mat_4d rhs)
  {
    Graphics::pos_2d newpos(rhs[2][0], rhs[2][1]);
    for (unsigned i = 0; i < 2; ++i)
    {
      for (unsigned j = 0; j < 2; ++j)
      {
        newpos[i] += lhs[j] * rhs[j][i];
      }
    }
    return newpos;
  }
  
  /*****************************************/
  /*!
  \brief
  Multiplication operator
  
  \param lhs
  Point to multiply
  
  \param rhs
  Matrix to multiply with
  
  \return
  Newly created position
  */
  /*****************************************/
  Graphics::pos_3d operator*(Graphics::pos_3d lhs, Graphics::mat_4d rhs)
  {
    Graphics::pos_3d newpos(rhs[3][0], rhs[3][1], rhs[3][2]);
    for (unsigned i = 0; i < 3; ++i)
    {
      for (unsigned j = 0; j < 3; ++j)
      {
        newpos[i] += lhs[j] * rhs[j][i];
      }
    }
    return newpos;
  }
  
  /*****************************************/
  /*!
  \brief
  Multiplication operator
  
  \param rhs
  Matrix to multiply with
  
  \return
  Newly created matrix
  */
  /*****************************************/
  Graphics::mat_4d Graphics::mat_4d::operator*(Graphics::mat_4d rhs)
  {
    mat_4d newmat(0);
    for(unsigned i = 0; i < 4; ++i)
    {
      for (unsigned j = 0; j < 4; ++j)
      {
        for (unsigned k = 0; k < 4; ++k)
        {
          newmat[i][j] += index[i][k] * rhs[k][j];
        }
      }
    }
    return newmat;
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Index to retrieve
  
  \return
  Indexed column
  */
  /*****************************************/
  Graphics::pos_4d& Graphics::mat_4d::operator[](unsigned rhs)
  {
    return index[rhs];
  }
  
  /*****************************************/
  /*!
  \brief
  Index operator
  
  \param rhs
  Index to retrieve
  
  \return
  Indexed column
  */
  /*****************************************/
  Graphics::pos_4d Graphics::mat_4d::operator[](unsigned rhs) const
  {
    return index[rhs];
  }
  
  /*****************************************/
  /*!
  \brief
  Pure virtual destructor for polymorphism
  */
  /*****************************************/
  Graphics::vertex::~vertex() {}
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified vertex
  */
  /*****************************************/
  Graphics::vertex_col& Graphics::vertex_col::operator=(vertex_col rhs)
  {
    pos = rhs.pos;
    color = rhs.color;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified vertex
  */
  /*****************************************/
  Graphics::vertex_tex& Graphics::vertex_tex::operator=(vertex_tex rhs)
  {
    pos = rhs.pos;
    uv = rhs.uv;
    return *this;
  }
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  
  \return
  Reference to modified texture
  */
  /*****************************************/
  Graphics::texture& Graphics::texture::operator=(texture rhs)
  {
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_TexInit(&tex, rhs.width, rhs.height, rhs.tex.fmt);
    #elif _WIN32 //The following only exists in a Windows build
    //TODO: Figure out windows equivalent
    #endif
    tile = rhs.tile;
    width = rhs.width;
    height = rhs.height;
    return *this;
  }
  
  /****************************************************************************/
  /*
  GENERIC SHAPE
  */
  /****************************************************************************/
  
  // /*****************************************/
  // /*!
  // \brief
  // Assignment operator
  
  // \param rhs
  // Object to the right of the =
  // */
  // /*****************************************/
  // Graphics::Shape& Graphics::Shape::operator=(Shape rhs) {}
  //   position = rhs.position;
  //   rotation = rhs.rotation;
  //   scale = rhs.scale;
  //   if (!tex) tex = new texture;
  //   *tex = *(rhs.tex);
  //   vc_isdirty = true;
  //   vt_isdirty = true;
  //   return *this;
  // }
  
  /*****************************************/
  /*!
  \brief
  Generates the vertices with colors
  */
  /*****************************************/
  bool Graphics::Shape::GenerateColorVertices()
  {
    if (vc_isdirty && vertexcount)
    {
      SAFE_DELETE_ARR(vc);
      vc = new vertex_col[vertexcount];
      mat_3d mat;
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vc[i].color = color[i];
        vc[i].pos = vertex[i];
      }
      return true;
    }
    return false;
  }
  
  /*****************************************/
  /*!
  \brief
  Generates the vertices with texture coordinates
  */
  /*****************************************/
  bool Graphics::Shape::GenerateTextureVertices()
  {
    if (vt_isdirty && vertexcount && tex)
    {
      SAFE_DELETE_ARR(vt);
      vt = new vertex_tex[vertexcount];
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        vt[i].uv = uv[i];
        vt[i].pos = vertex[i];
      }
      return true;
    }
    return false;
  }
  
  /*****************************************/
  /*!
  \brief
  Creates and returns a pointer to an array of color vertices
  
  \return
  Pointer to allocated vertex_col
  */
  /*****************************************/
  const Graphics::vertex_col* Graphics::Shape::GetColorVertices()
  {
    GenerateColorVertices();
    return vc;
  }
  
  /*****************************************/
  /*!
  \brief
  Creates and returns a pointer to an array of texture vertices
  */
  /*****************************************/
  const Graphics::vertex_tex* Graphics::Shape::GetTextureVertices()
  {
    GenerateTextureVertices();
    return vt;
  }
  
  /*****************************************/
  /*!
  \brief
  Default Constructor
  
  \param count
  Number of vertices in the shape
  */
  /*****************************************/
  Graphics::Shape::Shape(unsigned count)
  : vc(NULL), vt(NULL), vc_isdirty(true), vt_isdirty(true), vertexcount(count)
  {
    vertex.resize(count);
    color.resize(count);
    if (!(Engine::Get()->GetSystemIfExists<Graphics>())) return;    
    GenBuffers();
  }
  
  /*****************************************/
  /*!
  \brief
  Buffers everything into the GPU for drawing
  */
  /*****************************************/
  void Graphics::Shape::BufferColor()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    C3D_TexEnv* env = C3D_GetTexEnv(0);
    C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, 0, 0);
    C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
    C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
    
    C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3);
    AttrInfo_AddLoader(attrInfo, 1, GPU_UNSIGNED_BYTE, 4);
    
    C3D_BufInfo* bufInfo = C3D_GetBufInfo();
    BufInfo_Init(bufInfo);
    BufInfo_Add(bufInfo, vertex.data(), sizeof(Graphics::vertex_col), 2, 0x10);
    #elif _WIN32 //The following only exists in a Windows build
    if (!VAO || !VBO || !EBO) GenBuffers();
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(BrewTools::Graphics::pos_3d), vertex.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(unsigned), indice.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BrewTools::Graphics::pos_3d), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Draws the shape to the screen at its current location
  */
  /*****************************************/
  void Graphics::Shape::Draw()
  {
    const vertex_tex *texdraw;
    const vertex_col *coldraw;
    Graphics *g;
    if (!(g = Engine::Get()->GetSystemIfExists<Graphics>())) return;
    if ((texdraw = GetTextureVertices()) != NULL)
    {
      
    }
    else if ((coldraw = GetColorVertices()) != NULL)
    {
      BufferColor();
      #ifdef _3DS //The following only exists in a 3DS build
      C3D_DrawArrays(GPU_TRIANGLES, 0, vertexcount);
      #elif _WIN32 //The following only exists in a Windows build
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, 0);
      
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      #endif
      
      /*std::cout << "Drawing: shaderProgram" <<
      shaderProgram << "\nindice: ";
      for (unsigned i = 0; i < indice.size(); ++i)
      std::cout << indice[i] << ", ";
      std::cout << "\nvertex: ";
      for (unsigned i = 0; i < vertex.size(); ++i)
      std::cout << i << "." << vertex[i][0] << ", " <<
      vertex[i][1] << ", " << vertex[i][2] << std::endl;
      std::cout << "\nVAO: " << VAO << "\nVBO: " << VBO <<
      "\nEBO: " << EBO << std::endl;*/
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Selects a shader for the shape
  
  \param vs
  Vertex shader source code
  
  \param fs
  Fragment shader source code
  
  \return
  Shader Program ID. 0 on failure.
  */
  /*****************************************/
  int Graphics::Shape::LoadShader(const char *vs, const char *fs)
  {
    #ifdef _WIN32 // The following only exists in a Windows build
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vs[0]) glShaderSource(vertexShader, 1, &vs, NULL);
    else glShaderSource(vertexShader, 1, &DefaultVSSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fs[0]) glShaderSource(fragmentShader, 1, &fs, NULL);
    else glShaderSource(fragmentShader, 1, &DefaultFSSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    return shaderProgram;
    #elif _3DS // The following only exists in a 3DS build
    UNREFERENCED_PARAMETER(vs);
    UNREFERENCED_PARAMETER(fs);
    return 0;
    #endif
  }
  
  /****************************************************************************/
  /*
  GRAPHICS SYSTEM
  */
  /****************************************************************************/
  
  /*****************************************/
  /*!
  \brief
  Default Constructor
  */
  /*****************************************/
  Graphics::Graphics()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    gfxInitDefault();
    #elif _WIN32 //The following only exists in a Windows build
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Destructor
  */
  /*****************************************/
  Graphics::~Graphics()
  {
    for (auto it : windows)
    delete it;
    #ifdef _3DS //The following only exists in a 3DS build
    gfxExit();
    #elif _WIN32
    glfwTerminate();
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Updates graphics by flushing and swapping the buffers.
  */
  /*****************************************/
  void Graphics::Update()
  {
    bool selectedinlist(false);
    for (auto it : windows)
    {
      it->Update();
      if (it == currentwindow) selectedinlist = true;
    }
    if (!selectedinlist && currentwindow) currentwindow->Update();
    #ifdef _3DS //The following only exists in a 3DS build
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    #elif _WIN32 //The following only exists in a Windows build
    
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Adds a created window to the list of windows.
  
  \param window
  Pointer to window to add.
  */
  /*****************************************/
  unsigned Graphics::AddWindow(GFXWindow *window)
  {
    if (window->parent)
    ((Graphics*)(window->parent))->RemoveWindow(window);
    window->parent = this;
    windows.push_back(window);
    return windows.size();
  }
  
  /*****************************************/
  /*!
  \brief
  Removes a created window from the list of windows.
  
  \param window
  Pointer to window to remove.
  */
  /*****************************************/
  void Graphics::RemoveWindow(GFXWindow *window)
  {
    auto it = windows.begin();
    for (auto prev = it; it != windows.end(); prev = it++)
    {
      if (*it == window)
      {
        window->parent = NULL;
        windows.erase(it);
        it = prev;
      }
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Selects a given window to be drawn to
  
  \param window
  Pointer to window to select.
  */
  /*****************************************/
  void Graphics::SelectWindow(GFXWindow *window)
  {
    if (currentwindow) currentwindow->selected = false;
    currentwindow = window;
    if (!currentwindow) return;
    currentwindow->selected = true;
    #ifdef _3DS //The following only exists in a 3DS build
    
    #elif _WIN32 //The following only exists in a Windows build
    glfwMakeContextCurrent(currentwindow->GetGLFWWindow());
    #endif
  }
  
  /*****************************************/
  /*!
  \brief
  Selects a given window to be drawn to
  
  \param window
  ID of window to select.
  */
  /*****************************************/
  void Graphics::SelectWindow(unsigned id)
  {
    if (currentwindow) currentwindow->selected = false;
    currentwindow = windows[id];
    if (!currentwindow) return;
    currentwindow->selected = true;
    #ifdef _3DS //The following only exists in a 3DS build
    
    #elif _WIN32 //The following only exists in a Windows build
    glfwMakeContextCurrent(currentwindow->GetGLFWWindow());
    #endif
  }
}
