#include<nerva-press/temper.hxx>

namespace Temper {

std::istream* in;
std::ostream* out;

void use(std::istream &input_stream) {
	in = &input_stream;
}
void use(std::ostream &output_stream) {
	out = &output_stream;
}


bool isCode=false, isInline=false;

void checkCode();

int proc() {
	*out << "NEVRA_PRESS_MAIN_ROUTER.Get(\"/\", {}, [](const Http::Request &req, Http::Response &res, auto next) {" <<
		std::endl;

	*out << "res << R\"(";
	while(in->peek() != EOF) {
		if(!isCode && in->peek() == '<') {
			in->get();
			if(in->peek() == '%') {
				isCode = true;
				in->get();
				isInline = in->peek() == '-';
				if(isInline) {
					*out << ")\" << std::to_string(";
				} else
					*out << ")\";" << std::endl;
			} else *out << '<';
		} else if(isCode && in->peek() == '%') {
                        in->get();
                        if(in->peek() == '>') {
				isCode = false;
                                in->get();
				if(isInline)
					*out << ") << \"";
				else
	                                *out << std::endl << "res << R\"(";
                        } else *out << '%';
                } else *out << (char)in->get();
	}

	if(isCode) {
		std::cerr << "Code block isn't closed" << std::endl;
		return 1;
	}

	*out << ")\";" << std::endl;

	*out << "});" << std::endl;

	return 0;
}

}
