#include "crow_all.h"
#include "lib.h"

using namespace std;

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/<string>")([](const crow::request& req, string filename) {
    VideoChunkInfo chunk_info;
    stringstream extracted_chunk, transcoded_chunk, test;

    if (!is_request_valid(req)) {
      return crow::response(400);
    }

    try {
      chunk_info = {
        filename,
        boost::lexical_cast<long>(req.url_params.get("bitrate")),
        boost::lexical_cast<short>(req.url_params.get("width")),
        boost::lexical_cast<short>(req.url_params.get("height")),
      };
    } catch (const boost::bad_lexical_cast &) {
      return crow::response(400);
    }

    extracted_chunk = extract(chunk_info);
//    transcoded_chunk = transcode(extracted_chunk);

//    return crow::response{transcoded_chunk.str()};
      return crow::response{extracted_chunk.str()};
  });

  app.loglevel(crow::LogLevel::Debug);
  app.port(8080).multithreaded().run();
} 
