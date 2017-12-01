#include "meta_data.h"

meta_data::meta_data()
{
  current = NULL;
  front = NULL;
  back = NULL;
}

meta_data::~meta_data()
{
  while(front != NULL)
  {
    current = back;
    back = back->get_next();
    delete current;
  }
  
}

bool meta_data::enqueue(int xcyclenum, int xnumcycles, string xtype, string xletter)
{
  if(front == NULL)
  {
    front = new node(xcyclenum, xnumcycles, xtype, xletter, NULL);
    back = front;
  }
  else
  {
    current = new node(xcyclenum, xnumcycles, xtype, xletter, NULL);
    back->set_next(current);
    back = current;
  }
  
}

bool meta_data::dequeue()
{
  current = front;
  front = current->get_next();
  delete current;
}

void meta_data::print_meta_data(bool logtomonitor, string log_file)
{
  //prints to monitor
  if(logtomonitor)
  {

    cout<<endl<<"Meta-Data Metrics"<<endl;
    while(front != NULL)
    {
	int time = front->get_cyclenum() * front->get_numcycles();
	cout<<front->get_letter()<<"("<<front->get_type()<<")"<<front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	dequeue();
    }
  }
  //prints to monitor and log file
  else
  {
    std::ofstream log(log_file.c_str());
    cout<<endl<<"Meta-Data Metrics"<<endl;
    log<<endl<<"Meta-Data Metrics"<<endl;
    while(front != NULL)
    {
	int time = front->get_cyclenum() * front->get_numcycles();
	cout<<front->get_letter()<<"("<<front->get_type()<<")"<<front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	log<<front->get_letter()<<"("<<front->get_type()<<")"<<front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	dequeue();
    }
    log.close();
  }

}
