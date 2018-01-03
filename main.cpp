#include "crow_all.h"
#include "lib.h"

using namespace std;

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
        boost::lexical_cast<short>(req.url_params.get("height")),
      };
    } catch (const boost::bad_lexical_cast &) {
      return crow::response(400);
    }

    stringstream oss = transcode(chunk); 
    return crow::response{oss.str()};
  });

  app.loglevel(crow::LogLevel::Debug);
  app.port(8080).multithreaded().run();
} 
