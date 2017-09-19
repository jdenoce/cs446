#include "config_data.h"

config_data::config_data(string xconfig_file)
{
  config_file = xconfig_file;
  version = 0.0;
  cycle_time_array = new int[8];
  for(int x=0;x<8;x++)
  {
    cycle_time_array[x]=0;
  }
  log_file_path = "\n";
  meta_data_file = "\n";
  meta_data_ptr = NULL;
  logtomonitor=true;
  meta_data_ptr = new meta_data;

}

config_data::~config_data()
{
  version = 0.0;
  log_file_path = "\n";
  delete[] cycle_time_array;
  cycle_time_array = NULL;
  meta_data_file = "\n";
}

config_data::config_data(int* table, float xversion, string xlog_file_path, string xmeta_data_file)
{
  cycle_time_array = new int[8];
  for(int x=0;x<8;x++)
  {
    cycle_time_array[x]=table[x];
  }
  version = xversion;
  log_file_path = xlog_file_path;
  meta_data_file = xmeta_data_file;
}

/*
0 -processor
1 - monitor
2 - hard drive
3 - printer
4 - keyboard
5 - memory
6 - mouse
7 - speaker
*/
int config_data::cycle_time(int selection)
{
  if(selection > 7 || selection < 0)
  {
    cout<<"Invalid location to retrieve data"<<endl;
    return 0;
  }
  return cycle_time_array[selection];
}

bool config_data::set_cycle_time(int selection, int time)
{
  if(selection < 0 || selection > 7)
  {
    cout<<"Invalid location to store data"<<endl;
    return false;
  }
  cycle_time_array[selection]=time;
  return true;
}

bool config_data::set_version(float selection)
{
  if(selection < 1 || selection > 4)
  {
    cout<<"Invalid version"<<endl;
    return false;
  }
  version = selection;
  return true;
}

bool config_data::set_log_file_path(string s)
{
  log_file_path = s;
  return true;
}

bool config_data::set_meta_data_file(string s)
{
  meta_data_file = s;
  return true;
}


void config_data::print_all()
{
    std::ofstream log(log_file_path.c_str());

    cout<<"Configuration File Data"<<endl;
    cout<<"Processor = "<<cycle_time(0)<<" ms/cycle"<<endl;
    cout<<"Monitor = "<<cycle_time(1)<<" ms/cycle"<<endl;
    cout<<"Hard Drive = "<<cycle_time(2)<<" ms/cycle"<<endl;
    cout<<"Printer = "<<cycle_time(3)<<" ms/cycle"<<endl;
    cout<<"Keyboard = "<<cycle_time(4)<<" ms/cycle"<<endl;
    cout<<"Memory = "<<cycle_time(5)<<" ms/cycle"<<endl;
    cout<<"Mouse = "<<cycle_time(6)<<" ms/cycle"<<endl;
    cout<<"Speaker = "<<cycle_time(7)<<" ms/cycle"<<endl;
    

  if(!logtomonitor)
  {
    cout<<"Logged to: monitor and "<<log_file_path<<endl;
    log<<"Configuration File Data"<<endl;
    log<<"Processor = "<<cycle_time(0)<<" ms/cycle"<<endl;
    log<<"Monitor = "<<cycle_time(1)<<" ms/cycle"<<endl;
    log<<"Hard Drive = "<<cycle_time(2)<<" ms/cycle"<<endl;
    log<<"Printer = "<<cycle_time(3)<<" ms/cycle"<<endl;
    log<<"Keyboard = "<<cycle_time(4)<<" ms/cycle"<<endl;
    log<<"Memory = "<<cycle_time(5)<<" ms/cycle"<<endl;
    log<<"Mouse = "<<cycle_time(6)<<" ms/cycle"<<endl;
    log<<"Speaker = "<<cycle_time(7)<<" ms/cycle"<<endl;
    log<<"Logged to: monitor and "<<log_file_path<<endl;
  }
  else
  {
    cout<<"Logged to: monitor"<<endl;
  }

  //logs only to monitor
  if(logtomonitor)
  {

    cout<<endl<<"Meta-Data Metrics"<<endl;
    while(meta_data_ptr->front != NULL)
    {
	int time = meta_data_ptr->front->get_cyclenum() * meta_data_ptr->front->get_numcycles();
	cout<<meta_data_ptr->front->get_letter()<<"("<<meta_data_ptr->front->get_type()<<")"<<meta_data_ptr->front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	meta_data_ptr->dequeue();
    }
  }
  //prints to monitor and log file
  else
  {
    cout<<endl<<"Meta-Data Metrics"<<endl;
    log<<endl<<"Meta-Data Metrics"<<endl;
    while(meta_data_ptr->front != NULL)
    {
	int time = meta_data_ptr->front->get_cyclenum() * meta_data_ptr->front->get_numcycles();
	cout<<meta_data_ptr->front->get_letter()<<"("<<meta_data_ptr->front->get_type()<<")"<<meta_data_ptr->front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	log<<meta_data_ptr->front->get_letter()<<"("<<meta_data_ptr->front->get_type()<<")"<<meta_data_ptr->front->get_numcycles()<<" - "<<time<<" ms"<<endl;
	meta_data_ptr->dequeue();
    }
  }
  log.close();
}











/////

int config_data::data_size()
{
  int size=0;
  for(int x=0;x<8;x++)
  {
    if(cycle_time_array[x] != 0)
    {
      size++;
    }
  }
  return size;
}

