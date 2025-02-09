#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>


namespace RIIERUTHREAD {

	class RThreadmanage;

		//线程池
	class Threadpool {

		friend class RThreadmanage;

	private:
		unsigned short _initSize;       //初始化线程数量
		using Task = std::function<void()>; //定义类型
		std::vector<std::thread> _pool;          //线程池
		std::queue<Task> _tasks;            //任务队列
		std::mutex _lock;                   //任务队列同步锁

		std::condition_variable _task_cv;   //条件阻塞
		std::atomic<bool> _run{ true };     //线程池是否执行
		std::atomic<int>  _idlThrNum{ 0 };  //空闲线程数量

		//线程自动回收超时时间
		unsigned int waittime = 30000;

		//线程池增长同步锁
		std::mutex lockgrow;
		//线程池自动管理数量设置
		bool threadautograwflag = false;


		//线程池自动回收比例
		float threadproportions;
		//线程池最大线程数
		unsigned int THREADPOOL_MAX_SIZE = 4;

		//线程池关联管理器 (交互对象)
		std::condition_variable* manageslot;


	private:

		Threadpool(unsigned short size = 4);

		~Threadpool();


	public:
		//成员
		//添加任务  --- 带返回值
		template<class F, class... Args>
		auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {

			if (!_run)  
				throw std::runtime_error("commit on ThreadPool is stopped.");

			using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
			auto task = make_shared<std::packaged_task<RetType()>>(
				std::bind(std::forward<F>(f), std::ref(args)...)
			); // 把函数入口及参数,打包(绑定)
			std::future<RetType> future_d = task->get_future();
			{    // 添加任务到队列
				std::lock_guard<std::mutex> lock{ _lock };//对当前块的语句加锁  lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()
				_tasks.emplace([task]() { // push(Task{...}) 放到队列后面
					(*task)();
					});
			}
			//线程数自动管理
			if (threadautograwflag) {
				if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_SIZE)
					addThread(1);
			}

			_task_cv.notify_one(); // 唤醒一个线程执行

			return future_d;
		}


		//无参任务  
		template<class F>
		auto commit(F&& f) -> std::future<decltype(f())> {

			if (!_run)    // stoped ??
				throw std::runtime_error("commit on ThreadPool is stopped.");

			//返回值类型
			using RetType = decltype(f());

			auto task = std::make_shared<std::packaged_task<RetType()>>(std::forward<F>(f));
			//返回值
			std::future<RetType> future_d = task->get_future();

			{
				//添加任务到队列
				std::lock_guard<std::mutex> lock{ _lock };
				_tasks.emplace([task]() {
					(*task)();
					});
			}

			//线程数自动管理
			if (threadautograwflag) {
				if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_SIZE)
					addThread(1);
			}

			_task_cv.notify_one(); // 唤醒一个线程执行

			return future_d;
		}



		//类对象成员函数封装
		template<class F,class O, class... Args>
		auto commitobj(F&& f,O&& obj ,Args&&... args) -> std::future<decltype((obj->*f)(args...))> {
			if (!_run)    // stoped ??
				throw std::runtime_error("commit on ThreadPool is stopped.");

			using RetType = decltype((obj->*f)(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
			auto task = make_shared<std::packaged_task<RetType()>>(
				std::bind(std::forward<F>(f),std::forward<O>(obj), std::ref(args)...)
			); // 把函数入口及参数,打包(绑定)
			std::future<RetType> future_d = task->get_future();
			{    // 添加任务到队列
				std::lock_guard<std::mutex> lock{ _lock };
				_tasks.emplace([task]() { // push(Task{...}) 放到队列后面
					(*task)();
					});
			}
			//线程数自动管理
			if (threadautograwflag) {
				if (_idlThrNum < 1 && _pool.size() < THREADPOOL_MAX_SIZE)
					addThread(1);
			}

			_task_cv.notify_one(); // 唤醒一个线程执行

			return future_d;
		}



		//添加指定数量的线程
		void addThread(unsigned short size);

		//释放线程
		void DeleteThread();


	};



	class RThreadmanage {

		//线程池管理类
	private:
		//线程池
		RIIERUTHREAD::Threadpool* threadpool;
		//管理线程
		std::shared_ptr<std::thread> managethread;
		//线程锁
		std::mutex managemutex;
		//线程条件变量
		std::condition_variable manage_cv;
		//添加任务信号
		std::atomic<bool> addslot{ true };

	public:
		//构造
		RThreadmanage(int threadsize = 4);
		~RThreadmanage();

		//管理work
		void ThreadManageWork();


		//功能
	public:
		//添加任务  --- 带返回值
		template<class F, class... Args>
		auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
			return threadpool->commit(std::forward<F>(f), std::forward<Args>(args)...);
		}

		//无参任务  
		template<class F>
		auto commit(F&& f) -> std::future<decltype(f())> {
			return threadpool->commit(std::forward<F>(f));
		}

		//类对象成员函数封装
		template<class F, class O, class... Args>
		auto commitobj(F&& f, O&& obj, Args&&... args) -> std::future<decltype((obj->*f)(args...))> {
			return threadpool->commitobj(std::forward<F>(f), std::forward<O>(obj), std::forward<Args>(args)...);
		}

	public:
		//设置是否需要释放空闲线程 默认关闭   回收比例默认50%
		RThreadmanage* SetThreadAutoGrawFlag(bool flag, float proportions = 0.5);

		//设置释放空闲线程需等待的时间
		inline RThreadmanage* SetDeleteThreadTime(unsigned int waittime) {
			threadpool->waittime = waittime;
			return this;
		}

		//设置线程池最大线程数  默认4
		inline RThreadmanage* SetThreadNumMax(unsigned short threadnum) {
			if (threadnum > 0) threadpool->THREADPOOL_MAX_SIZE = threadnum;
			return this;
		}


		//返回空闲线程数量
		inline int GetidlCount() {
			return threadpool->_idlThrNum;
		}

		//返回线程数量
		inline int GetthrCount() {
			return threadpool->_pool.size();
		}

		//返回线程池状态
		inline bool GetThreadPoolState() {
			return threadpool->_run.load();
		}

	};


}