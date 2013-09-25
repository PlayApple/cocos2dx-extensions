//
//  EXGrayUtility.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-9-24.
//
//

#include "EXGrayUtility.h"

void EXGrayUtility::disableGray(CCSprite* sp)
{
    const GLchar* pszFragSource =
    "#ifdef GL_ES \n \
    precision mediump float; \n \
    #endif \n \
    uniform sampler2D u_texture; \n \
    varying vec2 v_texCoord; \n \
    varying vec4 v_fragmentColor; \n \
    void main(void) \n \
    { \n \
    // Convert to greyscale using NTSC weightings \n \
    vec4 col = texture2D(u_texture, v_texCoord); \n \
    gl_FragColor = vec4(col.r, col.g, col.b, col.a); \n \
    }";
    
    CCGLProgram* pProgram = new CCGLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
    sp->setShaderProgram(pProgram);
    pProgram->release();
    
    sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
    sp->getShaderProgram()->link();
    sp->getShaderProgram()->updateUniforms();
}

void EXGrayUtility::enableGray(CCSprite* sp)
{
    const GLchar* pszFragSource =
    "#ifdef GL_ES \n \
    precision mediump float; \n \
    #endif \n \
    uniform sampler2D u_texture; \n \
    varying vec2 v_texCoord; \n \
    varying vec4 v_fragmentColor; \n \
    void main(void) \n \
    { \n \
    // Convert to greyscale using NTSC weightings \n \
    vec4 col = texture2D(u_texture, v_texCoord); \n \
    float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
    gl_FragColor = vec4(grey, grey, grey, col.a); \n \
    }";
    
    CCGLProgram* pProgram = new CCGLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
    sp->setShaderProgram(pProgram);
    pProgram->release();
    
    sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
    sp->getShaderProgram()->link();
    sp->getShaderProgram()->updateUniforms();
}