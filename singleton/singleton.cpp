#include <list>
#include <iostream>
#include <pthread.h>

using namespace std;

class mcy
{
public:
	static mcy* getInstance()
	{
		pthread_mutex_lock(&mutex);
		if(instance != NULL)
		{
			instance = new mcy();
		}

		pthread_mutex_unlock(&mutex);
		return  instance;
	}

private:
	mcy(){
		pthread_mutex_init(&mutex,NULL);
	}
	static mcy* instance;

public:
	static pthread_mutex_t mutex;
};

pthread_mutex_t mcy::mutex;

mcy*mcy::instance = NULL;


class CSingleton
{
private:
    CSingleton()
    {
    }
    static CSingleton *p;
public:
    static CSingleton* getInstance()
    {
        if(p == NULL)
            p = new CSingleton();
        return p;
    }
};
CSingleton* CSingleton::p = NULL;

int main ()
{
	mcy *a = mcy::getInstance();
	CSingleton *t = CSingleton::getInstance();
}