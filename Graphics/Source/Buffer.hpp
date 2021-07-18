#ifndef BUFFER_HPP
#define BUFFER_HPP

class Buffer
{
public:
	Buffer(const void* data, size_t size);
	~Buffer();

	void bind() const;
	void unbind() const;

private:
	size_t m_id;

};

#endif
