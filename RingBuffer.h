#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <vector>
using namespace std;

template<typename T>
class RingBuffer
{
private:
	unsigned long inserted;
	unsigned long maxSize;
	vector<T> backing;
public:
	RingBuffer(int maxSize): inserted(0), maxSize(maxSize), backing(vector<T>(maxSize)) {};

	const vector<T>& getBacking() const;

	void push_back(const T&);
};

template<typename T>
const vector<T>& RingBuffer<T>::getBacking() const
{
	return backing;
}

template<typename T>
void RingBuffer<T>::push_back(const T& element)
{
	backing[inserted++ % maxSize] = element;
}

#endif /* RINGBUFFER_H_ */
