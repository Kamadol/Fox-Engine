#ifndef FRAME_BUFFER
#define FRAME_BUFFER

class FrameBuffer
{
public:
	FrameBuffer(unsigned int xSize, unsigned int ySize);
	~FrameBuffer();

	void bind() const;
	static void unbind();

	void bindTexture() const;
	void unbindTexture() const;

private:
	unsigned int m_fbo;
	unsigned int m_rbo;
	unsigned int m_colorTexture;

};

#endif

