#ifndef ATLAS_INCLUDE_ATLAS_GL_SHADER_HPP
#define ATLAS_INCLUDE_ATLAS_GL_SHADER_HPP

#pragma once

#include "GL.hpp"

#include <vector>
#include <string>
#include <memory>

namespace atlas
{
    namespace gl
    {
        /**
         *	\class ShaderInfo
         *	\brief Stores all the information for shaders.
         *	
         *	This struct just holds the following data:
         *	\li The type of shader,
         *	\li the handle for the shader,
         *	\li and the source for the shader.
         *	
         *	It is used by the Shader class to store multiple 
         *	shaders in one class instance.
         */
        struct ShaderInfo
        {
            /**
             *	Standard constructor. Initializes the shader type and 
             *	handle to 0.
             */
            ShaderInfo() :
                shaderType(0),
                shaderHandle(0)
            { }

            /**
             *	Initializes the struct with the type and file provided. Note
             *	that this initializes the handle to 0.
             *	
             *	@param[in] type The shader type.
             *	@param[in] name The string containing the shader source.
             */
            ShaderInfo(GLenum type, std::string const& name) :
                shaderType(type),
                shaderFile(name),
                shaderHandle(0)
            { }

            /**
             *	Initializes the shader using the provided struct along with 
             *	the handle. Acts as a pseudo-copy constructor, where just the
             *	shader type and source are copied.
             *	
             *	@param[in] shader The shader whose type and file will be 
             *	copied
             *	@param[in] handle The shader handle.
             */
            ShaderInfo(ShaderInfo const& shader, GLuint handle) :
                shaderType(shader.shaderType),
                shaderFile(shader.shaderFile),
                shaderHandle(handle)
            { }

            ShaderInfo(ShaderInfo const& shader) = default;

            GLenum shaderType;
            std::string shaderFile;
            GLuint shaderHandle;
        };

        /**
         *	\class Shader
         *	\brief Offers an encapsulation for all shader operations.
         *	
         *	This class allows the user to simply specify the shader types
         *	and source files to be created and the class handles the rest.
         *	Unlike other examples, the compilation and linkage of the shaders
         *	was separated to help isolate errors. While this introduces a small
         *	overhead with an extra function call, it is deemed worth it when
         *	trying to isolate where the shader errors are coming from.
         *	
         *	Aside from encapsulating the shader creation and linking, this 
         *	class also handles the shader program, which is created when the
         *	shaders are compiled.
         *	
         *	Once all the shaders are compiled and linked, it is possible to
         *	individually delete shaders if they are not needed anymore, or 
         *	delete all of them at once. Upon destruction, this class will
         *	automatically delete all the shaders, along with the shader
         *	program.
         *	
         *	This class also provides wrappers for typical shader operations, 
         *	such as accessing uniforms, attributes, or binding attributes.
         */
        class Shader
        {
        public:
            /**
             *	Standard constructor.
             */
            Shader();

            /**
             *	Standard copy constructor.
             */
            Shader(Shader const& shader);

            /**
             *	Destructor. Notice that this will destroy not just the shaders,
             *	but the shader program as well.
             */
            ~Shader();

            /**
             * This function does two things: first it creates the 
             * shader program (if it hasn't already) and then it compiles
             * the shaders from source, checking each one for errors. If an
             * error is encountered, everything is cleaned and the message
             * is written to the Log.
             * 
             * \warning
             * Currently, adding new shaders on the fly is not supported,
             * as a result, if this function is called more than once, it
             * will create and compile the provided shaders on the first round,
             * and simply return if called again.
             * 
             * @param[in] shaders The vector of ShaderInfo containing the 
             * shaders to compile.
             */
            void compileShaders(std::vector<ShaderInfo> const& shaders);

            /**
             *	As explained before, the linkage of shaders was separated to
             *	help in isolating errors. As a result, after calling
             *	compileShaders, it is necessary to follow that with a call
             *	to linkShaders. After this, the shaders are fully linked and
             *	ready to be used. If an error occurs, everything is destroyed
             *	and an error is written to the Log.
             */
            void linkShaders();

            /**
             *	Deletes all the shaders stored by the class along with the
             *	shader program. This is also called by the destructor.
             */
            void deleteShaders();

            /**
             *	Wraps around the glBindAttribLocation function. If the
             *	shader program hasn't been created, or it is invalid, the
             *	function writes an error to the Log and returns.
             *	
             *	\warning
             *	This function does not check the OpenGL error queue for errors
             *	after attempting to bind the attribute location.
             *	
             *	@param[in] location The attribute location.
             *	@param[in] name The name of the attribute to bind.
             */
            void bindAttribute(GLuint location, std::string const& name) const;

            /**
             *	Wraps around the glUseProgram function call. If the
             *	shader program hasn't been created, or it is invalid, the
             *	function writes an error to the log and returns.
             */
            void enableShaders() const;

            /**
             *	Equivalent to glUseProgram(0). This deactivates the current
             *	shader program.
             */
            void disableShaders() const;

            /**
             *	Returns the current shader program.
             */
            GLint getShaderProgram() const;

            /**
             *	Gets the specified uniform variable. If the shader program is
             *	invalid or if the uniform location doesn't exist, the function
             *	returns -1 and outputs the error to the Log.
             *	
             *	@param[in] name The name of the uniform variable.
             *	@return The uniform location if it exists, -1 otherwise.
             */
            GLint getUniformVariable(std::string const& name) const;

            /**
             *	Gets the specified attribute variable. If the shade program
             *	is invalid or if the uniform location doesn't exist, the
             *	function returns -1 and outputs the error to the Log.
             *	
             *	@param[in] name The name of the attribute variable.
             *	@return The attribute location if it exists, -1 otherwise.
             */
            GLint getAttributeVariable(std::string const& name) const;

        private:
            struct GLShaderImpl;
            std::unique_ptr<GLShaderImpl> mImpl;
        };
    }
}

#endif
