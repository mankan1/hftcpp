#include <boost/algorithm/string.hpp>
#include <chrono>
#include <fmt/ostream.h>
#include <seastar/core/app-template.hh>
#include <seastar/core/coroutine.hh>
#include <seastar/core/file.hh>
#include <seastar/core/fstream.hh>
#include <seastar/core/memory.hh>
#include <seastar/core/seastar.hh>
#include <seastar/core/sleep.hh>
#include <seastar/core/sstring.hh>
#include <seastar/util/log.hh>

// OS in userspace , setup , execution env - perfect core executor
// instantiate app template
// message queue - not waiting for that to complete, sppeed
// every core gb, instance every core work seastar budget , parameterized on run
// time instances
// few commands to do file io

namespace {
// seastar::logger lg("hello_world");
seastar::logger lg("word_world1");
} // namespace
// take file
// look at size of file and assign ranges to cores
// each core count words
// reduce thos coonts to core 0
// ---
// files larger than memory
//
static seastar::future<> hello_from_cores() {
  for (unsigned int i = 0; i < seastar::smp::count; ++i) {

    co_await seastar::smp::submit_to(i, []() -> seastar::future<> {
      // co_await seastar::smp::invoke_on_all([]() -> seastar::future<> {
      auto memory = seastar::memory::get_memory_layout();

      lg.info("Mem layout start = {} end= {} size= {}", memory.start,
              memory.end, (memory.end - memory.start) / 1000000);
      // co_await seastar::sleep(std::chrono::milliseconds(2000));
      // lg.info("App is running");
      co_return;
    });
  }

  /*for (unsigned int i = 0; i < seastar::smp::count; ++i) {
    // lg.info("App is running");
    co_await seastar::smp::submit_to(i, [] {
      lg.info("App is running{}/{}", seastar::this_shard_id(),
              seastar::smp::count);
    });
  }*/
  co_return;
}

using counts_t = std::unordered_map<seastar::sstring, int>;

static seastar::future<counts_t> word_count(seastar::sstring path, size_t start,
                                            size_t end) {

  lg.info("Counting words from {} to {}", start, end);
  /*auto f = co_await seastar::open_file_dma(path, seastar::open_flags::ro);
  auto is = seastar::make_file_input_stream(f, start);

  seastar::temporary_buffer<char> all_data;
  while (true) {
    auto data = co_await is.read();
    if (data.empty()) {// || (start + all_data.size()) >= end) {
      break;
    }
    
    lg.info("Read bytes {} ", data.size());
    seastar::temporary_buffer<char> tmp(all_data.size() + data.size());
    std::copy_n(all_data.get(), all_data.size(), tmp.get_write());
    // std::copy_n(data.get(), all_data.size(), tmp.get_write());
    std::copy_n(data.get(), data.size(), tmp.get_write());

    all_data = std::move(tmp);
  }

  lg.info("Done Reading bytes {}", all_data.size());
  std::string raw(all_data.get(), all_data.size());
  std::vector<std::string> words;
  boost::split(words, raw, boost::is_any_of("\n"));
 
  lg.info("Split words {}", words.size());
 */
  std::unordered_map<seastar::sstring, int> counts;
  /*for (auto w : words) {
    lg.info("each {}", w);
    if (w != "")
      counts[w]++;
  }
*/
  // auto data1 = co_await is.read();
  //lg.info("Read {} bytes", all_data.size());

  /*auto data2 = co_await is.read();
  lg.info("Read {} bytes", data2.size());*/

  //co_await is.close();
  co_return counts;
}

static seastar::future<> word_count(std::string path) {
  auto file_size = co_await seastar::file_size(path);
  lg.info("Counting words in = {} size= {}", path, file_size);

  counts_t global_counts;
  const auto per_core_size = file_size / seastar::smp::count;
  for (unsigned int i = 0; i < seastar::smp::count; ++i) {
    auto start = i * per_core_size;
    auto end = start + per_core_size;
    auto counts = co_await seastar::smp::submit_to(
        i, [path, start, end] { return word_count(path, start, end); });
   /*for (auto it : counts) {
     lg.info("it {} {}", it.first, it.second);
     global_counts[it.first] += it.second;
    }
    
    lg.info("Done ");
    for (auto it : global_counts) {
      lg.info("Counting words in = {} size= {}", it.first, it.second);
    }*/ 
  }
  co_return;
}

int main(int argc, char **argv) {
  seastar::app_template app;

  namespace po = boost::program_options;
  app.add_options()("file", po::value<std::string>()->required(), "input file");

  // return app.run(argc, argv, [&] { sharding exec atom core, fidelling
  // around with cache lines of orhter core
  return app.run(argc, argv, [&]() -> seastar::future<int> {
    auto &&config = app.configuration();
    seastar::sstring path = config["file"].as<std::string>();
    // co_await word_count(path);
    lg.info("Counting words in : {}", path);
    //co_await word_count(path);
    co_await hello_from_cores();

    // std::cout<< "foo" << std::endl;
    lg.info("App is running");
    co_return 0;
    // return seastar::make_ready_future<int>(0);
    // per cpu machine - core instance its running
    // comp as instance of app per cpu on the machine - what core, instance
    // the application is running on
  });
}
