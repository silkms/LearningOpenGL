//
//  shaderLoading.cpp
//  LearningOpenGL
//
//  Created by Michael  Silk on 8/28/18.
//  Copyright © 2018 Michael  Silk. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"

GLint LoadAndCompileShader(GLuint shaderID, const char* file_path);

GLuint GetShaderProgram(const char * vertex_file_path, const char * frag_file_path)
{
    // build and compile our shader program
    // ------------------------------------
    
    // load and compile the vertex shader
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (LoadAndCompileShader(vertexShaderID, vertex_file_path) == GL_FALSE)
    {
        return 0;
    }
    
    // load and compile the fragment shader
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (LoadAndCompileShader(fragmentShaderID, frag_file_path) == GL_FALSE)
    {
        return 0;
    }
    
    // Link the program
    printf("Linking program\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    
    // Check the program
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }
    
    
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    
    return programID;
}

GLint LoadAndCompileShader(GLuint shaderID, const char* file_path)
{
    // load the shader from the file path
    std::string shaderSource;
    std::ifstream shaderStream(file_path, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderSource = sstr.str();
        shaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
        getchar();
        return GL_FALSE;
    }
    
    printf("Compiling shader : %s\n", file_path);
    char const * sourcePointer = shaderSource.c_str();
    glShaderSource(shaderID, 1, &sourcePointer , NULL);
    glCompileShader(shaderID);
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> shaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }
    
    return result;
}
