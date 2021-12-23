#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

class IndexBuffer
{
public:
	IndexBuffer(size_t count, const void* data, bool staticDraw = true);
	~IndexBuffer();
	IndexBuffer(IndexBuffer&& other) noexcept;

	unsigned int getCount() const;
	void putData(size_t offset, size_t count, const void* data);

	void bind() const;
	void unbind() const;

private:
	unsigned int m_IBO;
	unsigned int m_count;

};

#endif
