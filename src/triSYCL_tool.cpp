#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void
put_file_into_source(std::istream &input_file,
                     std::ostream &output_file) {

  input_file.seekg(0, std::ios_base::end);
  uint32_t len = input_file.tellg() + 8l;
  input_file.seekg(0, std::ios_base::beg);
  fprintf(stderr, "len is %d\n", len);
  output_file << R"(#include "CL/sycl.hpp"

namespace {

const char binary[] = {
)";

  output_file << "'\\x01', '\\x00', '\\x00', '\\x00', "; // one symbols
  output_file << "'\\x10', '\\x00', '\\x00', '\\x00', "; // 16-byte name
  output_file << "'T', 'R', 'I', 'S', 'Y', 'C', 'L', '_', 'k', 'e', 'r', 'n', 'e', 'l', '_', '0', ";
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // section 0
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // offset 0
  output_file << "'\\x02', '\\x00', '\\x00', '\\x00', "; // 2 args
  output_file << "'\\x02', '\\x00', '\\x00', '\\x00', "; // global
  output_file << "'\\x08', '\\x00', '\\x00', '\\x00', "; // size??
  output_file << "'\\x08', '\\x00', '\\x00', '\\x00', "; // target_size??
  output_file << "'\\x01', '\\x00', '\\x00', '\\x00', "; // target_align??
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // ext type
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // semantic
  output_file << "'\\x02', '\\x00', '\\x00', '\\x00', "; // global
  output_file << "'\\x08', '\\x00', '\\x00', '\\x00', "; // size??
  output_file << "'\\x08', '\\x00', '\\x00', '\\x00', "; // target_size??
  output_file << "'\\x01', '\\x00', '\\x00', '\\x00', "; // target_align??
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // ext type
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // semantic
  output_file << "'\\x01', '\\x00', '\\x00', '\\x00', "; // one section
  output_file << "'\\x00', '\\x00', '\\x00', '\\x00', "; // res id
  output_file << "'\\x02', '\\x00', '\\x00', '\\x00', "; // text executable
  output_file << "'\\x" << std::hex << std::setw(2) << std::setfill('0')
	      << static_cast<unsigned int>((len >> 0) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 8 ) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 16) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 24) & 0xff) << "', ";

  len -= 4;
  output_file << "'\\x" << std::hex << std::setw(2) << std::setfill('0')
	      << static_cast<unsigned int>((len >> 0) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 8 ) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 16) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 24) & 0xff) << "', ";

  len -= 4;
  output_file << "'\\x" << std::hex << std::setw(2) << std::setfill('0')
	      << static_cast<unsigned int>((len >> 0) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 8 ) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 16) & 0xff) << "', '\\x"
    << static_cast<unsigned int>((len >> 24) & 0xff) << "', ";

  for (;;) {
    char c;
    input_file.get(c);
    if (!input_file)
      break;
    output_file << "'\\x" << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<unsigned int>(static_cast<unsigned char>(c))
                << "', ";
  }
  output_file << R"(
};

cl::sycl::drt::code::program p { sizeof(binary), binary };

}
)";
}

int main(int argc, char *argv[]) {

  std::string output_file_name;

  // The description title when displaying the help
  po::options_description desc {
    "Some helper tools for triSYCL"
  };

  // Add the supported options
  desc.add_options()
    ("help,h", "produce this help message")
    ("source-in", po::value<std::string>(),
     R"(Take a file and put it into a C++ file to construct a kernel::code
 when compiled)")
    ("output,o", po::value<std::string>(&output_file_name),
     "specify the relay id (0--3)");

  // Where to get the option results
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // Display the help if required
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("source-in")) {
    std::ifstream input_file { vm["source-in"].as<std::string>() };
    if (!input_file.is_open()) {
      std::cerr << "Failed to open \"" << vm["source-in"].as<std::string>()
                << "\" for --source-in" << std::endl;
      exit(-1);
    }
    input_file.exceptions(std::ifstream::badbit);
    if (output_file_name.empty())
      put_file_into_source(input_file, std::cout);
    else {
      std::ofstream output_file { output_file_name };
      if (!output_file.is_open()) {
        std::cerr << "Failed to open \"" << output_file_name
                  << "\" for --output" << std::endl;
        exit(-1);
      }
      output_file.exceptions(std::ifstream::badbit);
      put_file_into_source(input_file, output_file);
    }
    return 0;
  }

  std::cout << desc << std::endl;
  return 0;
}

/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/
