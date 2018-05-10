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
#include "vshader_shbin.h"
#elif _WIN32 //The following only exists in a Windows build
static const char *DefaultVSSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aCol;\n"
"out vec4 color;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   color = aCol;\n"
"}\n\0";
static const char *DefaultFSSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
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
    red = rhs.r;
    green = rhs.g;
    blue = rhs.b;
    alpha = rhs.a;
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
  
  /*****************************************/
  /*!
  \brief
  Assignment operator
  
  \param rhs
  Object to the right of the =
  */
  /*****************************************/
  Graphics::Shape& Graphics::Shape::operator=(Shape rhs)
  {
    position = rhs.position;
    rotation = rhs.rotation;
    scale = rhs.scale;
    if (!tex) tex = new texture;

    // Copy vertices
    vertc.clear();
    vertt.clear();
    for (auto it : rhs.vertc) vertc.push_back(it);
    for (auto it : rhs.vertt) vertt.push_back(it);

    *tex = *(rhs.tex);
    return *this;
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
  : vertexcount(count), position(0,0,0), rotation(0), scale(1,1), tex(nullptr)
  {
    vertc.resize(count);
    vertt.resize(count);
    for (unsigned i = 0; i < count; ++i) indice.push_back(i);
    if (!(Engine::Get()->GetSystemIfExists<Graphics>())) return;    
  }
  
  /*****************************************/
  /*!
  \brief
  Buffers everything into the GPU for drawing
  */
  /*****************************************/
  void Graphics::Shape::BufferColor()
  {
    vc.resize(vertc.size());
    memcpy(vc.data(), vertc.data(), vertc.size() * sizeof(vertex_col));

    for (unsigned i = 0; i < vc.size(); ++i)
    {
      vc[i].pos.x += position.x;
      vc[i].pos.y += position.y;
      vc[i].pos.z += position.z;
    }

    #ifdef _3DS //The following only exists in a 3DS build
    C3D_ImmDrawBegin(GPU_TRIANGLES);
    for (unsigned i = 0; i < vertc.size(); ++i)
    {
      vertex_col v = ColorVertex(i);

      C3D_ImmSendAttrib(v.pos[0], v.pos[1], v.pos[2], 0.0f); // v0=pos
      C3D_ImmSendAttrib(v.r, v.g, v.b, v.a);                // v1=color
    }
    C3D_ImmDrawEnd();
    #elif _WIN32 //The following only exists in a Windows build
    Graphics *gfx = BrewTools::Engine::Get()->GetSystem<BrewTools::Graphics>();
    unsigned VAO = gfx->GetVAO();
    unsigned VBO = gfx->GetVBO();
    unsigned EBO = gfx->GetEBO();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
      GL_ARRAY_BUFFER,
      vertc.size() * sizeof(vertex_col), vc.data(),
      GL_STATIC_DRAW
    );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      indice.size() * sizeof(unsigned), indice.data(),
      GL_STATIC_DRAW
    );
    
    // There's 4 bytes (1 float) of padding in vertex_col before pos
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE,
      sizeof(vertex_col), (void*)(sizeof(float))
    );
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(
      1, 4, GL_FLOAT, GL_FALSE,
      sizeof(vertex_col), (void*)(sizeof(float) * 4)
    );
    glEnableVertexAttribArray(1);
    
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
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    Graphics *g;
    if (trace) (*trace)[6] << "  Drawing shape...";
    if (!(g = Engine::Get()->GetSystemIfExists<Graphics>())) 
    {
      if (trace) (*trace)[0] << "Couldn't draw! No graphics system!";
      return;
    }
    if (vertt.empty() && vertc.empty())
    {
      if (trace) (*trace)[0] << "Couldn't draw! No color or texture vertices!";
      return;
    }
    if (!vertt.empty())
    {
      if (trace) (*trace)[7] << "    Drawing Textures...";
      // TODO: Draw textures
      if (trace) (*trace)[7] << "    Textures drawn!";
    }
    if (!vertc.empty())
    {
      if (trace) (*trace)[7] << "    Drawing Colors...";
      #ifdef _3DS //The following only exists in a 3DS build
      //if (trace) (*trace)[8] << "      Preparing projection matrix...";
      //C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, g->uLoc_projection, &g->projection);
      #endif
      if (trace) (*trace)[8] << "      Buffering colors...";
      BufferColor();
      #ifdef _WIN32 //The following only exists in a Windows build
      if (trace) (*trace)[8] << "      Selecting program...";
      int shaderProgram = g->GetProgram();
      unsigned VAO = g->GetVAO();
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      if (trace) (*trace)[8] << "      Drawing elements...";
      glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, 0);
      
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      
      // Debugging shaders
      //unsigned VBO = g->GetVBO();
      //unsigned EBO = g->GetEBO();
      //std::cout << "Drawing: shaderProgram" <<
      //shaderProgram << "\nindice: ";
      //for (unsigned i = 0; i < indice.size(); ++i)
      //std::cout << indice[i] << ", ";
      //std::cout << "\nvertex: ";
      //for (unsigned i = 0; i < vertex.size(); ++i)
      //std::cout << "\n(" << vertex[i][0] << ", " <<
      //vertex[i][1] << ", " << vertex[i][2] << ") ";
      //std::cout << "\nvc: " << std::endl;
      //for (unsigned i = 0; i < vertex.size(); ++i)
      //  std::cout << "  " << i << ". " << *(float*)(vc + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " << *(float*)(vc + sizeof(float) * 2 + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " << *(float*)(vc + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " <<
      //    (unsigned)(uint8_t)*(vc + sizeof(float) * 3 + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " << (unsigned)(uint8_t)*(vc + sizeof(float) * 3 + 1 + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " << (unsigned)(uint8_t)*(vc + sizeof(float) * 3 + 2 + i * (sizeof(float) * 3 + sizeof(uint32_t))) << ", " << (unsigned)(uint8_t)*(vc + sizeof(float) * 3 + 3 + i * (sizeof(float) * 3 + sizeof(uint32_t))) << std::endl;
      //std::cout << "\nVAO: " << VAO << "\nVBO: " << VBO <<
      //"\nEBO: " << EBO << std::endl;
      #endif
      if (trace) (*trace)[7] << "    Colors drawn!";
    }
    if (trace) (*trace)[6] << "  Shape drawn!";
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
#ifdef _WIN32 // The following only exists in a Windows build
      : VAO(0), VBO(0), EBO(0), shaderProgram(0), currentwindow(nullptr),
        frameStarted(false)
