//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// ProgramGL.h: Defines the class interface for ProgramGL.

#ifndef LIBANGLE_RENDERER_GL_PROGRAMGL_H_
#define LIBANGLE_RENDERER_GL_PROGRAMGL_H_

#include "libANGLE/renderer/ProgramImpl.h"

namespace rx
{

class FunctionsGL;
class StateManagerGL;

struct SamplerBindingGL
{
    GLenum textureType;
    std::vector<GLuint> boundTextureUnits;
};

class ProgramGL : public ProgramImpl
{
  public:
    ProgramGL(const gl::Program::Data &data,
              const FunctionsGL *functions,
              StateManagerGL *stateManager);
    ~ProgramGL() override;

    int getShaderVersion() const override;

    GLenum getBinaryFormat() override;
    LinkResult load(gl::InfoLog &infoLog, gl::BinaryInputStream *stream) override;
    gl::Error save(gl::BinaryOutputStream *stream) override;

    LinkResult link(const gl::Data &data,
                    gl::InfoLog &infoLog,
                    gl::Shader *fragmentShader,
                    gl::Shader *vertexShader) override;

    GLboolean validate(const gl::Caps &caps, gl::InfoLog *infoLog) override;

    void setUniform1fv(GLint location, GLsizei count, const GLfloat *v) override;
    void setUniform2fv(GLint location, GLsizei count, const GLfloat *v) override;
    void setUniform3fv(GLint location, GLsizei count, const GLfloat *v) override;
    void setUniform4fv(GLint location, GLsizei count, const GLfloat *v) override;
    void setUniform1iv(GLint location, GLsizei count, const GLint *v) override;
    void setUniform2iv(GLint location, GLsizei count, const GLint *v) override;
    void setUniform3iv(GLint location, GLsizei count, const GLint *v) override;
    void setUniform4iv(GLint location, GLsizei count, const GLint *v) override;
    void setUniform1uiv(GLint location, GLsizei count, const GLuint *v) override;
    void setUniform2uiv(GLint location, GLsizei count, const GLuint *v) override;
    void setUniform3uiv(GLint location, GLsizei count, const GLuint *v) override;
    void setUniform4uiv(GLint location, GLsizei count, const GLuint *v) override;
    void setUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void setUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;

    void getUniformfv(GLint location, GLfloat *params) override;
    void getUniformiv(GLint location, GLint *params) override;
    void getUniformuiv(GLint location, GLuint *params) override;

    bool validateSamplers(gl::InfoLog *infoLog, const gl::Caps &caps) override;

    void reset() override;

    GLuint getProgramID() const;
    const std::vector<SamplerBindingGL> &getAppliedSamplerUniforms() const;

  private:
    const FunctionsGL *mFunctions;
    StateManagerGL *mStateManager;

    // A map from uniform location to index of mSamplerBindings and array index of the uniform
    struct SamplerLocation
    {
        size_t samplerIndex;
        size_t arrayIndex;
    };
    std::map<GLint, SamplerLocation> mSamplerUniformMap;

    // An array of the samplers that are used by the program
    std::vector<SamplerBindingGL> mSamplerBindings;

    GLuint mProgramID;
};

}

#endif // LIBANGLE_RENDERER_GL_PROGRAMGL_H_
