//
//  shaderLoading.hpp
//  LearningOpenGL
//
//  Created by Michael  Silk on 8/28/18.
//  Copyright © 2018 Michael  Silk. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
    // The program ID
    GLuint ID;
    
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    
    // activate the shader
    void Use();
    void SetBool(const string &name, bool value) const;
    void SetInt(const string &name, int value) const;
    void SetFloat(const string &name, float value) const;
};

#endif /* shader_hpp */
