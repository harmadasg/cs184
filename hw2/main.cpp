/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glut.h>
#include "shaders.h"
#include "Transform.h"

using namespace std; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp  
void display(void);  // prototype for display function.  

// Uses the Projection matrices (technically deprecated) to set perspective 
// We could also do this in a more modern fashion with glm.  
void reshape(int width, int height){
	w = width;
	h = height;
        mat4 mv; // just like for lookat

	glMatrixMode(GL_PROJECTION);
        float aspect = w / (float) h, zNear = 0.1, zFar = 99.0;
        // I am changing the projection stuff to be consistent with lookat
        if (true) mv = glm::perspective(glm::radians(fovy),aspect,zNear,zFar); 
        else {
          mv = Transform::perspective(fovy,aspect,zNear,zFar); 
          mv = glm::transpose(mv); // accounting for row major 
        }
        glLoadMatrixf(&mv[0][0]); 

	glViewport(0, 0, w, h);
}

void printHelp() {
  std::cout << "\npress 'h' to print this message again.\n" 
       << "press '+' or '-' to change the amount of rotation that\noccurs with each arrow press.\n" 
            << "press 'g' to switch between using glm::lookAt and glm::Perspective or your own LookAt.\n"       
            << "press 'r' to reset the transformations.\n"
            << "press 'v' 't' 's' to do view [default], translate, scale.\n"
            << "press ESC to quit.\n";      
}


void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case '+':
		amount++;
		std::cout << "amount set to " << amount << "\n";
		break;
	case '-':
		amount--;
		std::cout << "amount set to " << amount << "\n"; 
		break;
	case 'g':
		useGlu = !useGlu;
                reshape(w,h); 
		std::cout << "Using glm::LookAt and glm::Perspective set to: " << (useGlu ? " true " : " false ") << "\n"; 
		break;
	case 'h':
		printHelp();
		break;
        case 27:  // Escape to quit
                exit(0);
                break;
        case 'r': // reset eye and up vectors, scale and translate. 
		eye = eyeinit; 
		up = upinit; 
                sx = sy = 1.0; 
                tx = ty = 0.0; 
		break;   
        case 'v': 
                transop = view;
                std::cout << "Operation is set to View\n"; 
                break; 
        case 't':
                transop = translate; 
                std::cout << "Operation is set to Translate\n"; 
                break; 
        case 's':
                transop = scale; 
                std::cout << "Operation is set to Scale\n"; 
                break; 
        }
	glutPostRedisplay();
}

//  You will need to enter code for the arrow keys 
//  When an arrow key is pressed, it will call your transform functions

void specialKey(int key, int x, int y) {
	switch(key) {
	case 100: //left
          if (transop == view) Transform::left(amount, eye,  up);
          else if (transop == scale) sx -= amount * 0.01; 
          else if (transop == translate) tx -= amount * 0.01; 
          break;
	case 101: //up
          if (transop == view) Transform::up(amount,  eye,  up);
          else if (transop == scale) sy += amount * 0.01; 
          else if (transop == translate) ty += amount * 0.01; 
          break;
	case 102: //right
          if (transop == view) Transform::left(-amount, eye,  up);
          else if (transop == scale) sx += amount * 0.01; 
          else if (transop == translate) tx += amount * 0.01; 
          break;
	case 103: //down
          if (transop == view) Transform::up(-amount,  eye,  up);
          else if (transop == scale) sy -= amount * 0.01; 
          else if (transop == translate) ty -= amount * 0.01; 
          break;
	}
	glutPostRedisplay();
}

void init() {
      // Initialize shaders
      vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl");
      fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl");
      shaderprogram = initprogram(vertexshader, fragmentshader); 
      enablelighting = glGetUniformLocation(shaderprogram,"enablelighting");
      lightpos = glGetUniformLocation(shaderprogram,"lightposn");       
      lightcol = glGetUniformLocation(shaderprogram,"lightcolor");       
      numusedcol = glGetUniformLocation(shaderprogram,"numused");       
      ambientcol = glGetUniformLocation(shaderprogram,"ambient");       
      diffusecol = glGetUniformLocation(shaderprogram,"diffuse");       
      specularcol = glGetUniformLocation(shaderprogram,"specular");       
      emissioncol = glGetUniformLocation(shaderprogram,"emission");       
      shininesscol = glGetUniformLocation(shaderprogram,"shininess");       
}


int main(int argc, char* argv[]) {

	if (argc < 2) {
		cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
		exit(-1); 
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW2: Scene Viewer");
	init();
        readfile(argv[1]); 
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(w, h);

	printHelp();
	glutMainLoop();
	return 0;
}
