#include "filewriter.h"

using namespace std;

FileWriter::FileWriter()
{

}

void FileWriter::write_to(string filename, string data)
{
	output_file.open(filename, std::ios_base::app);
	output_file << data;
	output_file.close();	
}