bool config_data::parse_data()
{
  std::ifstream file(config_file.c_str());
  string line;


  while(getline(file, line)) 
  {
    string colon = ":";
    string pre_colon = line.substr(0, line.find(colon));
    string post_colon = line.substr(line.find(colon) + 1);

    //removes whitespace, also convert lowercase?
    remove_spaces(pre_colon);
    remove_spaces(post_colon);

    if(line.find(colon) == std::string::npos)
    {
    }
  else
  { 

    if(pre_colon == "Version/Phase")
    {
	version = atoi(post_colon.c_str());
    }
    if(pre_colon == "FilePath")
    {
	meta_data_file = post_colon;
    }
    if(pre_colon.find("Processor") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(0, time);
    }
    if(pre_colon.find("Monitor") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(1, time);
    }
    if(pre_colon.find("Harddrive") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(2, time);
    }
    if(pre_colon.find("Printer") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(3, time);
    }
    if(pre_colon.find("Keyboard") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(4, time);
    }
    if(pre_colon.find("Memory") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(5, time);
    }
    if(pre_colon.find("Mouse") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(6, time);
    }
    if(pre_colon.find("Speaker") != std::string::npos)
    {
	int time = atoi(post_colon.c_str());
	set_cycle_time(7, time);
    }
    if(pre_colon == "Log")
    {
	if(post_colon == "LogtoBoth")
	{
	  logtomonitor=false;
	}
    }
    if(pre_colon == "LogFilePath")
    {
	log_file_path = post_colon;
    }
  }

  }
  //end of while getline loop
  if(data_size() != 8)
  {
    throw invalid_argument("Error: 8 system cycle times expected");
    return false;
  }
return true;
}

bool config_data::parse_meta_data()//fun!
{
  //checks for valid extension
  int period = meta_data_file.find_last_of(".");
  string extension = meta_data_file.substr(period);
  if(extension != ".mdf")
  {
    throw invalid_argument("Error: Invalid meta data file extension");
    return false;
  }

  //Opening file   
  ifstream meta_file (meta_data_file.c_str());
  string line;

  //Checking if file is empty
  if(meta_file.peek() == std::ifstream::traits_type::eof()) 
  {
    throw std::invalid_argument("Error: Empty meta data file");
    return false;
  }
   bool start_found  = false;
  bool end_found = false;
  int xtype_start;
  int xtype_end;
  int xnumcycle_start;//#cycles location
  int xnumcycle_end;
  string letter;
  

  //Looping through each line
  while(getline(meta_file, line))
  {
    //remove whitespace from to make parsing simpler
    remove_spaces(line);

    //Loop through each character of the line
    for(int x=0;x<line.length();x++) 
    {
	if(line[x] == '(')
	{
	  //If current char is (, then char after should be meta data type
	  xtype_start = x + 1;
	  letter = line[x - 1];
	  
	  //Set flag to true
	  start_found = true;
	}
	else if(line[x] == ')') 
	{
	  //If current char is ), then next characters should be # of cycles
	  xtype_end = x;
	  xnumcycle_start = x + 1;
	  xnumcycle_end = xnumcycle_start;
	 
	  //iterate until character is not a digit
	  while(is_digit(line[xnumcycle_end])) 
	  {
	    xnumcycle_end++;
	  }
	 
	  //Set flag to true
	  end_found = true;
	}

	if(start_found && end_found) 
	{
	  bool queue = true;
	  int code;
	  //Extract info and push onto meta_data stack
	  string type = line.substr(xtype_start, xtype_end - xtype_start);
	  string numcyclesstr = line.substr(xnumcycle_start, xnumcycle_end - xnumcycle_start);
	  int numcycles = atoi(numcyclesstr.c_str());
	  if(letter == "S" || letter == "A")
	  {
		queue=false;
	  }
	  if(letter == "P"){
	    code = cycle_time(0);
	  }
	  if(letter == "I"){
	    if(type=="harddrive"){
		code=2;
	    }
	    if(type=="keyboard"){
		code=cycle_time(4);
	    }
	    if(type=="mouse"){
		code=cycle_time(6);
	    } 
	  }
	  if(letter == "O"){
	    if(type=="harddrive"){
		code=cycle_time(2);
	    }
	    if(type=="monitor"){
		code=cycle_time(1);
	    }
	    if(type=="speaker"){
		code=cycle_time(7);
	    }
	    if(type=="printer"){
		code=cycle_time(3);
	    }
	  }
	  if(letter == "M"){
	    if(type=="block"){
		code=cycle_time(5);
	    }
	    if(type=="allocate"){
		code=cycle_time(5);
	    }
	  }
	  
	  //queues data
	  if(queue)
	  {
	    meta_data_ptr->enqueue(code, numcycles, type, letter);
	  }

	  //reset flags
	  start_found = false;
	  end_found = false;
	}
    }
  }
  return true;
}
/*
0 -processor
1 - monitor
2 - hard drive
3 - printer
4 - keyboard
5 - memory
6 - mouse
7 - speaker
*/



void config_data::remove_spaces(string &str)
{
  std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
  str.erase(end_pos, str.end());
}

bool config_data::is_digit(char x)
{
  if((x=='0') || (x=='1') || (x=='2') || (x=='3') || (x=='4') || (x=='5')  || (x=='6')  || (x=='7') || (x=='8') || (x=='9') )
  {
    return true;
  }
  return false;
}















