#ifndef PROCESS_SQL_EXECUTOR_H
# define PROCESS_SQL_EXECUTOR_H
# include <cppconn/driver.h>
# include <cppconn/exception.h>
# include <cppconn/resultset.h>
# include <cppconn/statement.h>

namespace process
{
	class sql_executor
	{
		static std::thread *proc_thread;

		static std::list<std::string> buffer;

		static std::mutex buffer_lock;

                static std::mutex               suspend_lock;

                static std::condition_variable  suspend_cv;

		static sql::Connection *con;


		static void connect()
		{
			using namespace std::chrono_literals;

			while(1)
			{
				delete con;
				con = 0;
				try
				{
					sql::Driver *driver = get_driver_instance();

					if(!driver)
						std::cout << "\e[31;01m - \e[0msql executor process: failed to obtain MySQL driver instance" << std::endl;
					else
					{
						con = driver->connect("tcp://127.0.0.1:3306","root","Ge25Za40");
						if(!con)
							std::cout << "\e[31;01m - \e[0msql executor process: failed to connect to the MySQL server" << std::endl;
						else
							return;
					}
				}

				catch(sql::SQLException &ex)
				{
					std::cout << "\e[31;01m - \e[0msql executor process: MySQL error " << ex.getErrorCode() <<
						" during connection: " << ex.what() << std::endl;
				}

				std::cout << "\e[31;01m - \e[0msql executor process: MySQL connection failed; retrying in 3 seconds" << std::endl; 
				std::this_thread::sleep_for(3s);
			}
		}

		static void start()
		{
			connect();

			std::cout << "\e[32;01m - \e[0msql executor process: initialized" << std::endl;

			while(1)
			{
				buffer_lock.lock();
				const size_t bs = buffer.size();
				if(!bs)
				{
					buffer_lock.unlock();
					std::cout << "\e[37;01m - \e[0msql executor process: nothing to do; suspending until next notify" << std::endl;
					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
					continue;
				}
				buffer_lock.unlock();

				try {
					std::cout << 
						"\e[37;01m - \e[0msql executor process: executing " <<std::dec<< bs << " statements" << std::endl;
					sql::Statement *s = con->createStatement();
					s->execute("START TRANSACTION");
					while(1)
					{
						buffer_lock.lock();
						if(!buffer.size())
						{
							buffer_lock.unlock();
							break;
						}
						const std::string q = buffer.back();
						buffer.pop_back();
						buffer_lock.unlock();
						try
						{ s->execute(q.c_str()); }
						catch(sql::SQLException &ex)
						{
							std::cout << "\e[31;01m - \e[0mwsql executor process: MySQL error " << ex.getErrorCode() <<
								" in query `" << q << "': " << ex.what() << std::endl;
						}
					}
					s->execute("COMMIT");
					delete s;
				}
				catch(sql::SQLException &ex)
				{ connect(); }
			}
		}
	public:
		static void init()
		{
			con = 0;
			proc_thread = new std::thread(start);
		}

		static void uninit()
		{
			delete proc_thread;
		}

		static void notify(const std::string &query)
		{
			buffer_lock.lock();
			buffer.push_front(query);
			buffer_lock.unlock();
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}
	};

	std::thread *sql_executor::proc_thread;

	std::list<std::string> sql_executor::buffer;

	std::mutex sql_executor::buffer_lock;

	std::mutex               sql_executor::suspend_lock;

	std::condition_variable  sql_executor::suspend_cv;

	sql::Connection *sql_executor::con = 0;
}
#endif
