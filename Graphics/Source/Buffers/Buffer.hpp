#ifndef BUFFER_HPP
#define BUFFER_HPP

class Buffer
{
public:
	Buffer(size_t elementSize, size_t count, const void* data, bool staticDraw = true);
	~Buffer();
	Buffer(Buffer&& other) noexcept;

	void putData(size_t offset, size_t size, const void* data);

	void bind() const;
	void unbind() const;

private:
	unsigned int m_VBO;

};

#endif
