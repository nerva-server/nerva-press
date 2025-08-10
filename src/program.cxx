#include <nerva-press/temper.hxx>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
        std::ostream* out = nullptr;

	std::vector<std::istream*> inputs;

        for(int i=1; i < argc; i++) {
                std::string arg = argv[i];
                if(arg == "-o")
                        if(++i < argc) {
                                arg = argv[i];
                                if(arg == "-")
					out = &std::cout;
				else {
                                        std::ofstream *fout = new std::ofstream(arg);
                                        if(!fout->is_open()) {
                                                std::cerr << "Can't open the file: " << arg << std::endl;
                                                delete fout;
                                                return 1;
                                        }
                                        out = fout;
                                }
                        } else {
                                std::cerr << "File path not given after '-o' option" << std::endl;
                                return 1;
                        }
		else {
                        std::ifstream *fin;
			if(arg == "-")
				fin = new std::ifstream(arg);
	                        if(!fin->is_open()) {
                        	        std::cerr << "Can't open the file: " << arg << std::endl;
                	                delete fin;
        	                        return 1;
	                        }
			} else fin = &std::cin;
                        inputs.push_back(fin);
                }
        }

        if(inputs.size() == 0) {
		std::cerr << "error: no input file specified!" << std::endl;
		return 1;
	}

        if(out == nullptr)
                out = new ofstream("o.press");

        Temper::use(*out);

	*out << "Router NEVRA_PRESS_MAIN_ROUTER;" << std::endl;
	for(std::istream *in: inputs) {
	        Temper::use(*in);
		Temper::proc();
	}

        if(out != &std::cout)
                delete out;

	for(std::istream *in: inputs)
		if(in != &std::cin)
	                delete in;

	return 0;
};