#elif _3DS // The following will only exist in a 3DS build
      : currentwindow(nullptr), frameStarted(false)
#endif
  {
    BrewTools::Trace *trace =
      BrewTools::Engine::Get()->GetSystemIfExists<BrewTools::Trace>();
    if (trace) (*trace)[5] << "Creating Graphics...";
    #ifdef _3DS //The following only exists in a 3DS build
    if (trace) (*trace)[6] << "  Initializing gfx default...";
    gfxInitDefault();
    //gfxSet3D(false);
    if (trace) (*trace)[6] << "  Initializing C3D...";
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    // TODO: Investigate this. Maybe it should be uncommented
    //C3D_CullFace(GPU_CULL_NONE);
    //C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
    #elif _WIN32 //The following only exists in a Windows build
    if (trace) (*trace)[6] << "  Initializing GLFW...";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif
    if (trace) (*trace)[6] << "  Adding GFXWindow...";
    AddWindow(
      new BrewTools::GFXWindow("BrewTools", Window::Screen::TOP)
    );
    #ifdef _3DS //The following only exists in a 3DS build
    if (trace) (*trace)[6] << "  Running 3DS GFX initialization...";
    Init3DS();
    #endif
    SelectWindow(unsigned(0));
    #ifdef _WIN32 //The following only exists in a Windows build
    if (trace) (*trace)[6] << "  Generating buffers...";
    GenBuffers();
    LoadShader();
    #endif
    if (trace) (*trace)[5] << "Graphics created!";
  }

  /*****************************************/
  /*!
  \brief
  Destructor
  */
  /*****************************************/
  Graphics::~Graphics()
  {
    BrewTools::Trace *trace =
        BrewTools::Engine::Get()->GetSystemIfExists<BrewTools::Trace>();
    if (trace) (*trace)[5] << "Shutting down graphics...";
    for (auto it : windows)
      delete it;
    #ifdef _3DS //The following only exists in a 3DS build
    Exit3DS();
    C3D_Fini();
    gfxExit();
    #elif _WIN32
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    #endif
    if (trace) (*trace)[5] << "Graphics shut down!";
  }

  /*****************************************/
  /*!
  \brief
  Updates graphics by flushing and swapping the buffers.

  TODO: Rewrite this function to look like this:
    1. Call an EndFrame function
    2. Call GFXWindow::EndFrame on all windows
    3. Call GFXWindow::Update on all windows
    4. Call a StartFrame function
    5. Call GFXWindow::StartFrame on all windows
  */
  /*****************************************/
  void Graphics::Update()
  {
    BrewTools::Trace *trace =
        BrewTools::Engine::Get()->GetSystemIfExists<BrewTools::Trace>();
    if (trace)
      (*trace)[6] << "  Updating Graphics...";
    bool selectedinlist(false);
    if (trace)
      (*trace)[7] << "    Updating Windows...";
    for (auto it : windows)
    {
      it->Update();
      if (it == currentwindow) selectedinlist = true;
    }
    if (trace)
      (*trace)[7] << "    Windows updated!";
    if (!selectedinlist && currentwindow)
    {
      if (trace)
        (*trace)[7] << "    Selected window not in the list. Updating it...";
      currentwindow->Update();
      if (trace)
        (*trace)[7] << "    Selected window updated!";
    }

    #ifdef _3DS
    // End the frame if one has been started
    if (frameStarted)
    {
      if (trace)
        (*trace)[7] << "    Ending frame...";
      C3D_FrameEnd(0);
      if (trace)
        (*trace)[7] << "    Frame ended!";
      frameStarted = false;
    }
    else
    {
      if (trace)
        (*trace)[7] << "    Couldn't end frame! None in progress";
    }
    
    // Start a new frame if none are in progress
    if (!frameStarted)
    {
      if (trace)
        (*trace)[7] << "    Starting frame...";
      if (currentwindow)
      {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C3D_FrameDrawOn(currentwindow->GetTarget());
        if (trace)
          (*trace)[7] << "    Frame Started...";
      }
      else
      {
        if (trace)
          (*trace)[7] << "    Couldn't start frame! No currentwindow";
      }
      frameStarted = true;
    }
    else
    {
      if (trace)
        (*trace)[7] << "    Couldn't start frame! One in progress";
    }
    #endif

    if (trace)
      (*trace)[6] << "  Graphics updated!";
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
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    if (trace)
      (*trace)[6] << "  Adding GFXWindow to Graphics...";
    if (window->parent)
    {
      if (trace)
        (*trace)[7] << "    Window has an existing parent. Removing it...";
      ((Graphics*)(window->parent))->RemoveWindow(window);
    }
    if (trace)
      (*trace)[7] << "    Setting parent...";
    window->parent = this;
    windows.push_back(window);
    if (trace)
      (*trace)[6] << "  Window added!";
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
        window->parent = nullptr;
        windows.erase(it);
        it = prev;
      }
    }
  }
  
  /*****************************************/
  /*!
  \brief
  Selects a given window to be drawn to
  
  \param id
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
    if (currentwindow)
    {
      C3D_FrameDrawOn(currentwindow->GetTarget());
      C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
    }
    #elif _WIN32 //The following only exists in a Windows build
    if (currentwindow)
      glfwMakeContextCurrent(currentwindow->GetGLFWWindow());
    #endif
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
    if (currentwindow)
      currentwindow->selected = false;
    currentwindow = window;
    if (currentwindow)
      currentwindow->selected = true;
    #ifdef _3DS //The following only exists in a 3DS build
    if (currentwindow)
      C3D_FrameDrawOn(currentwindow->GetTarget());
    #elif _WIN32 //The following only exists in a Windows build
    if (currentwindow)
      glfwMakeContextCurrent(currentwindow->GetGLFWWindow());
    else
      glfwMakeContextCurrent(0);
    #endif
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
  int Graphics::LoadShader(const char *vs, const char *fs)
  {
    Trace *trace = Engine::Get()->GetSystemIfExists<Trace>();
    #ifdef _WIN32 // The following only exists in a Windows build
    if (trace) (*trace)[5] << "Loading shaders..." << std::endl;
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // If a vertex shader was given, use it as the source
    // If none was given, use the default one
    if (trace) (*trace)[6] << "  Compiling Vertex Shader..." << std::endl;
    if (vs && vs[0]) glShaderSource(vertexShader, 1, &vs, nullptr);
    else glShaderSource(vertexShader, 1, &DefaultVSSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else if (trace) (*trace)[6] << "  Vertex Shader Compiled!" << std::endl;
    if (trace) (*trace)[6] << "  Compiling Fragment Shader..." << std::endl;
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // If a fragment shader was given, use it as the source
    // If none was given, use the default one
    if (fs && fs[0]) glShaderSource(fragmentShader, 1, &fs, nullptr);
    else glShaderSource(fragmentShader, 1, &DefaultFSSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else if (trace) (*trace)[6] << "  Fragment Shader Compiled!" << std::endl;
    if (trace) (*trace)[6] << "  Linking shaders..." << std::endl;
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
      if (trace) (*trace)[0] << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    else if (trace) (*trace)[6] << "  Shaders linked!" << std::endl;
    if (trace) (*trace)[6] << "  Cleaning up..." << std::endl;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    if (trace) (*trace)[5] << "Shaders loaded!" << std::endl;
    return shaderProgram;
    #elif _3DS // The following only exists in a 3DS build
      if (trace)
        (*trace)[5] << "Graphics::LoadShader() only works on Windows";
    return 0;
    #endif
  }
  

  /*****************************************/
  /*!
  \brief
  Initializes the 3DS Shaders
  */
  /*****************************************/
  void Graphics::Init3DS()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    // Load the vertex shader, create a shader program and bind it
    vshader_dvlb = DVLB_ParseFile((u32 *)vshader_shbin, vshader_shbin_size);
    shaderProgramInit(&program);
    shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
    C3D_BindProgram(&program);

    // Get the location of the uniforms
    uLoc_projection = shaderInstanceGetUniformLocation(
      program.vertexShader,
      "projection"
    );

    // Configure attributes for use with the vertex shader
    // Attribute format and element count are ignored in immediate mode
    C3D_AttrInfo *attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
    AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 3); // v1=color

    // Compute the projection matrix
    Mtx_OrthoTilt(&projection, -1.0, 1.0, -1.0, 1.0, 0.0, 1.0, true);

    // Configure the first fragment shading substage to just pass through the vertex color
    // See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
    C3D_TexEnv *env = C3D_GetTexEnv(0);
    C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, 0, 0);
    C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
    C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
    #endif
  }

  /*****************************************/
  /*!
  \brief
  Cleans up the 3DS shaders
  */
  /*****************************************/
  void Graphics::Exit3DS()
  {
    #ifdef _3DS //The following only exists in a 3DS build
    // Free the VBO
    linearFree(vbo_data);

    // Free the shader program
    shaderProgramFree(&program);
    DVLB_Free(vshader_dvlb);
    #endif
  }
  
}
