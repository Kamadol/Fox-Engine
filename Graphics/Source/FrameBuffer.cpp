#include "FrameBuffer.hpp"

#include <iostream>

#include "GL/glew.h"

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::FrameBuffer(unsigned int xSize, unsigned int ySize)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	
	glGenTextures(1, &m_colorTexture);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xSize, ySize, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, xSize, ySize);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "framebuffer is not complete" << std::endl;
}
FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo);
	glDeleteRenderbuffers(1, &m_rbo);
	glDeleteTextures(1, &m_colorTexture);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, m_colorTexture);
}
void FrameBuffer::unbindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
