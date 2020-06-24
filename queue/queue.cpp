#include <iostream>
#include <queue>

using namespace std;

typedef struct  _KSY_Frame
{
	unsigned char *y;
	unsigned char *u;
	unsigned char *v;
	int width;
	int height;
}KSY_Frame;

class framepool{
public:
	framepool(){}
	~framepool();

	KSY_Frame *newFrame(int size);
	void deleteFrame(KSY_Frame *frame);
public:
	queue<KSY_Frame *> frame_queue_;	

};

framepool::~framepool()
{
	// KSY_Frame *tmp;
	// while(frame_queue_.size()>0)
	// {
	// 	tmp = frame_queue_.front();
	// 	frame_queue_.pop();
	// 	deleteFrame(tmp);
	// }
	frame_queue_.pop();
	frame_queue_.pop();

	cout<<"delete"<<frame_queue_.size()<<endl;
}

KSY_Frame *framepool::newFrame(int size)
{
	KSY_Frame *p = (KSY_Frame *)malloc(sizeof(KSY_Frame));
	p->y = (unsigned char *)malloc(size);
	p->u = (unsigned char *)malloc(size);
	p->v = (unsigned char *)malloc(size);

	frame_queue_.push(p);
	cout<<frame_queue_.size()<<endl;
	return p;
}

void framepool::deleteFrame(KSY_Frame *frame)
{
	if(frame->y != NULL)
		free(frame->y);
	if(frame->u != NULL)
		free(frame->y);
	if(frame->v != NULL)
		free(frame->y);
}

int main()
{
	framepool pool;
	pool.newFrame(1024);
	pool.newFrame(2048);

}