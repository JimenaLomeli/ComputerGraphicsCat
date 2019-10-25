//
//  main.cpp
//  Challenge2
//
// Ana Jimena Lomeli Cantu - A00818665
// Eduardo Enrique Trujillo Ramos - A01187313
// Samuel Pacheco - A01039815
//
// Code taken from: github.com/opengl-tutorials/ogl
//
// ---------------------------
// Libraries
// ---------------------------
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "shader.hpp"


// ---------------------------
// Transformations made by us
// ---------------------------

void translate(float dx, float dy, float dz, GLfloat matrix[]) {
  for (int i = 0; i < 876; i++) {
    matrix[i*3] += dx;
    matrix[i*3+1] += dy;
    matrix[i*3+2] += dz;
  }
}

void scale(float sx, float sy, float sz, GLfloat matrix[]) {
  for (int i = 0; i < 876; i++) {
    matrix[i*3] *= sx;
    matrix[i*3+1] *= sy;
    matrix[i*3+2] *= sz;
  }
}

void rotateX(float angle, GLfloat matrix[]) {
  for (int i = 0; i < 876; i++) {
    float y = matrix[i*3+1];
    float z = matrix[i*3+2];
    y = matrix[i*3+1]*cos(angle*M_PI/180.0) - matrix[i*3+2]*sin(angle*M_PI/180.0);
    z = matrix[i*3+2]*cos(angle*M_PI/180.0) + matrix[i*3+1]*sin(angle*M_PI/180.0);
    
    matrix[i*3+2] = z;
    matrix[i*3+1] = y;
  }
}

void rotateY(float angle, GLfloat matrix[]) {
  for (int i = 0; i < 876; i++) {
    float x = matrix[i*3];
    float z = matrix[i*3+2];
    z = matrix[i*3+2]*cos(angle*M_PI/180.0) - matrix[i*3]*sin(angle*M_PI/180.0);
    x = matrix[i*3]*cos(angle*M_PI/180.0) + matrix[i*3+2]*sin(angle*M_PI/180.0);
    
    matrix[i*3] = x;
    matrix[i*3+2] = z;
  }
}


void rotateZ(float angle, GLfloat matrix[]) {
  for (int i = 0; i < 876; i++) {
    float x = matrix[i*3];
    float y = matrix[i*3+1];
    x = matrix[i*3]*cos(angle*M_PI/180.0) - matrix[i*3+1]*sin(angle*M_PI/180.0);
    y = matrix[i*3+1]*cos(angle*M_PI/180.0) + matrix[i*3]*sin(angle*M_PI/180.0);
    
    matrix[i*3] = x;
    matrix[i*3+1] = y;
  }
}

// ----------------------------
// Keyboard control made by us
// ----------------------------

char operation = 't', axis = 'x';

void controlModel(GLfloat matrix[]) {
  if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
    operation = 't';
  }
  if (glfwGetKey( window, GLFW_KEY_R ) == GLFW_PRESS) {
    operation = 'r';
  }
  if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS) {
    operation = 's';
  }
  if (glfwGetKey( window, GLFW_KEY_X ) == GLFW_PRESS) {
    axis = 'x';
  }
  if (glfwGetKey( window, GLFW_KEY_Y ) == GLFW_PRESS) {
    axis = 'y';
  }
  if (glfwGetKey( window, GLFW_KEY_Z ) == GLFW_PRESS) {
    axis = 'z';
  }
  // Move up
  if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
    float dx, dy, dz;
    if (operation == 't') {
      if (axis == 'x') {
        dx = 0.01;
        dy = 0;
        dz = 0;
      } else if (axis == 'y') {
        dx = 0;
        dy = 0.01;
        dz = 0;
      } else if (axis == 'z') {
        dx = 0;
        dy = 0;
        dz = 0.01;
      }
      translate(dx, dy, dz, matrix);
    } else if (operation == 'r') {
      if (axis == 'x') {
        rotateX(1, matrix);
      } else if (axis == 'y') {
        rotateY(1, matrix);
      } else if (axis == 'z') {
        rotateZ(1, matrix);
      }
    } else if (operation == 's') {
      if (axis == 'x') {
        dx = 1.01;
        dy = 1;
        dz = 1;
      } else if (axis == 'y') {
        dx = 1;
        dy = 1.01;
        dz = 1;
      } else if (axis == 'z') {
        dx = 1;
        dy = 1;
        dz = 1.01;
      }
      scale(dx, dy, dz, matrix);
    }
  }
  // Move down
  if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
    float dx, dy, dz;
    if (operation == 't') {
      if (axis == 'x') {
        dx = 0.01;
        dy = 0;
        dz = 0;
      } else if (axis == 'y') {
        dx = 0;
        dy = 0.01;
        dz = 0;
      } else if (axis == 'z') {
        dx = 0;
        dy = 0;
        dz = 0.01;
      }
      translate(-dx, -dy, -dz, matrix);
    } else if (operation == 'r') {
      if (axis == 'x') {
        rotateX(-1, matrix);
      } else if (axis == 'y') {
        rotateY(-1, matrix);
      } else if (axis == 'z') {
        rotateZ(-1, matrix);
      }
    } else if (operation == 's') {
      if (axis == 'x') {
        dx = 1.01;
        dy = 1;
        dz = 1;
      } else if (axis == 'y') {
        dx = 1;
        dy = 1.01;
        dz = 1;
      } else if (axis == 'z') {
        dx = 1;
        dy = 1;
        dz = 1.01;
      }
      scale(2-dx, 2-dy, 2-dz, matrix);
    }
  }
}


// ----------------------------
// Code taken from tutorial
// ----------------------------
int main( void )
{
  // Initialise GLFW
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }
  
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
  
  // Open a window and create its OpenGL context
  window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  
  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );
  
  // Get a handle for our "MVP" uniform
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  
  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  // Or, for an ortho camera :
  //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
  
  // Camera matrix
  glm::mat4 View       = glm::lookAt(
                                     glm::vec3(6,1,8), // Camera is at (4,3,3), in World Space
                                     glm::vec3(0,0,0), // and looks at the origin
                                     glm::vec3(0,3,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                     );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model      = glm::mat4(1.0f);
  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
  
// ----------------------------------------------------------
// Developed Code
// ----------------------------------------------------------
  
  GLfloat g_vertex_buffer_data[3*876] = {
  };
  
  std::ifstream catvertices;
  catvertices.open("cat_vertices.txt");
  for(int i = 0; i < 3*876; i++) {
    catvertices >> g_vertex_buffer_data[i];
  }
  
  
// ------------------------ Rotate ----------------------------
  
  float angle = 0;
  rotateZ(angle, g_vertex_buffer_data);
  

  // ------------------------ Scale ---------------------------
  
  float sx = 0.5, sy = 0.5, sz = 0.5;
  scale(sx, sy, sz, g_vertex_buffer_data);
  
  
  // ------------------------ Translate -----------------------
  
  float dx = 0, dy = 0, dz = 0;
  translate(dx, dy, dz, g_vertex_buffer_data);
    
  // ----------------------------------------------------------
  // Code taken from tutorial
  // ----------------------------------------------------------
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  
  do{
    controlModel(g_vertex_buffer_data);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Use our shader
    glUseProgram(programID);
    
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 1000); // 3 indices starting at 0 -> 1 triangle
    
    glDisableVertexAttribArray(0);
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );
  
  // Cleanup VBO and shader
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);
  
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  
  return 0;
}

