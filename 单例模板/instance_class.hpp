#pragma once

#include<atomic>
#include<mutex>
//单例对象模板
template<class T>
class instance_obj {
private:
	//私有构造
	instance_obj() = default;
	~instance_obj() = default;
	//定义单例锁
	static std::mutex mex;
	//定义单例对象
	static std::atomic<T*> obj;
public:
	static void* GetInstance() {
		//原子操作
		T* temp = obj.load(std::memory_order_acquire);
		if (temp == NULL) {
			mex.lock();
			temp = obj.load(std::memory_order_relaxed);
			if (temp == NULL) {
				temp = new T();
				obj.store(temp, std::memory_order_release);
			}
			mex.unlock();
		}
		return temp;
	}

	//单例释放
	static void DeleteInstance() {
		T* temp = obj.load(std::memory_order_acquire);
		if (temp != NULL) {
			mex.lock();
			temp = obj.load(std::memory_order_relaxed);
			if (temp != NULL) {
				obj.store(NULL, std::memory_order_release);
				delete(temp);
				temp = NULL;
			}
			mex.unlock();
		}
	}
};

template<class T>
std::atomic<T*> instance_obj<T>::obj = NULL;
template<class T>
std::mutex instance_obj<T>::mex;

