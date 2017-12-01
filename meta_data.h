#include "node.h"
#include <fstream>

class meta_data//structured as a queue
{
  public:
	meta_data();
	~meta_data();
	bool enqueue(int, int, string, string);
	bool dequeue();
	void print_meta_data(bool, string);
	node* current;
	node* front;
	node* back;
 private:
};
