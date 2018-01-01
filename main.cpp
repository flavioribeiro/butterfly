#include "vireo/base_h.h"
#include "vireo/base_cpp.h"
#include "vireo/demux/movie.h"
#include "vireo/mux/mp4.h"
#include "vireo/util/util.h"

#include "crow_all.h"

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")([](){
    return "Hello w0rldzz!";
  });

  app.port(8080).multithreaded().run();
}

void remux(string in, string out) {
  vireo::demux::Movie movie(in);
  vireo::mux::MP4 muxer(movie.video_track);
  auto binary = muxer();
  vireo::util::save(out, binary);
}
