#include <iostream>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/lexical_cast.hpp>

/*	BOOST.ASIO STRAND REFERENCE
	https://chipmaker.tistory.com/entry/boost-asio-%EC%A0%95%EB%A6%AC-4-strand-%EC%A0%81%EC%9A%A9
	https://chipmaker.tistory.com/entry/boost-asio-%EC%A0%95%EB%A6%AC-5-work-%EA%B3%A0%EC%B0%B0?category=534965
	https://htnanote.tistory.com/entry/boostasio-%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC%EC%9D%98-%EB%B9%84%EB%8F%99%EA%B8%B0-%EC%B2%98%EB%A6%AC-%EC%8B%9C-%EC%A3%BC%EC%9D%98%ED%95%B4%EC%95%BC-%ED%95%A0-%EC%A0%90-strand
	http://blog.naver.com/PostView.nhn?blogId=njh0602&logNo=220715956896&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView
	https://devdockr.tistory.com/11
	https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=laster40&logNo=50004283
*/

class CTest
{
public:
	CTest() : service(), strand1(service), strand2(service), strand3(service), strand4(service)
	{
		// ·Î±ë Facility : https://yesarang.tistory.com/74
		std::cout << __FUNCTION__ << std::endl;
	}

	virtual ~CTest()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	void do_print(int x)
	{
		std::string curTrId = boost::lexical_cast<std::string>(boost::this_thread::get_id());

		for (int i = 0; i < x; i++)
		{
			std::printf("[ %d -> current Thread Id : %s] \n", i, curTrId.c_str());
			boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
		}
	}

	void start(void)
	{
		std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl;
#if 0
		service.post(strand1.wrap(boost::bind(&CTest::do_print, this, 5)));
		service.post(strand1.wrap(boost::bind(&CTest::do_print, this, 5)));
		service.post(strand3.wrap(boost::bind(&CTest::do_print, this, 5)));
		service.post(strand4.wrap(boost::bind(&CTest::do_print, this, 5)));
#else
		std::cout << "----------------------------" << std::endl;
		service.post(strand1.wrap(boost::bind(&CTest::do_print, this, 50)));
		service.post(strand2.wrap(boost::bind(&CTest::do_print, this, 50)));
		service.post(strand3.wrap(boost::bind(&CTest::do_print, this, 50)));
		service.post(strand4.wrap(boost::bind(&CTest::do_print, this, 50)));
#endif
		for (int i = 0; i < 4; i++)
		{
			io_threads.create_thread(boost::bind(&boost::asio::io_service::run, &service));
		}
	}

	void stop(void)
	{
		service.stop();
		io_threads.join_all();
		service.reset();
	}
private:
	boost::asio::io_service service;
	boost::thread_group io_threads;
	boost::asio::io_service::strand strand1;
	boost::asio::io_service::strand strand2;
	boost::asio::io_service::strand strand3;
	boost::asio::io_service::strand strand4;
};

int main(int argc, char* argv[])
{
	CTest test;

	test.start();

	while (1)
	{
		char option;
		std::cout << "... in while loop ..." << std::endl;
		std::cin.get(option);

		if (option == 'x')
		{
			break;
		}
	}
	std::cout << "... end of loop ..." << std::endl;
	test.stop();

	std::cout << "... end of main ..." << std::endl;
	return 0;
}