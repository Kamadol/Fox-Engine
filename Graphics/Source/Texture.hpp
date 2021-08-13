#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
public:
	Texture();
	bool load(const char* filename);

	void bind();
	void unbind();

private:
	size_t m_id;
	int m_xSize, m_ySize;

};

#endif
