#include <gflags/gflags.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "comp0019.h"
#include "decomp0019.h"

DEFINE_string(type, "both", "One of encode|decode|both");
DEFINE_string(file, "", "File to test/dump tests from");
DEFINE_bool(dump, false,
            "If true will not run tests, but will dump a single test");
DEFINE_bool(invalid_input, false,
            "If true will assume that the input tests check for invalid input");
DEFINE_uint64(test_index, std::numeric_limits<uint64_t>::max(),
              "If dump is specified this is the index of the test to dump.");

namespace lzw_test {
using Bytes = std::vector<char>;

class SingleChunk {
 public:
  SingleChunk(const Bytes* contents, size_t* at) : contents_(contents) {
    size_t& at_ref = *at;
    assert(at_ref < contents->size());
    const uint32_t* bytes_count =
        reinterpret_cast<const uint32_t*>(contents->data() + at_ref);
    count_ = *bytes_count;
    index_ = at_ref + 4;
    at_ref += count_ + 4;
  }

  void WriteToFileOrDie(FILE* out) const {
    size_t n_written = fwrite(contents_->data() + index_, count_, 1, out);
    assert(n_written == 1);
  }

  void WriteToFileOrDie(const std::string& filename) const {
    FILE* file = fopen(filename.c_str(), "w");
    WriteToFileOrDie(file);
    fclose(file);
  }

  Bytes ToBytes() const {
    Bytes out;
    out.resize(count_);
    std::memcpy(out.data(), contents_->data() + index_, count_);
    return out;
  }

  std::string ToString() const {
    Bytes bytes = ToBytes();
    return std::string(reinterpret_cast<char const*>(bytes.data()),
                       bytes.size());
  }

