#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

class IndexBuffer
{
public:
	IndexBuffer(const void* data, size_t count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

private:
	size_t m_id;

};

#endif
