#include "meta_data.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class config_data
{
  public:
	config_data(string xconfig_file);
	config_data(int* table, float xversion, string xlog_file_path, string xmeta_data_file);
	~config_data();
	int cycle_time(int selection);
	void print_all();
	meta_data* meta_data_ptr;
	bool parse_data();
	bool parse_meta_data();


	//set functions
	bool set_log_file_path(string s);
	bool set_meta_data_file(string s);
	bool set_cycle_time(int selection, int time);
	bool set_version(float selection);
	//helper functions
	bool is_digit(char);
	void remove_spaces(string &);
	int data_size();

	//other things
	bool logtomonitor;
	string log_file_path;


  private:
	int *cycle_time_array;

	float version;
	string meta_data_file;
	string config_file;

};
