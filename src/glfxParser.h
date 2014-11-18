/* Copyright (c) 2011, Max Aizenshtein <max.sniffer@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#pragma once

#include <string>
#include <map>
#include <vector>

#include "glfxClasses.h"

using namespace std;
using namespace glfxParser;

/// Values that represent SamplerParam.
enum SamplerParam
{
    SAMPLER_PARAM_STRING,
    SAMPLER_PARAM_INT,
    SAMPLER_PARAM_FLOAT
};

/// Values that represent RegisterParamType.
enum RegisterParamType
{
    REGISTER_NONE,
    REGISTER_INT,
    REGISTER_NAME
};

//! This is the struct that the parser uses to store data about document elements.
struct glfxstype
{
    glfxstype() {}

    struct variable
	{
        string storage;
        string type;
        string identifier;
        string semantic;
    };

    struct samplerVar
	{
        string  binding;
        string  name;
    };

    union
	{
        int num;
        unsigned unum;
        int lineno;
        float fnum;
        bool boolean;
		Technique *tech;
        Program* prog;
		Sampler* samp; 
		map<string, Program>* passes;
        map<ShaderType, Program::Shader>* shaders;
        vector<variable>* vars;
        vector<samplerVar>* texNames;
    };
    
    union
	{
        SamplerParam	samplerParamType;
        ShaderType		sType;
		ShaderCommand	sCommand;
		RenderState		renderState;
        RegisterParamType rType;
    };

    // Carrying these around is bad luck, or more like bad performance. But whatever...
    string strs[4];
};

namespace glfxParser
{
	extern bool gLexPassthrough;
	extern bool read_shader;
	
	#ifdef LINUX
	int fopen_s(FILE** pFile, const char *filename, const char *mode);
	#endif

}

#define YYSTYPE glfxstype

#if 1
#define YYDEBUG 1
extern int glfxdebug;
#endif

extern string glfxreadblock(unsigned char openChar, unsigned char closeChar);
extern void glfxerror(const char*);
extern int glfxparse();
extern void resetGlfxParse();
extern void glfxWarning(const char* e);
