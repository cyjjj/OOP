#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include<new> //placement new
#include<cstddef> //ptrdiff_t size_t
#include<iostream>
//分配内存

#define BUFFER_SIZE 1024
using namespace std;

template <typename T>
struct Block {
	Block *next;
};

template <typename T>
class Buffer
{
private:
	//blocksize至少要能装下Block信息
	static const size_t blockSize = sizeof(T);
	unsigned char* data = new unsigned char[blockSize * BUFFER_SIZE];//开辟一个buffer的空间
	Buffer * next;

public:
	Buffer() = default;//构造函数
	Buffer * getNext() const{return next;}
	void setNext(Buffer *p) { next = p; }
	T *getBlock(size_t index)	{//获取index处block对应指针
		return reinterpret_cast<T *>(data + blockSize * index);
	}
};

template <typename T>
class MemoryPool
{
private:
	Buffer<T> *HeadBuffer = new Buffer<T>;//锚点
	Buffer<T> *curBuffer = NULL;
	size_t bufferedBlocks = BUFFER_SIZE;
	Block<T> * firstFreeBlock;//串联自由的内存
	Block<T> * bigMem;//串联大于Buffer大小的内存

public:
	MemoryPool(){
		HeadBuffer->setNext(NULL);
		firstFreeBlock = NULL;
	}
	//仅支持无参数构造函数
	MemoryPool(MemoryPool &&memoryPool) = delete;
	MemoryPool(const MemoryPool &memoryPool) = delete;
	MemoryPool operator =(MemoryPool &&memoryPool) = delete;
	MemoryPool operator =(const MemoryPool &memoryPool) = delete;

	~MemoryPool()
	{
		//释放所有Buffer
		while (HeadBuffer) {
			Buffer<T> *buffer = HeadBuffer;
			HeadBuffer = buffer->getNext();
			delete buffer;
		}
		//释放超出Buffer大小的大内存
		while (bigMem)
		{
			T* temp = reinterpret_cast<T *>(bigMem);
			bigMem = bigMem->next;
			::operator delete(temp);
		}
	}

	T *allocate(size_t n)
	{
		if (n == 1)
		{
			if (firstFreeBlock) {
				Block<T> *block = firstFreeBlock;
				firstFreeBlock = block->next;
				return reinterpret_cast<T *>(block);
			}

			if (bufferedBlocks + n >= BUFFER_SIZE) {//若多分配1个超出容量（BUFFER_SIZE是容量，bufferedBlocks从0开始，是索引）
				Buffer<T>*p = new Buffer<T>;
				p->setNext(HeadBuffer->getNext());
				HeadBuffer->setNext(p);
				curBuffer = p;
				bufferedBlocks = 0;
			}

			return curBuffer->getBlock(bufferedBlocks++);
		}	
		else
		{
			//若n比Buffer大小还大，那么使用内存池无疑是不划算的，大内存使用new/delete更为划算可靠
			if (n > BUFFER_SIZE)
			{
				T* temp = (T*)::operator new (sizeof(T)*n);
				Block<T> * block = reinterpret_cast<Block<T> *>(temp);
				block->next = bigMem;
				bigMem = block;
				return temp;
			}
			
			if (bufferedBlocks + n >= BUFFER_SIZE) {//若多分配n个超出容量（BUFFER_SIZE是容量，bufferedBlocks从0开始，是索引）
				Buffer<T>*p = new Buffer<T>;
				p->setNext(HeadBuffer->getNext());
				HeadBuffer->setNext(p);
				//该buffer中不足n的剩余块挂到freeBlock上
				int i = bufferedBlocks;
				while (i < BUFFER_SIZE)
				{
					Block<T> * temp = reinterpret_cast<Block<T> *>(curBuffer->getBlock(i));
					temp->next = firstFreeBlock;
					firstFreeBlock = temp;
					i++;
				}
				//更换Buffer
				curBuffer = p;
				bufferedBlocks = 0;
			}

			bufferedBlocks += n;
			return curBuffer->getBlock(bufferedBlocks-n);
		}
	}

	void deallocate(T *pointer)
	{
		//将归还的内存直接挂到freeBlock上，由于未知大小，放弃除第一个block外的内存碎片		
		Block<T> *block = reinterpret_cast<Block<T> *>(pointer);
		block->next = firstFreeBlock;
		firstFreeBlock = block;
		//（哪怕存储信息，分配后也会因为内存被使用而被覆盖，
		//同时另辟空间存储信息也会浪费空间，而且众多处理操作也会降低速度）
	}
};

template<typename T>
class MyAllocate {
private:
	//分开处理MyAllocate、copyMyAllocate、rebindMyAllocate
	MyAllocate *copyMyAllocate = NULL;
	allocator<T> *rebindMyAllocate = NULL;
	MemoryPool<T> MP;//定义内存池
public:
	//型别定义
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template<class U>
	struct rebind {
		typedef MyAllocate<U> other;
	};

	MyAllocate() = default;
	MyAllocate(MyAllocate &allocator) :	copyMyAllocate(&allocator){}
	template <class U>
	MyAllocate(const MyAllocate<U> &other)
	{
		if (!std::is_same<T, U>::value)
			rebindMyAllocate = new allocator<T>();
	}
	~MyAllocate(){
		delete copyMyAllocate;
		delete rebindMyAllocate;
	}

	pointer allocate(size_type n, const void *hint = 0)
	{
		if (copyMyAllocate)
			return copyMyAllocate->allocate(n, hint);
		if (rebindMyAllocate)
			return rebindMyAllocate->allocate(n, hint);
		/*
			if (n != 1 || hint)
			throw std::bad_alloc();		*/
		//待修改
		T* temp =  MP.allocate(n);
		//T* temp = (T*)(::operator new((size_t)(sizeof(T))));
		return temp;
	}

	void deallocate(pointer p, size_type n)
	{
		if (copyMyAllocate) {
			copyMyAllocate->deallocate(p, n);
			return;
		}
		if (rebindMyAllocate) {
			rebindMyAllocate->deallocate(p, n);
			return;
		}
		MP.deallocate(p);
		//::operator delete(p);//待修改
	}

	void construct(pointer ptr, value_type value) {
		new (ptr) T(value); //定位new，在指定地址处构造对象
	}
	void destroy(pointer ptr) {
		ptr->~T();
	}
	pointer address(reference x) {
		return (pointer)&x;
	}
	const_pointer address(reference x) const {
		return (const_pointer)&x;
	}
	size_type max_size() const {//由于超出Buffer的大内存使用new/delete，可分配内存大小仅仅取决于内存大小，因此与UINT_MAX有关
		return size_type(UINT_MAX / sizeof(T));
	}
	void newElement(value_type value)
	{
		pointer result = allocate();
		construct<value_type>(result, value);
		return result;
	}
	void deleteElement(pointer p)
	{
		if (p != nullptr)
		{
			p->~value_type();
			deallocate(p);
		}
	}
};

#endif