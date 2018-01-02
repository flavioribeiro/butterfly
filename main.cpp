#include <iostream>

#include "vireo/base_h.h"
#include "vireo/base_cpp.h"
#include "vireo/demux/movie.h"

#include "crow_all.h"

struct VideoChunk {
  string filename;
  long   bitrate;
  short  width;
  short  height;
};

bool is_request_valid(const crow::request& req) {
  std::cout << "valitading request" << std::endl;
  return req.url_params.get("bitrate") != nullptr &&
    req.url_params.get("width") != nullptr && 
    req.url_params.get("height") != nullptr;
}

std::stringstream transcode(VideoChunk chunk) {
  std::stringstream transcoded_chunk;

//  vireo::demux::Movie movie(filename);
//  // check https://github.com/twitter/vireo/blob/master/vireo/tools/chunk/main.cpp#L88
//  vireo::mux::MP4 muxer(movie.video_track);
//  auto binary = muxer();
// 
  transcoded_chunk << "ok" << chunk.bitrate;

  return transcoded_chunk;
}

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/<string>")([](const crow::request& req, string filename) {
    VideoChunk chunk;

    if (!is_request_valid(req)) {
      return crow::response(400);
    }

    try {
      chunk = {
        filename,
        boost::lexical_cast<long>(req.url_params.get("bitrate")),
        boost::lexical_cast<short>(req.url_params.get("width")),
      };
    } catch (const boost::bad_lexical_cast &) {
      return crow::response(400);
    }

    std::stringstream os = transcode(chunk);
    return crow::response{os.str()};
  });

  app.loglevel(crow::LogLevel::Debug);
  app.port(8080).multithreaded().run();
} 
