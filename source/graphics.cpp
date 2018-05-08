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
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
    *tex = *(rhs.tex);
    vc_isdirty = true;
    vt_isdirty = true;
    return *this;
  }
  
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
      const unsigned s = (sizeof(float) * 3 + sizeof(uint32_t));
      vc = new char[s * vertexcount];
      mat_3d mat;
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        *(float*)(vc + i * s + sizeof(float) * 0) = vertex[i][0];
        *(float*)(vc + i * s + sizeof(float) * 1) = vertex[i][1];
        *(float*)(vc + i * s + sizeof(float) * 2) = vertex[i][2];
        *(uint32_t*)(vc + i * s + sizeof(float) * 3) = color[i];
      }
      vc_isdirty = false;
      return true;
    }
    else if (vertexcount > 0) return true;
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
      const unsigned s = (sizeof(float) * 5);
      vt = new char[s * vertexcount];
      for (unsigned i = 0; i < vertexcount; ++i)
      {
        *(float*)(vt + i * s + sizeof(float) * 0) = vertex[i][0];
        *(float*)(vt + i * s + sizeof(float) * 1) = vertex[i][1];
        *(float*)(vt + i * s + sizeof(float) * 2) = vertex[i][2];
        *(float*)(vt + i * s + sizeof(float) * 3) = uv[i][0];
        *(float*)(vt + i * s + sizeof(float) * 4) = uv[i][1];
      }
      vt_isdirty = false;
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
  const char* Graphics::Shape::GetColorVertices()
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
  const char* Graphics::Shape::GetTextureVertices()
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
  : vc(nullptr), vt(nullptr), vc_isdirty(true), vt_isdirty(true), vertexcount(count),
  position(0,0), rotation(0), scale(1,1), tex(nullptr)
  {
    vertex.resize(count);
    color.resize(count);
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
    BufInfo_Add(bufInfo, vc, sizeof(Graphics::vertex_col), 2, 0x10);
    #elif _WIN32 //The following only exists in a Windows build
    Graphics *gfx = BrewTools::Engine::Get()->GetSystem<BrewTools::Graphics>();
    unsigned VAO = gfx->GetVAO();
    unsigned VBO = gfx->GetVBO();
    unsigned EBO = gfx->GetEBO();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * (sizeof(float) * 3 + sizeof(uint32_t)), vc, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(unsigned), indice.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(uint32_t), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(float) * 3 + sizeof(uint32_t), (void*)(sizeof(float) * 3));
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
    if (trace) (*trace)[5] << "Drawing shape...";
    if (!(g = Engine::Get()->GetSystemIfExists<Graphics>())) 
    {
      if (trace) (*trace)[0] << "Couldn't draw! No graphics system!";
      return;
    }
    if (!GetTextureVertices() && !GetColorVertices())
    {
      if (trace) (*trace)[0] << "Couldn't draw! No color or texture vertices!";
      return;
    }
    else if (GetTextureVertices())
    {
      if (trace) (*trace)[6] << "  Drawing Textures...";
      // TODO: Draw textures
      if (trace) (*trace)[6] << "  Textures drawn!";
    }
    else if (GetColorVertices())
    {
      if (trace) (*trace)[6] << "  Drawing Colors...";
      if (trace) (*trace)[7] << "    Buffering colors...";
      BufferColor();
      #ifdef _3DS //The following only exists in a 3DS build
      if (trace) (*trace)[7] << "    Drawing array...";
      C3D_DrawArrays(GPU_TRIANGLES, 0, vertexcount);
      if (trace) (*trace)[7] << "  Array drawn!";
      #elif _WIN32 //The following only exists in a Windows build
      if (trace) (*trace)[7] << "    Selecting program...";
      int shaderProgram = g->GetProgram();
      unsigned VAO = g->GetVAO();
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      if (trace) (*trace)[7] << "    Drawing elements...";
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
      vc_isdirty = true;
      vt_isdirty = true;
      if (trace) (*trace)[6] << "  Colors drawn!";
    }
    if (trace) (*trace)[5] << "Shape drawn!";
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
    : VAO(0), VBO(0), EBO(0), shaderProgram(0), currentwindow(nullptr)
  #elif _3DS // The following will only exist in a 3DS build
    : currentwindow(nullptr)
  #endif
  {
    BrewTools::Trace *trace =
      BrewTools::Engine::Get()->GetSystem<BrewTools::Trace>();
    (*trace)[5] << "Creating Graphics...";
    #ifdef _3DS //The following only exists in a 3DS build
    (*trace)[6] << "  Initializing gfx default...";
    gfxInitDefault();
    //gfxSet3D(false);
    (*trace)[6] << "  Initializing C3D...";
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    C3D_CullFace(GPU_CULL_NONE);
    C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
    #elif _WIN32 //The following only exists in a Windows build
    (*trace)[6] << "  Initializing GLFW...";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif
    (*trace)[6] << "  Adding GFXWindow...";
    AddWindow(
      new BrewTools::GFXWindow("BrewTools", Window::Screen::TOP)
    );
    #ifdef _3DS //The following only exists in a 3DS build
    (*trace)[6] << "  Running 3DS GFX initialization...";
    Init3DS();
    #endif
    SelectWindow(unsigned(0));
    #ifdef _WIN32 //The following only exists in a Windows build
    (*trace)[6] << "  Generating buffers...";
    GenBuffers();
    LoadShader();
    #endif
    (*trace)[5] << "Graphics created!";
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
        BrewTools::Engine::Get()->GetSystem<BrewTools::Trace>();
    if (trace)
      (*trace)[5] << "Shutting down graphics...";
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
    if (trace)
      (*trace)[5] << "Graphics shut down!";
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
      it->Update(frameStarted);
      if (it == currentwindow) selectedinlist = true;
    }
    if (!selectedinlist && currentwindow) currentwindow->Update(frameStarted);
    #ifdef _3DS //The following only exists in a 3DS build
    // End old frame if one exists
    if (frameStarted)
    {
      gfxFlushBuffers();
      gfxSwapBuffers();
      gspWaitForVBlank();
      vbo_index = 0;
    }

    // Start new frame
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    C3D_FrameDrawOn(target);

    // Update the uniforms
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
    #elif _WIN32 //The following only exists in a Windows build
    
    #endif
    frameStarted = true;
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
      C3D_FrameDrawOn(currentwindow->GetTarget());
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
