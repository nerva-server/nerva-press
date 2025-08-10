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
                                if(arg != "-") {
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
                        std::ifstream *fin = new std::ifstream(arg);
                        if(!fin->is_open()) {
                                std::cerr << "Can't open the file: " << arg << std::endl;
                                delete fin;
                                return 1;
                        }
                        inputs.push_back(fin);
                }
        }

        if(inputs.size() == 0)
                inputs.push_back(&std::cin);

        if(out == nullptr)
                out = &std::cout;

        Temper::use(*out);

	*out << "Router NEVRA_PRESS_MAIN_ROUTER;" << std::endl;
	for(std::istream *in: inputs) {
	        Temper::use(*in);
		Temper::proc();
	}

        if(out != &std::cout)
                delete out;
};
