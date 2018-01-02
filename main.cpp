#include "vireo/base_h.h"
#include "vireo/base_cpp.h"
#include "vireo/demux/movie.h"

#include "crow_all.h"

bool is_request_valid(const crow::request& req) {
  return req.url_params.get("bitrate") != nullptr;
}

struct Media {
  string filename;
  long bitrate;
  short width;
  short height;
  long timestamp_init;
  long timestamp_end;
}

std::ostringstream transcode(Media chunk) {
  std::ostringstream transcoded_chunk;

  vireo::demux::Movie movie(filename);
  // check https://github.com/twitter/vireo/blob/master/vireo/tools/chunk/main.cpp#L88
  vireo::mux::MP4 muxer(movie.video_track);
  auto binary = muxer();

  return transcoded_chunk;
}

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/<string>")([](const crow::request& req, string filename) {
    std::ostringstream os;

    if (!is_request_valid(req)) {
      return crow::response(400);
    }

    try {
      long bitrate = boost::lexical_cast<long>(req.url_params.get("bitrate"));
    } catch (const boost::bad_lexical_cast &) {
      return crow::response(400);
    }

    chunk = Media{
      filename: filename,
      bitrate: bitrate
    }

    os = transcode(chunk);
    return crow::response{os.str()};
  });

  app.loglevel(crow::LogLevel::Debug);
  app.port(8080).multithreaded().run();
} 
