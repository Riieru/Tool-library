#include"Rthreadpool.h"


RIIERUTHREAD::Threadpool::Threadpool(unsigned short size) { 
	_initSize = size; 
	addThread(size); 
}

RIIERUTHREAD::Threadpool::~Threadpool(){
	//关闭线程池
	{
		std::lock_guard<std::mutex> lock(_lock);
		_run = false;
	}

	_task_cv.notify_all(); // 唤醒所有线程执行
	for (std::thread& thread : _pool) {
		//thread.detach(); // 让线程“自生自灭”
		if (thread.joinable())
			thread.join(); // 等待任务结束， 前提：线程一定会执行完
	}
	_pool.clear();
}







//添加指定数量的线程
void RIIERUTHREAD::Threadpool::addThread(unsigned short size) {
	//线程数自动管理
	if (threadautograwflag) {
		//如果线程池停止运行
		if (!_run)
			throw std::runtime_error("Grow on ThreadPool is stopped.");
		std::unique_lock<std::mutex> lockGrow{ lockgrow }; //自动增长锁
	}
	for (; _pool.size() < THREADPOOL_MAX_SIZE && size > 0; --size) {
		//增加线程数量,但不超过 预定义数量 
		_pool.emplace_back([this] { //工作线程函数
			// 等待任务或线程池关闭
			auto wait_condition = [this] {
				return !_tasks.empty() || !_run;
				};

			while (true) {
				//防止 _run==false 时立即结束,此时任务队列可能不为空
				Task task; // 获取一个待执行的 task
				while (true) {
					std::unique_lock<std::mutex> lock{ _lock };
					// 使用条件变量等待任务，带超时
					if (threadautograwflag) {
						if (!_task_cv.wait_for(lock, std::chrono::milliseconds(waittime), [this] {
							return !_tasks.empty() || !_run;
							})) {
							// 超时发生
							//启动管理器释放方法
							manageslot->notify_all();
							if (threadautograwflag && _pool.size() > _initSize) {
								return; // 自动释放空闲线程
							}
						}
					}
					else {
						// 不带超时的等待
						_task_cv.wait(lock, wait_condition);
					}
					// 条件满足（有任务或线程池关闭）
					if (!_run && _tasks.empty()) {
						return; // 线程池关闭且任务队列为空，退出线程
					}
					if (!_tasks.empty()) {
						// 取出任务
						task = std::move(_tasks.front());
						_tasks.pop();
						_idlThrNum--; // 减少空闲线程数
						break; // 退出循环，执行任务
					}
				}
				//执行任务
				task();
				{
					//执行后更改为空闲状态
					std::unique_lock<std::mutex> lock{ _lock };
					_idlThrNum++;
				}
			  }
			});//线程对象
		{
			//手动添加后，增加的线程
			std::lock_guard<std::mutex> lock{ _lock };
			_idlThrNum++;
		}
	}
}//addthread

		//释放线程
void RIIERUTHREAD::Threadpool::DeleteThread() {
	// 获取最后一个元素的迭代器
	auto it = std::prev(_pool.end());
	std::thread& deletethread = *it;

	if (deletethread.joinable())
		deletethread.join();
	_pool.erase(_pool.end());
	_idlThrNum--;
}


		//构造
RIIERUTHREAD::RThreadmanage::RThreadmanage(int threadsize) : 
	//初始化线程池
	threadpool{new Threadpool(threadsize)} ,
	//初始化管理线程
	managethread{std::make_shared<std::thread>(std::bind(&RIIERUTHREAD::RThreadmanage::ThreadManageWork,this))}
{
	//传递交互对象
	threadpool->manageslot = &manage_cv;

}
RIIERUTHREAD::RThreadmanage::~RThreadmanage() {
	if (threadpool != NULL) {
		delete(threadpool);
		threadpool = NULL;
	}
	manage_cv.notify_all();
	if (managethread->joinable())
		managethread->join(); // 等待任务结束， 前提：线程一定会执行完
}
	



//管理work
void RIIERUTHREAD::RThreadmanage::ThreadManageWork() {
	//管理线程池
	while (true) {


		while (addslot) {
			std::unique_lock<std::mutex> lock(managemutex);
			//检测线程池数量 空闲线程多的话，则释放
			while ((threadpool->_tasks.size() == 0) && (threadpool->_pool.size() > threadpool->_initSize)) {
				threadpool->DeleteThread();
			}
			//打开自动回收模式
			if (threadpool->threadautograwflag) {
				//空闲数量大于一定数值，回收  
				while(threadpool->_run && (threadpool->_tasks.size() == 0) &&(((threadpool->THREADPOOL_MAX_SIZE) * (1-threadpool->threadproportions))< threadpool->_idlThrNum) )
					threadpool->DeleteThread();
			}

			//检测线程池是否继续运行
			if (!this->GetThreadPoolState() || addslot) {
				return;
			}
			manage_cv.wait(lock, [this] {
				return ((threadpool->_tasks.size() == 0) && (threadpool->_pool.size() > threadpool->_initSize)) || addslot;
				});

		}

	}
}



//设置是否需要释放空闲线程 默认关闭   回收比例默认50%
RIIERUTHREAD::RThreadmanage* RIIERUTHREAD::RThreadmanage::SetThreadAutoGrawFlag(bool flag, float proportions) {
	threadpool->threadautograwflag = flag;
	if (!((proportions < 1) && (proportions > 0)))  proportions = 0.5;
	threadpool->threadproportions = proportions;

	return this;
}