 private:
  const Bytes* contents_;
  size_t index_;
  size_t count_;
};

static Bytes ReadFileOrDie(const std::string& name) {
  char buffer[1024];
  FILE* file = fopen(name.c_str(), "rb");
  assert(file != NULL);

  Bytes out;
  while (true) {
    size_t n = fread(buffer, 1, sizeof(buffer), file);
    if (n <= 0) break;

    for (size_t i = 0; i < n; ++i) {
      out.emplace_back(buffer[i]);
    }
  }

  int error = ferror(file);
  assert(fclose(file) == 0);
  assert(error == 0);
  return out;
}

static std::string ReadFileToStringOrDie(const std::string& name) {
  Bytes bytes = ReadFileOrDie(name);
  return std::string(reinterpret_cast<char const*>(bytes.data()), bytes.size());
}

static Bytes ReadFileOrDie(FILE* file) {
  fseek(file, 0L, SEEK_END);
  long int fsize = ftell(file);
  assert(fsize >= 0);
  rewind(file);

  if (fsize == 0) {
    return {};
  }

  Bytes contents;
  contents.resize(fsize);
  size_t n_read = fread(&(contents[0]), fsize, 1, file);
  assert(n_read == 1);
  return contents;
}


// Functions for functional (encode/decode) tests
static void RunEncodeTest(const SingleChunk& encoder_input,
                          const SingleChunk& model_encoder_output) {
  FILE* encoder_input_file = tmpfile();
  FILE* test_output_file = tmpfile();

  encoder_input.WriteToFileOrDie(encoder_input_file);
  rewind(encoder_input_file);

  Encode(encoder_input_file, test_output_file);
  Bytes new_encoded = ReadFileOrDie(test_output_file);
  Bytes model_encoder_output_bytes = model_encoder_output.ToBytes();
  if (model_encoder_output_bytes != new_encoded) {
    std::cout << "Encoder output does not match model output" << std::endl;
    exit(1);
  }

  fclose(encoder_input_file);
  fclose(test_output_file);
}

static void RunDecodeTest(const SingleChunk& encoder_input,
                          const SingleChunk& model_encoder_output) {
  FILE* model_encoder_output_file = tmpfile();
  FILE* test_output_file = tmpfile();

  model_encoder_output.WriteToFileOrDie(model_encoder_output_file);
  rewind(model_encoder_output_file);

  Decode(model_encoder_output_file, test_output_file);
  Bytes new_decoded = ReadFileOrDie(test_output_file);
  Bytes original_encoder_input_bytes = encoder_input.ToBytes();
  if (original_encoder_input_bytes != new_decoded) {
    std::cout << "Decoder output does not match original input" << std::endl;
    exit(1);
  }
  
  fclose(model_encoder_output_file);
  fclose(test_output_file);
}

static void RunFunctionalTestsFromFile(const std::string& file, bool encode) {
  Bytes contents = ReadFileOrDie(file);

  size_t test_index = 0;
  size_t at = 0;
  while (at != contents.size()) {
    SingleChunk encoder_input(&contents, &at);
    SingleChunk model_encoder_output(&contents, &at);
  
    if (FLAGS_test_index == std::numeric_limits<uint64_t>::max() ||
        FLAGS_test_index == test_index) {
      std::cout << "Will run test at index " << test_index << std::endl;
      if (encode) {
      	RunEncodeTest(encoder_input, model_encoder_output);
      }
      else {
	RunDecodeTest(encoder_input, model_encoder_output);
      }
      std::cout << "Test passed" << std::endl;
    }

    ++test_index;
  }

  if (FLAGS_test_index != std::numeric_limits<uint64_t>::max() &&
      FLAGS_test_index >= test_index) {
    std::cout << "Unable to find test index " << FLAGS_test_index << std::endl;
    exit(1);
  }
}


// Functions for invalid input tests (those in group three)
static void RunInvalidInputTest(size_t test_index, const SingleChunk& input,
                         const SingleChunk& regex, bool encode) {
  FILE* input_file = tmpfile();
  FILE* output_file = tmpfile();

  std::cout << "Will run test at index " << test_index << std::endl;

  input.WriteToFileOrDie(input_file);
  rewind(input_file);

  int fd;
  fpos_t pos;
  fflush(stdout);
  fgetpos(stdout, &pos);
  fd = dup(fileno(stdout));
  freopen("stdout_contents", "w", stdout);

  if (encode) {
    Encode(input_file, output_file);
  } else {
    Decode(input_file, output_file);
  }

  fflush(stdout);
  dup2(fd, fileno(stdout));
  close(fd);
  clearerr(stdout);
  fsetpos(stdout, &pos);

  std::string output = ReadFileToStringOrDie("stdout_contents");
  std::cout << output;

  std::string regex_string = regex.ToString();
  std::regex re(regex_string,
                std::regex_constants::ECMAScript | std::regex_constants::icase);

  if (!std::regex_search(output, re)) {
    std::cout << "Output does not match expected regex '" << regex_string
              << "'" << std::endl;
    exit(1);
  }
  
  std::cout << "Test passed" << std::endl;

  fclose(input_file);
  fclose(output_file);
}

static void RunInvalidInputTestsFromFile(const std::string& file, bool encode) {
  Bytes contents = ReadFileOrDie(file);

  size_t test_index = 0;
  size_t at = 0;
  while (at != contents.size()) {
    SingleChunk input(&contents, &at);
    SingleChunk regex(&contents, &at);

    if (FLAGS_test_index == std::numeric_limits<uint64_t>::max() ||
        FLAGS_test_index == test_index) {
      RunInvalidInputTest(test_index, input, regex, encode);
    }

    ++test_index;
  }

  if (FLAGS_test_index != std::numeric_limits<uint64_t>::max() &&
      FLAGS_test_index >= test_index) {
    std::cout << "Unable to find test index " << FLAGS_test_index << std::endl;
    exit(1);
  }
}


// dump functions
static void DumpTest(const std::string& file, const std::string& type) {
  Bytes contents = ReadFileOrDie(file);

  size_t test_index = 0;
  size_t at = 0;
  while (at != contents.size()) {
    SingleChunk tested_input(&contents, &at);
    SingleChunk model_output(&contents, &at);

    std::string input_filename = type + "r_input";
    std::string model_output_filename = "model_" + type + "r_output";

    if (test_index == FLAGS_test_index) {
      tested_input.WriteToFileOrDie((type == "encode") ? input_filename : model_output_filename);
      std::cout << type << "r input saved to '" << input_filename << "'"<< std::endl;
      model_output.WriteToFileOrDie((type == "encode") ? model_output_filename : input_filename);
      std::cout << "Model " << type << "r output saved to '"
	        << model_output_filename << "'" << std::endl;
      return;
    }

    ++test_index;
  }

  std::cout << "Unable to find test index " << test_index;
  abort();
}

static void DumpInvalidInputTest(const std::string& file, const std::string& type) {
  Bytes contents = ReadFileOrDie(file);

  size_t test_index = 0;
  size_t at = 0;
  while (at != contents.size()) {
    SingleChunk input(&contents, &at);
    SingleChunk regex(&contents, &at);

    if (test_index == FLAGS_test_index) {
      std::string filename = type + "r_input";
      input.WriteToFileOrDie(filename);
      std::cout << "Input saved to " << filename << std::endl;
      std::cout << "Your " << type 
	        << "r is expected to output an error message matching regex '" 
	        << regex.ToString() <<  "'"
		<< std::endl;
      return;
    }

    ++test_index;
  }

  std::cout << "Unable to find test index " << FLAGS_test_index;
  abort();
}

}  // namespace lzw_test


int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  if (FLAGS_dump) {
    if (FLAGS_invalid_input){
      lzw_test::DumpInvalidInputTest(FLAGS_file, FLAGS_type);
    }
    else {
      lzw_test::DumpTest(FLAGS_file, FLAGS_type);
    }
    
    return 0;
  }

  if (FLAGS_invalid_input) {
    lzw_test::RunInvalidInputTestsFromFile(FLAGS_file, FLAGS_type == "encode");
  }
  else {
    lzw_test::RunFunctionalTestsFromFile(FLAGS_file, FLAGS_type == "encode");
  }

  return 0;
}
