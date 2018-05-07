#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class FileWriter
{
	public:
		FileWriter();
		void write_to(string filename, string data);
	private:
		ofstream output_file;
};

#endif
